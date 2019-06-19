/**
 ******************************************************************************
 * @file    BSP/Src/lcd.c
 * @author  MCD Application Team
 * @brief   This example code shows how to use LCD drawing features.
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
#include "stdio.h"
#include "stdlib.h"

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd_dma2d.h"
#include "stm32746g_discovery_rng.h"

#include "tests.h"
#include "../configuration/memory_mapping.h"
#include "../Ressources/stlogo.h"
/** @addtogroup STM32F7xx_HAL_Examples
 * @{
 */

/** @addtogroup BSP
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LCD_FEATURES_NUM                6
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t LCD_Feature = 0;
/* Private function prototypes -----------------------------------------------*/
static void LCD_SetHint(void);
static void LCD_Show_Feature(uint8_t feature);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  LCD demo
 * @param  None
 * @retval None
 */
void LCD_demo (void)
{
	LCD_SetHint();
	LCD_Feature = 0;
	LCD_Show_Feature (LCD_Feature);

	while (CheckForUserInput() == 0);

	while (1)
	{
		if (++LCD_Feature < LCD_FEATURES_NUM)
		{
			LCD_Show_Feature (LCD_Feature);
		}
		else
		{
			return;
		}

		HAL_Delay(100);

		while (CheckForUserInput() != 0);
	}
}

/**
 * @brief  Display LCD demo hint
 * @param  None
 * @retval None
 */
static void LCD_SetHint(void)
{
	/* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set LCD Demo description */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 80);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
	BSP_LCD_SetFont(&Font24);
	BSP_LCD_DisplayStringAt(0, 0, (uint8_t *)"LCD", CENTER_MODE);
	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, 30, (uint8_t *)"This example shows the different", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"LCD Features, press A to display", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 60, (uint8_t *)"next page", CENTER_MODE);

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_DrawRect(10, 90, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 100);
	BSP_LCD_DrawRect(11, 91, BSP_LCD_GetXSize() - 22, BSP_LCD_GetYSize() - 102);
}

/**
 * @brief  Show LCD Features
 * @param  feature : feature index
 * @retval None
 */
static void LCD_Show_Feature(uint8_t feature)
{
	Point Points[] = {{20, 150}, {80, 150}, {80, 200}};
	Point Points2[] = {{100, 150}, {160, 150}, {160, 200}};

	uint32_t OrgTick=0;
	uint32_t CurrentTick=0;
	uint32_t FPS;

	uint32_t color;
	uint16_t x1,y1,x2,y2,rng_val;
	uint16_t tmp;

	uint16_t screenWidth, screenHeight;

	char StrBuffer[30];

	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_FillRect(12, 92, BSP_LCD_GetXSize() - 24, BSP_LCD_GetYSize() - 104);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

	switch (feature)
	{
	case 0:
		/* Text Feature */

		BSP_LCD_DisplayStringAt(14, 100, (uint8_t *)"Left aligned Text", LEFT_MODE);
		BSP_LCD_DisplayStringAt(0, 115, (uint8_t *)"Center aligned Text", CENTER_MODE);
		BSP_LCD_DisplayStringAt(14, 130, (uint8_t *)"Right aligned Text", RIGHT_MODE);
		BSP_LCD_SetFont(&Font24);
		BSP_LCD_DisplayStringAt(14, 180, (uint8_t *)"Font24", LEFT_MODE);
		BSP_LCD_SetFont(&Font20);
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 - 20, 180, (uint8_t *)"Font20", LEFT_MODE);
		BSP_LCD_SetFont(&Font16);
		BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() - 80, 184, (uint8_t *)"Font16", LEFT_MODE);

		while (CheckForUserInput() == 0);
		break;

	case 1:

		/* Draw misc. Shapes */
		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DrawRect(20, 100, 60 , 40);
		BSP_LCD_FillRect(100, 100, 60 , 40);

		BSP_LCD_SetTextColor(LCD_COLOR_GRAY);
		BSP_LCD_DrawCircle(BSP_LCD_GetXSize() - 120, 120, 20);
		BSP_LCD_FillCircle(BSP_LCD_GetXSize() - 40, 120, 20);

		BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
		BSP_LCD_DrawPolygon(Points, 3);
		BSP_LCD_FillPolygon(Points2, 3);

		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_DrawEllipse(BSP_LCD_GetXSize() - 120, 170, 30, 20);
		BSP_LCD_FillEllipse(BSP_LCD_GetXSize() - 50, 170, 30, 20);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_DrawHLine(20, BSP_LCD_GetYSize() - 30, BSP_LCD_GetXSize() / 5);
		BSP_LCD_DrawLine (BSP_LCD_GetXSize() - 150, BSP_LCD_GetYSize() - 20, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 50);
		BSP_LCD_DrawLine (BSP_LCD_GetXSize() - 150, BSP_LCD_GetYSize() - 50, BSP_LCD_GetXSize() - 20, BSP_LCD_GetYSize() - 20);

		while (CheckForUserInput() == 0);

		break;

	case 2:
		screenWidth = BSP_LCD_GetXSize();
		screenHeight = BSP_LCD_GetYSize();

		/* Random drawFillRect */
		while (CheckForUserInput() == 0)
		{
			color = BSP_RNG_GetNumber();
			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x1 = (uint16_t)((rng_val*(screenWidth-40))/0xFFFF);
			x1 += 20;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x2 = (uint16_t)((rng_val*(screenWidth-40))/0xFFFF);
			x2 += 20;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y1 = (uint16_t)((rng_val*(screenHeight-120))/0xFFFF);
			y1 +=100;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y2 = (uint16_t)((rng_val*(screenHeight-120))/0xFFFF);
			y2 +=100;

			if (x1>x2)
			{
				tmp= x1;
				x1=x2;
				x2=tmp;
			}

			if (y1>y2)
			{
				tmp= y1;
				y1=y2;
				y2=tmp;
			}

			if (x1+x2 >=screenWidth-20 ) x2 = screenWidth- x1-20;
			if (y1+y2 >=screenHeight-20 ) y2 = screenHeight- y1-20;

			BSP_LCD_SetTextColor(color);
			BSP_LCD_FillRect(x1, y1, x2 , y2);
		}

		break;
	case 3:
		screenWidth = BSP_LCD_GetXSize();
		screenHeight = BSP_LCD_GetYSize();

		/* Random drawFillRect */
		while (CheckForUserInput() == 0)
		{
			color = BSP_RNG_GetNumber();
			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x1 = (uint16_t)((rng_val*(screenWidth-40))/0xFFFF);
			x1 += 20;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x2 = (uint16_t)((rng_val*(screenWidth-40))/0xFFFF);
			x2 += 20;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y1 = (uint16_t)((rng_val*(screenHeight-120))/0xFFFF);
			y1 +=100;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y2 = (uint16_t)((rng_val*(screenHeight-120))/0xFFFF);
			y2 +=100;

			if (x1>x2)
			{
				tmp= x1;
				x1=x2;
				x2=tmp;
			}

			if (y1>y2)
			{
				tmp= y1;
				y1=y2;
				y2=tmp;
			}

			if (x1+x2 >=screenWidth-20 ) x2 = screenWidth- x1-20;
			if (y1+y2 >=screenHeight-20 ) y2 = screenHeight- y1-20;

			BSP_LCD_SetTextColor(color);
			BSP_LCD_DrawRect(x1, y1, x2 , y2);
		}

		break;
	case 4:
		screenWidth = BSP_LCD_GetXSize();
		screenHeight = BSP_LCD_GetYSize();

		/* Random drawFillRect */
		while (CheckForUserInput() == 0)
		{
			color = BSP_RNG_GetNumber();
			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x1 = (uint16_t)((rng_val*(screenWidth-80))/0xFFFF);
			x1 += 40;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y1 = (uint16_t)((rng_val*(screenHeight-160))/0xFFFF);
			y1 +=120;

			BSP_LCD_SetTextColor(color);
			BSP_LCD_FillCircle(x1,y1, 20);
		}

		break;
	case 5:
		/* Draw Bitmap */
		OrgTick = HAL_GetTick();
		FPS = 0;

		screenWidth = BSP_LCD_GetXSize();
		screenHeight = BSP_LCD_GetYSize();

		while (CheckForUserInput() == 0)
		{
			/* Draw to numbers */
			rng_val = (uint16_t)BSP_RNG_GetNumber();
			x1 = (uint16_t)((rng_val*(screenWidth-20))/0xFFFF);
			x1 += 20;

			rng_val = (uint16_t)BSP_RNG_GetNumber();
			y1 = (uint16_t)((rng_val*(screenHeight-120))/0xFFFF);
			y1 +=100;

			if (x1>screenWidth-80-20) x1 = screenWidth-80-20;
			if (y1>screenHeight-54-20) y1 = screenHeight-54-20;

			BSP_LCD_DrawBitmap(x1, y1, (uint8_t *)stlogo);

			FPS++;

			CurrentTick= HAL_GetTick();
			if(CurrentTick - OrgTick >=1000) {
				OrgTick = CurrentTick;

				sprintf (StrBuffer,"FPS = %lu     ", FPS);
				BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)StrBuffer, LEFT_MODE);

				FPS=0;
			}
		}

		/*BSP_LCD_DrawBitmap(20, 100, (uint8_t *)stlogo);


		BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, 100, (uint8_t *)stlogo);


		BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, 100, (uint8_t *)stlogo);


		BSP_LCD_DrawBitmap(20, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);


		BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);


		BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);*/

		break;

	default :
		break;
	}
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
