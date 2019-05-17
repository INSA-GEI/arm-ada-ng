/**
 ******************************************************************************
 * @file    BSP/Src/keys.c
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
#include "main.h"
#include "string.h"
#include "stdio.h"


/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */
static void KEYS_SetHint(void);

/**
 * @brief  Keys Demo
 * @param  None
 * @retval None
 */
void Keys_demo (void)
{
	uint8_t keys=0;
	uint8_t status;
	char strbuff[30];
	status= BSP_KEYS_Init();

	KEYS_SetHint();

	if (status != KEYS_OK)
	{
		BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"Keys init failed.", LEFT_MODE);
	}
	else
	{
		BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)"Keys init : OK.", LEFT_MODE);
	}

	if (status == KEYS_OK)
	{
		while (CheckForUserInput() == 0)
		{
			HAL_Delay(100);
			status = BSP_KEYS_Read();
			if (status == KEYS_OK) {
				keys=BSP_KEYS_GetKeys();
				sprintf((char*)&strbuff, "Read result: (OK) %02X", keys);
			}
			else {
				sprintf((char*)&strbuff, "Read result: Failed");
			}

			BSP_LCD_DisplayStringAt(20, 130, (uint8_t *)strbuff, LEFT_MODE);
		}
	}
}

/**
 * @brief  Display SD Demo Hint
 * @param  None
 * @retval None
 */
static void KEYS_SetHint(void)
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
	/*BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
	BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);*/

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