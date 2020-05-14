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
#include "string.h"
#include "stdio.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_mag.h"
#include "stm32746g_discovery_acc_gyro.h"
#include "stm32746g_discovery_pressure.h"
#include "stm32746g_discovery_lcd_dma2d.h"

#include "tests.h"
#include "../configuration/memory_mapping.h"

/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */
static void SENSORS_SetHint(void);

/**
 * @brief  Keys Demo
 * @param  None
 * @retval None
 */
void SENSORS_Demo (void)
{
	uint8_t status = MAG_OK;
	uint8_t statusPressure = PRESSURE_OK;

	char strbuff[80];
	acceleration_t acc;
	angularRate_t angularRate;
	magnetic_t mag;
	float temperature;
	float pressure;

	SENSORS_SetHint();

	while (CheckForUserInput() == 0)
	{
		HAL_Delay(100);
		status = BSP_MAG_ReadValues(&mag);
		if (status == MAG_OK) {
			sprintf((char*)&strbuff, "Mag (OK): X= %i, Y=%i, Z=%i     ", (int)mag.x, (int)mag.y, (int)mag.z);
		}
		else {
			sprintf((char*)&strbuff, "Mag (Failed):                                       ");
		}

		BSP_LCD_DisplayStringAt(20, 100, (uint8_t *)strbuff, LEFT_MODE);

		status = BSP_ACC_ReadValues(&acc);
		if (status == ACC_OK) {
			sprintf((char*)&strbuff, "Acc (OK): X= %i, Y=%i, Z=%i     ", (int)acc.x, (int)acc.y, (int)acc.z);
		}
		else {
			sprintf((char*)&strbuff, "Acc (Failed):                                       ");
		}

		BSP_LCD_DisplayStringAt(20, 120, (uint8_t *)strbuff, LEFT_MODE);

		status = BSP_GYRO_ReadValues(&angularRate);
		if (status == ACC_OK) {
			sprintf((char*)&strbuff, "Gyro (OK): X= %i, Y=%i, Z=%i     ", (int)angularRate.x, (int)angularRate.y, (int)angularRate.z);
		}
		else {
			sprintf((char*)&strbuff, "Gyro (Failed):                                      ");
		}

		BSP_LCD_DisplayStringAt(20, 140, (uint8_t *)strbuff, LEFT_MODE);

		statusPressure = BSP_PRESSURE_ReadCompensatedValues(&pressure, &temperature);
		if (statusPressure == PRESSURE_OK) {
			sprintf((char*)&strbuff, "Pressure (OK): %i     ", (int)pressure);
		}
		else {
			sprintf((char*)&strbuff, "Pressure (Failed):                                      ");
		}

		BSP_LCD_DisplayStringAt(20, 160, (uint8_t *)strbuff, LEFT_MODE);

		if (statusPressure == PRESSURE_OK) {
			sprintf((char*)&strbuff, "Temperature (PRESSURE) ( OK): %i C     ", (int)temperature);
		}
		else {
			sprintf((char*)&strbuff, "Temperature (PRESSURE) (NOK):");
		}

		BSP_LCD_DisplayStringAt(20, 240, (uint8_t *)strbuff, LEFT_MODE);

		status = BSP_MAG_ReadTemperature(&temperature);
		if (status == ACC_OK) {
			sprintf((char*)&strbuff, "Temperature (MAG) ( OK): %i C     ", (int)temperature);
		}
		else {
			sprintf((char*)&strbuff, "Temperature (MAG) (NOK):");
		}

		BSP_LCD_DisplayStringAt(20, 200, (uint8_t *)strbuff, LEFT_MODE);

		status = BSP_ACC_ReadTemperature(&temperature);
		if (status == ACC_OK) {
			sprintf((char*)&strbuff, "Temperature (ACC) ( OK): %i C     ", (int)temperature);
		}
		else {
			sprintf((char*)&strbuff, "Temperature (ACC) (NOK):");
		}

		BSP_LCD_DisplayStringAt(20, 220, (uint8_t *)strbuff, LEFT_MODE);
	}

	//__disable_irq();
}

/**
 * @brief  Display SD Demo Hint
 * @param  None
 * @retval None
 */
static void SENSORS_SetHint(void)
{
	/* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set LCD Demo description */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"SENSORS", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows sensors", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"values  ", CENTER_MODE);

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
