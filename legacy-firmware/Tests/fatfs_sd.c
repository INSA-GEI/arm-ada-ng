/**
 ******************************************************************************
 * @file    BSP/Src/fatfs_sd.c
 * @author  MCD Application Team
 * @brief   This example code shows how to use the SD Driver
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
#include "string.h"
#include "stdio.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_lcd_dma2d.h"

#include "ff.h"
#include "tests.h"
#include "../configuration/memory_mapping.h"
/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BLOCK_START_ADDR         0     /* Block start address      */
#define NUM_OF_BLOCKS            5     /* Total number of blocks   */
#define BUFFER_WORDS_SIZE        ((BLOCKSIZE * NUM_OF_BLOCKS) >> 2) /* Total data size in bytes */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t aTxBuffer[BUFFER_WORDS_SIZE];
uint32_t aRxBuffer[BUFFER_WORDS_SIZE];
/* Private function prototypes -----------------------------------------------*/
static void SD_SetHint(void);
//static void Fill_Buffer(uint32_t *pBuffer, uint32_t uwBufferLenght, uint32_t uwOffset);
//static uint8_t Buffercmp(uint32_t* pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  SD Demo
 * @param  None
 * @retval None
 */
void FATFSSD_demo (void)
{
	uint8_t SD_state = MSD_OK;

	volatile FRESULT res;
	FIL fp;
	FATFS FATFS_Obj;
	char buffer[128];
	uint br;
	char strbuff[60];

	SD_SetHint();
	SD_state = BSP_SD_Init();

	if (SD_state != MSD_OK)
	{
		if(SD_state == MSD_ERROR_SD_NOT_PRESENT)
		{
			BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD shall be inserted before running test", LEFT_MODE);
		}
		else
		{
			BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD Initialization : FAIL.", LEFT_MODE);
		}
		BSP_LCD_DisplayStringAt(20, 115, (uint8_t *)"SD Test Aborted.", LEFT_MODE);
	}
	else
	{
		BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"SD Initialization : OK.", LEFT_MODE);
	}

	res = f_mount(&FATFS_Obj, "0:" ,0);

	res = f_open(&fp, "/essai.txt", FA_READ|FA_WRITE);
	if (res != FR_OK) BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)"File opening : Failed.", LEFT_MODE);
	else BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)"File opening : OK.", LEFT_MODE);

	res=f_read(&fp, buffer,  20, &br);
	if (res != FR_OK) BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)"File read : Failed.", LEFT_MODE);
	else
	{
		buffer[br]='\0';
		if (buffer[br-1] == '\n') buffer[br-1]='\0';
		sprintf((char*)&strbuff, "File read(%i): OK (%s).", br, (char*)buffer);
		BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)strbuff, LEFT_MODE);
	}

	res=f_write(&fp, (char*)"/hello",  strlen("/hello"), &br);
	if (res != FR_OK) BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)"File write : Failed.", LEFT_MODE);
	else
	{
		sprintf((char*)&strbuff, "File write(%i): OK.", br);
		BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)strbuff, LEFT_MODE);
	}

	res= f_sync(&fp);
	res =f_close(&fp);
	if (res != FR_OK) BSP_LCD_DisplayStringAt(20, 180, (uint8_t *)"File close : Failed.", LEFT_MODE);
	else BSP_LCD_DisplayStringAt(20, 180, (uint8_t *)"File close : OK.", LEFT_MODE);

	BSP_LCD_DisplayStringAt(20, 200, (uint8_t *)"Test finished !", LEFT_MODE);
	while (1){
		if (CheckForUserInput() > 0)
		{
			return;
		}
	}
}

/**
 * @brief  Display SD Demo Hint
 * @param  None
 * @retval None
 */
static void SD_SetHint(void)
{
	/* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set LCD Demo description */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"FATFS", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows how to write", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"and read data on the SD card ", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"using FATFS", CENTER_MODE);

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
	BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
}

/**
 * @}
 */

/**
 * @}
 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
