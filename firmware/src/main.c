/**
 ******************************************************************************
 * @file    BSP/Src/main.c
 * @author  MCD Application Team
 * @brief   This example code shows how to use the STM32746G Discovery BSP Drivers
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tests.h"

#include "memory_mapping.h"
/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Global extern variables ---------------------------------------------------*/

#ifndef USE_FULL_ASSERT
uint32_t    ErrorCounter = 0;
#endif

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);

static void CPU_CACHE_Enable(void);
static void CPU_EnableFPU(void);
static void CPU_EnableFaultHandler(void);
static void MAIN_SystemInit(void);

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
	uint8_t  lcd_status = LCD_OK;

	/* Enable the FPU */
	CPU_EnableFPU();

	/* Enable User fault, Bus fault, Memory Fault handlers */
	CPU_EnableFaultHandler();

	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
	 */
	HAL_Init();

	/* Configure the system clock to 200 Mhz */
	SystemClock_Config();

	/* Configure system and BSP peripherals (except LCD) */
	MAIN_SystemInit();

	/*##-1- Initialize the LCD #################################################*/
	/* Initialize the LCD */
	lcd_status = BSP_LCD_Init();
	ASSERT(lcd_status != LCD_OK);

	/* Initialize the LCD Layers */
	//BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FRAME_BUFFER);
	BSP_LCD_LayerRgb565Init(LTDC_FOREGROUND_LAYER, LCD_FRAME_BUFFER_LAYER_1);
	BSP_LCD_LayerRgb565Init(LTDC_BACKGROUND_LAYER, LCD_FRAME_BUFFER_LAYER_2);

	TESTS_Run();
}

/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 216000000 (formerly 200000000)
 *            HCLK(Hz)                       = 216000000 (formerly 200000000)
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 25000000
 *            PLL_M                          = 25
 *            PLL_N                          = 432 (formerly 400)
 *            PLL_P                          = 2
 *            PLL_Q                          = 9 (formerly 8)
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 7 (formerly 5)
 * @param  None
 * @retval None
 */
void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;
	HAL_StatusTypeDef ret = HAL_OK;

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 25;
	RCC_OscInitStruct.PLL.PLLN = 432;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 9;

	ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
	if(ret != HAL_OK)
	{
		while(1) { ; }
	}

	/* Activate the OverDrive to reach the 216 MHz Frequency */
	ret = HAL_PWREx_EnableOverDrive();
	if(ret != HAL_OK)
	{
		while(1) { ; }
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);
	if(ret != HAL_OK)
	{
		while(1) { ; }
	}
}

/**
 * @brief EXTI line detection callbacks.
 * @param GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	static uint32_t debounce_time = 0;
	static volatile uint32_t counter_mag=0;
	static volatile uint32_t counter_acc_gyro=0;

	switch (GPIO_Pin)
	{
	case KEY_BUTTON_PIN:
		/* Prevent debounce effect for user key */
		if ((HAL_GetTick() - debounce_time) > 50)
		{
			debounce_time = HAL_GetTick();
		}

		break;
	case AUDIO_IN_INT_GPIO_PIN:
		/* Audio IN interrupt */
		break;
	case MAG_DRDY_PIN:
		/* MAG DRDY interrupt */
		counter_mag++;
		break;
	case ACC_GYRO_DRDY_PIN:
		/* ACC and Gyro DRDY interrupt */
		counter_acc_gyro++;
		break;
	case SD_DETECT_PIN:
		/* SD Detect and TS interrupt (shared) */
		if (HAL_GPIO_ReadPin(TS_INT_GPIO_PORT, TS_INT_PIN))
		{
			/* Touchscreen it */
			BSP_TS_ITClear();
		}
		else
		{
			/* SD Detect it */
		}
		break;

	default:
		/* Unknown interrupt */
		break;
	}
}

/**
 * @brief  CPU L1-Cache enable.
 * @param  None
 * @retval None
 */
static void CPU_CACHE_Enable(void)
{
	/* Enable I-Cache */
	SCB_EnableICache();

	/* Enable D-Cache */
	SCB_EnableDCache();
}

/**
 * @brief  FPU Coprocessors enable.
 * @param  None
 * @retval None
 */
static void CPU_EnableFPU(void)
{
	SCB->CPACR=(0x3<<20)+(0x3<<22); // Enable full access to CP11 and CP10 FPU
}

/**
 * @brief  Fault Manager Enable.
 * @param  None
 * @retval None
 */
static void CPU_EnableFaultHandler(void)
{
	SCB->SHCSR = SCB->SHCSR | (SCB_SHCSR_BUSFAULTENA_Msk + SCB_SHCSR_MEMFAULTENA_Msk + SCB_SHCSR_USGFAULTENA_Msk);
}

/**
 * @brief  Fault Manager Enable.
 * @param  None
 * @retval None
 */
static void MAIN_SystemInit(void)
{
	/* Init standard IO serial link */
	BSP_STDIO_Init();

	/* Init led1 */
	BSP_LED_Init(LED1);

	/* Configure the User Button in GPIO Mode */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_GPIO);

	/* Init External SRAM */
	BSP_SDRAM_Init();

	/* Init QSPI */
	BSP_QSPI_Init();
	BSP_QSPI_EnableMemoryMappedMode();

	/* Init Keys */
	BSP_KEYS_Init();

	/* Init magnetic sensor */
	BSP_MAG_Init();

	/* Init accelerometer and gyroscope sensor */
	BSP_ACC_GYRO_Init();

	/* Init pressure sensor */
	BSP_PRESSURE_Init();

	/* Init WIFI */
	//BSP_WIFI_Init();

	/* Init RNG */
	BSP_RNG_InitGenerator();

}

#ifdef USE_FULL_ASSERT

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif /* USE_FULL_ASSERT */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
