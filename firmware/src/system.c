/******************************************************************************/
/* system.c: resident system main file                                        */
/*                                                                            */
/******************************************************************************/
/* This program is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    This program is distributed in the hope that it will be useful,         */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>.   */
/******************************************************************************/

#include "system.h"
#include "tests.h"

#include "ressources.h"

COLOR *data;

struct Magic_Header_ST
{
	const char magic_str[4];
	const uint32_t abi_version;
	const uint32_t ep; 
};

typedef struct Magic_Header_ST magicHeader;

/* Ces variables doivent rester globale ... liées à la stack systeme */
magicHeader *mh;
int (*AppEntryPoint)(void);
uint32_t *TestEntryPoint;
uint32_t SYSTEM_Stack;
/* Fin des variables liées à la stack */

static __IO uint32_t TimingDelay;
void Delay(__IO uint32_t nTime);
void SYSTEM_PeripheralsReset(void);
void SYSTEM_PeripheralsInit(void);
void SYSTEM_SplashScreen(void);
void SetStack(uint32_t systemstack, uint32_t applistack);
void RETARGET_Init(void);
int SYSTEM_RunApp(void);

volatile int DataReady=0;
int (*AppEntryPoint)(void);
uint32_t *TestEntryPoint;
int return_val;

char RunAutoTest=0;

void SysTick_Handler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
//void USART3_IRQHandler(void);
void DMA2_Channel3_IRQHandler(void);
void TIM4_IRQHandler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);

// Debut de la stack applicative;
void SYSTEM_MoveITVector(void);
void SYSTEM_AddITtoVector (int it, int *p);

int main (void)
{
	/* Pre init du system */
	SetStack(0x10000400,0x2000A000);
	SYSTEM_MoveITVector();
	RETARGET_Init();

	/* Init du systeme */
	SYSTEM_PeripheralsReset();
	SYSTEM_PeripheralsInit();
	GLCD_ResetScreen();

	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Black);

	/* Si l'utilisateur presse la touche B avant le lancement de l'animation
	   on ne lance pas le programme ADA mais un auto-test*/
	if (KEYS_GetState(KEY_B)==KEY_PRESSED)
	{
		RunAutoTest=1;
	}

#ifndef ADA_TEST_SYSTEM	
	if (PRG_CheckReprogRequest()==PRG_RESET_HARDRESET) 
	{
		SYSTEM_SplashScreen();
	}
#endif /* ADA_TEST_SYSTEM */

	/* Finalement, on positionne le drapeau de demarrage a froid */
	/* Desormais, lors d'un reset, le systeme ne ferra plus d'attente pour l'ecran, ni d'animation */
	PRG_ResetReprogRequest();

	GLCD_Clear(White);

	if (RunAutoTest==1)
	{
		/* Lancement des auto-tests */
		//puts ("Starting tests ...\r");
		Tests();
	}

	/* Lance l'application ADA (si les auto test n'ont pas été activés avant) */
	while (SYSTEM_RunApp()!= BAD_APPLICATION_RETURN_CODE);

	/* On arrive ici si l'application est pourrie */
	/* efface le premier secteur du programme utilisateur (pour le rendre invalid et forcer la reprog) */
	PANIC_EraseUserProgramEntry();
	/* Redemarre le system (devrait rester bloqué dans le bootloader) */
	NVIC_SystemReset();	
	//while (1);

	/* N'arrive jamais ici, normalement */
	return 0;
}

/**
 * @brief  Peripheral Reset.
 * @param  None
 * @retval None
 */
int SYSTEM_RunApp(void)
{
	TestEntryPoint = (uint32_t*)APPLICATION_FIRST_ADDR;
	GLCD_SetTextColor(Black);
	GLCD_SetBackColor(White);

	if (*TestEntryPoint == 0xFFFFFFFF)
	{
		/* Pas d'appli en memoire */
		GLCD_DrawString(1,12, "No program loaded");
		GLCD_DrawString(1,14, "C -> Load a program");

		while (KEYS_GetState(KEY_CENTER)!=KEY_PRESSED);
		/* Don't wait for key C to be released, used in bootloader to stop and wait for fresh program to be load */

		return BAD_APPLICATION_RETURN_CODE;
	}
	else 
	{
		mh=(magicHeader*)TestEntryPoint;

		if ((mh->magic_str[0] == 'I') && 
				(mh->magic_str[1] == 'N') &&
				(mh->magic_str[2] == 'S') &&
				(mh->magic_str[3] == 'A'))
		{
			/* Verification de la version d'abi */
			if (mh->abi_version <= ABI_VERSION)
			{
				/* Lancement de l'appli */
				/* Sauvegarde de la stack systeme */
				SYSTEM_Stack = __get_MSP();

				/* On remet la console à 0 */
				CONSOLE_GotoXY(0,0);

				__disable_irq(); 	// Desactive les IT, le temps de changer la stack */
				/* Bascule vers la stack applicative */
				/* La stack appli va de 0x20009000 à 0x2000A000, la stack systeme de 0x10000000 à 0x10000400,
				   le reste (0x1600) est reservée pour les données (data et bss) du systeme et le vecteur d'IT */

				__set_PSP((uint32_t)(0x2000A000-0x4));

				__set_CONTROL(0x2); // bascule en mode thread + psp
				__ISB();			// Vide le cache
				__enable_irq(); 	// réactive les IT

				/* Appelle l'applicatif ADA */
				AppEntryPoint = (int (*)(void))(mh->ep);
				return_val=AppEntryPoint();

				/* Rebascule vers la stack system */
				__disable_irq(); 	// Desactive les IT, le temps de changer la stack */
				__set_CONTROL(0x0); // bascule en mode thread + msp
				__ISB();			// Vide le cache
				__enable_irq(); 	// réactive les IT

				GLCD_SetTextColor(Black);
				GLCD_SetBackColor(White);

				if (return_val == 0xDEAD0001)
				{
					GLCD_DrawString(1,11, "Invalid ABI");
					GLCD_DrawString(1,12, "Program requires a more recent system");
					GLCD_DrawString(1,14, "Please, upgrade system");
				}
				else
				{
					char buffer[50];
					int i;

					sprintf(buffer,"Program terminated with exit code 0x%08X\n",return_val);
					for (i=0; i<strlen(buffer); i++)
					{
						USART_Send(USART1, buffer[i]);
					}

					GLCD_DrawString(1,14, "A -> Run again");
				}

				while ((KEYS_GetState(KEY_A)!=KEY_PRESSED) && (KEYS_GetState(KEY_B)!=KEY_PRESSED));
				while ((KEYS_GetState(KEY_A)==KEY_PRESSED) || (KEYS_GetState(KEY_B)==KEY_PRESSED));
				GLCD_ResetScreen();

				return 0;
			}
			else /* L'appli demande une version plus recente d'abi */
			{
				GLCD_DrawString(1,11, "Invalid ABI");
				GLCD_DrawString(1,12, "Program requires a more recent system");
				GLCD_DrawString(1,14, "C -> Upgrade system ");

				while (KEYS_GetState(KEY_CENTER)!=KEY_PRESSED);
				/* Don't wait for key C to be released, used in bootloader to stop and wait for fresh program to be load */

				return BAD_APPLICATION_RETURN_CODE;
			}
		}
		else
		{
			/* Appli incompatible ou corrompue */
			GLCD_DrawString(1,12, "Invalid or corrupted program");
			GLCD_DrawString(1,14, "C -> Load a new program");

			while (KEYS_GetState(KEY_CENTER)!=KEY_PRESSED);
			/* Don't wait for key C to be released, used in bootloader to stop and wait for fresh program to be load */

			return BAD_APPLICATION_RETURN_CODE;
		}
	}
}

/**
 * @brief  Peripheral Reset.
 * @param  None
 * @retval None
 */
void SYSTEM_PeripheralsReset(void)
{
	/* Switch off all clock */
	RCC_AHBPeriphClockCmd(	RCC_AHBPeriph_ADC34 | RCC_AHBENR_ADC12EN | RCC_AHBPeriph_GPIOA |
			RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |	RCC_AHBPeriph_GPIOD |
			RCC_AHBPeriph_GPIOE |	RCC_AHBPeriph_GPIOF |	RCC_AHBPeriph_TS |
			RCC_AHBPeriph_CRC |	RCC_AHBPeriph_FLITF |	RCC_AHBPeriph_SRAM |
			RCC_AHBPeriph_DMA2 |	RCC_AHBPeriph_DMA1, DISABLE);

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG | RCC_APB2Periph_TIM1 | RCC_APB2Periph_SPI1 |
			RCC_APB2Periph_TIM8 | RCC_APB2Periph_USART1 | RCC_APB2Periph_TIM15 |
			RCC_APB2Periph_TIM16 | RCC_APB2Periph_TIM17, DISABLE);

	RCC_APB1PeriphClockCmd( RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |
			RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_WWDG |
			RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3 | RCC_APB1Periph_USART2 |
			RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 |
			RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2 | RCC_APB1Periph_USB |
			RCC_APB1Periph_CAN1  | RCC_APB1Periph_PWR | RCC_APB1Periph_DAC, ENABLE);

	__DSB();
	__ISB();

	/* Reset Every periph on AHB */
	RCC_AHBPeriphResetCmd(	RCC_AHBPeriph_ADC34 | RCC_AHBENR_ADC12EN | RCC_AHBPeriph_GPIOA |
			RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |	RCC_AHBPeriph_GPIOD |
			RCC_AHBPeriph_GPIOE |	RCC_AHBPeriph_GPIOF |	RCC_AHBPeriph_TS |
			RCC_AHBPeriph_CRC |	RCC_AHBPeriph_FLITF |	RCC_AHBPeriph_SRAM |
			RCC_AHBPeriph_DMA2 |	RCC_AHBPeriph_DMA1, ENABLE);

	RCC_APB2PeriphResetCmd(	RCC_APB2Periph_SYSCFG | RCC_APB2Periph_TIM1 | RCC_APB2Periph_SPI1 |
			RCC_APB2Periph_TIM8 | RCC_APB2Periph_USART1 | RCC_APB2Periph_TIM15 |
			RCC_APB2Periph_TIM16 | RCC_APB2Periph_TIM17, ENABLE);

	RCC_APB1PeriphResetCmd( RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |
			RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_WWDG |
			RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3 | RCC_APB1Periph_USART2 |
			RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 |
			RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2 | RCC_APB1Periph_USB |
			RCC_APB1Periph_CAN1  | RCC_APB1Periph_PWR | RCC_APB1Periph_DAC, ENABLE);

	__DSB();
	__ISB();

	/* Reset SYSTICK */
	SysTick->CTRL=0;

	/* Reset NVIC */
	NVIC->ICER[0]=0xFFFFFFFF;
	NVIC->ICER[1]=0xFFFFFFFF;
	NVIC->ICER[1]=0xFFFFFFFF;

	/* Release Reset */
	RCC_AHBPeriphResetCmd(	RCC_AHBPeriph_ADC34 | RCC_AHBENR_ADC12EN | RCC_AHBPeriph_GPIOA |
			RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC |	RCC_AHBPeriph_GPIOD |
			RCC_AHBPeriph_GPIOE |	RCC_AHBPeriph_GPIOF |	RCC_AHBPeriph_TS |
			RCC_AHBPeriph_CRC |	RCC_AHBPeriph_FLITF |	RCC_AHBPeriph_SRAM |
			RCC_AHBPeriph_DMA2 |	RCC_AHBPeriph_DMA1, DISABLE);

	RCC_APB2PeriphResetCmd( RCC_APB2Periph_SYSCFG | RCC_APB2Periph_TIM1 | RCC_APB2Periph_SPI1 |
			RCC_APB2Periph_TIM8 | RCC_APB2Periph_USART1 | RCC_APB2Periph_TIM15 |
			RCC_APB2Periph_TIM16 | RCC_APB2Periph_TIM17, DISABLE);


	RCC_APB1PeriphResetCmd( RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |
			RCC_APB1Periph_TIM6 | RCC_APB1Periph_TIM7 | RCC_APB1Periph_WWDG |
			RCC_APB1Periph_SPI2 | RCC_APB1Periph_SPI3 | RCC_APB1Periph_USART2 |
			RCC_APB1Periph_USART3 | RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 |
			RCC_APB1Periph_I2C1 | RCC_APB1Periph_I2C2 | RCC_APB1Periph_USB |
			RCC_APB1Periph_CAN1  | RCC_APB1Periph_PWR | RCC_APB1Periph_DAC, DISABLE);
	__DSB();
	__ISB();
}

/**
 * @brief  Peripheral initialisation.
 * @param  None
 * @retval None
 */
void SYSTEM_PeripheralsInit(void)
{
	//uint32_t Status = 0;
	L3GD20_InitTypeDef L3GD20_InitStructure;
	L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;

	LSM303DLHCMag_InitTypeDef LSM303DLHC_InitStructure;
	LSM303DLHCAcc_InitTypeDef LSM303DLHCAcc_InitStructure;
	LSM303DLHCAcc_FilterConfigTypeDef LSM303DLHCFilter_InitStructure;

	/* Vectorize IT */
	SYSTEM_AddITtoVector(NonMaskableInt_IRQn, (int*)NMI_Handler);
	SYSTEM_AddITtoVector(NonMaskableInt_IRQn+1, (int*)HardFault_Handler);
	SYSTEM_AddITtoVector(MemoryManagement_IRQn, (int*)MemManage_Handler);
	SYSTEM_AddITtoVector(BusFault_IRQn , (int*)BusFault_Handler);
	SYSTEM_AddITtoVector(UsageFault_IRQn, (int*)UsageFault_Handler);

	SYSTEM_AddITtoVector(SysTick_IRQn, (int*)SysTick_Handler);
	SYSTEM_AddITtoVector(USART1_IRQn, (int*)USART1_IRQHandler);
	SYSTEM_AddITtoVector(USART2_IRQn, (int*)USART2_IRQHandler);
	SYSTEM_AddITtoVector(DMA2_Channel3_IRQn, (int*)DMA2_Channel3_IRQHandler);
	SYSTEM_AddITtoVector(TIM4_IRQn, (int*)TIM4_IRQHandler);

	/* Demarrage du systick */
	SysTick_Config(SystemCoreClock/1000);
	NVIC_SetPriority(SysTick_IRQn,15);

	//MALLOC_Init(MALLOC_INITIAL_BASE);

	USART_Configure(USART1, BAUDRATE, USART_NO_REMAP);

	//puts ("\r\rSystem %d.%d\r", BL_MAJOR_VERSION, BL_MINOR_VERSION);
	//puts ("Init [");

	//puts ("Usart Systick IT Led ");
	LED_Init();
	LED_Set(LED_ON);

	//puts ("Keys ");
	KEYS_Init();
	POT_Init();

	/* Demarrage du generateur de nombre aleatoire */
	//puts ("Rng ");
	RNG_Init();

	/* Demarrage de l'audio */
	//puts ("Audio ");
	AUDIO_Init();

	/* Demarrage de la RAM externe */
	//puts ("Sram ");
	SRAM_Init();

	/* Demarrage de la carte SD */
	//	socket_cp_init();
	//	disk_timerproc();
	//	disk_timerproc();
	//  printf ("SD Card ");
	//	Status = SD_Init();

	//#ifndef ADA_TEST_SYSTEM
	if (PRG_CheckReprogRequest()==PRG_RESET_HARDRESET)
		GLCD_Wait();
	//#endif /* ADA_TEST_SYSTEM */

	//puts ("Lcd ");
	GLCD_Init();
	GLCD_Clear(White);

	/* Configure Mems L3GD20 */
	//puts ("L3gd20 ");
	L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
	L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_1;
	L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
	L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_4;
	L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
	L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
	L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_500;
	L3GD20_Init(&L3GD20_InitStructure);

	L3GD20_FilterStructure.HighPassFilter_Mode_Selection =L3GD20_HPM_NORMAL_MODE_RES;
	L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_0;
	L3GD20_FilterConfig(&L3GD20_FilterStructure) ;

	L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_ENABLE);

	/* Configure MEMS magnetometer main parameters: temp, working mode, full Scale and Data rate */
	//puts ("Lsm303dlhc ");
	LSM303DLHC_InitStructure.Temperature_Sensor = LSM303DLHC_TEMPSENSOR_DISABLE;
	LSM303DLHC_InitStructure.MagOutput_DataRate =LSM303DLHC_ODR_30_HZ ;
	LSM303DLHC_InitStructure.MagFull_Scale = LSM303DLHC_FS_8_1_GA;
	LSM303DLHC_InitStructure.Working_Mode = LSM303DLHC_CONTINUOS_CONVERSION;
	LSM303DLHC_MagInit(&LSM303DLHC_InitStructure);

	/* Fill the accelerometer structure */
	LSM303DLHCAcc_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
	LSM303DLHCAcc_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_50_HZ;
	LSM303DLHCAcc_InitStructure.Axes_Enable= LSM303DLHC_AXES_ENABLE;
	LSM303DLHCAcc_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
	LSM303DLHCAcc_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
	LSM303DLHCAcc_InitStructure.Endianness=LSM303DLHC_BLE_LSB;
	LSM303DLHCAcc_InitStructure.High_Resolution=LSM303DLHC_HR_ENABLE;
	/* Configure the accelerometer main parameters */
	LSM303DLHC_AccInit(&LSM303DLHCAcc_InitStructure);

	/* Fill the accelerometer LPF structure */
	LSM303DLHCFilter_InitStructure.HighPassFilter_Mode_Selection =LSM303DLHC_HPM_NORMAL_MODE;
	LSM303DLHCFilter_InitStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
	LSM303DLHCFilter_InitStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
	LSM303DLHCFilter_InitStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;

	/* Configure the accelerometer LPF main parameters */
	LSM303DLHC_AccFilterConfig(&LSM303DLHCFilter_InitStructure);

	//puts ("] Done\r");
}

/**
 * @brief  Vectorise une routine d'interruption
 * @param  it: numero de l'interruption
 * @param  *p: Pointeur vers la routine d'it
 * @retval None
 */
void SYSTEM_AddITtoVector (int it, int *p)
{
	uint32_t *VectorTable=(uint32_t*)VECTOR_TABLE_ADDR;
	VectorTable[it+16] = (int)p;
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in 10 ms.
 * @retval None
 */
void SYSTEM_SplashScreen(void)
{
	int dx,i;
	int x;
	char str[15];

	GLCD_SetLayer(GLCD_LAYER2);
	GLCD_SetTextColor(White);
	GLCD_DrawFillRectangle(0,0,319,239);
	GLCD_SetLayer(GLCD_LAYER1);
	GLCD_SetTextColor(White);
	GLCD_DrawFillRectangle(0,0,319,239);

	GLCD_SetTransparentColor(Green);
	GLCD_LayerScrollMode(GLCD_LAYER_SCROLL_BOTH);
	GLCD_LayerDisplayMode(GLCD_LAYER_DISPLAY_TRANSPARENT);
	GLCD_LayerTransparency(GLCD_LAYER_TRANSPARENT_TOTAL,GLCD_LAYER_TRANSPARENT_TOTAL);

	if (KEYS_GetState(KEY_A)==KEY_PRESSED) 
	{
		GLCD_SetTextColor(Black);
		GLCD_SetBackColor(White);

		sprintf (str, "System ver. %d.%d", BL_MAJOR_VERSION, BL_MINOR_VERSION);
		GLCD_DrawString((40-strlen(str))/2, 13, str);
	}

	/* allocation du buffer pour l'image */
	//data = (COLOR*)MALLOC_GetMemory(logo_armada.height*logo_armada.width);
	data = (COLOR*)malloc(logo_armada.height*logo_armada.width);
	if (data ==0x0) while (1);

	UnpackBMP((PackedBMP_Header *)&logo_armada, data);

	/* Animation du logo de demarrage */
	GLCD_SetLayer(GLCD_LAYER2);
	GLCD_DrawImage(data, (320-logo_armada.width)/2, (240-logo_armada.height)/2, logo_armada.width, logo_armada.height);

	//MALLOC_FreeMemory(data);
	free(data);
	GLCD_SetLayer(GLCD_LAYER1);
	GLCD_SetTextColor(Green);

	for (i=1; i<33; i++)
	{
		dx=(logo_armada.width*i)/(2*32);
		x=(320/2)-dx;

		GLCD_DrawFillRectangle(x,(240-logo_armada.height)/2,x+(dx*2),((240-logo_armada.height)/2)+logo_armada.height);
		Delay(20);
	}

	Delay(2000);

	GLCD_ResetScreen();
}


/**
 * @brief  Move IT vector to a better place (start of 0x2000000)
 * @param  None
 * @retval None
 */
void SYSTEM_MoveITVector(void)
{
	uint32_t* porg=0x0;
	int i;
	uint32_t *VectorTable=(uint32_t*)VECTOR_TABLE_ADDR;

	/* Recopie la table des vecteurs d'IT */
	for (i=0; i<96; i++)
	{
		VectorTable[i] = porg[i];
	}

	/* et mets a jour VTOR */
	SCB->VTOR = (uint32_t)VectorTable;
}

/**
 * @brief  Inserts a delay time.
 * @param  nTime: specifies the delay time length, in 10 ms.
 * @retval None
 */
void Delay(volatile uint32_t nTime)
{
	TimingDelay = nTime;

	while(TimingDelay != 0);
}

/**
 * @brief  Decrements the TimingDelay variable.
 * @param  None
 * @retval None
 */
void TimingDelay_Decrement(void)
{
	if (TimingDelay != 0x00)
	{
		TimingDelay--;
	}
}

/* Appelé tout les ms */
void SysTick_Handler(void)
{
	static int Counter_100Hz=0;

	TimingDelay_Decrement();

	POT_Filtering();

	Counter_100Hz++;
	if (Counter_100Hz>=10) 
	{
		/* Fonction utilisée par fatFS */
		//disk_timerproc();
		Counter_100Hz=0;
	}

	DataReady++;

	/* Gestion des evenements timer envoyés vers l'applicatif */
	TIMER_Handler();
}


