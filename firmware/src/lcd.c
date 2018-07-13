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
#include "main.h"
#include "rng.h"
#include "stdio.h"
#include "stdlib.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LCD_FEATURES_NUM                3
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

  while (1)
  {

    if (CheckForUserInput() > 0)
    {
      if (++LCD_Feature < LCD_FEATURES_NUM)
      {
        LCD_Show_Feature (LCD_Feature);
      }
      else
      {
        return;
      }
    }
    HAL_Delay(100);
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
  BSP_LCD_DisplayStringAt(0, 45, (uint8_t *)"LCD Features, use BUTTON to display", CENTER_MODE);
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

  uint32_t CoordX,CoordY;
  uint32_t OrgTick=0;
  uint32_t CurrentTick=0;
  uint32_t FPS;
  uint8_t *ImageBuffer;

  int16_t x,y;
  uint32_t cpt;

  char StrBuffer[30];

  BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
  BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
  BSP_LCD_FillRect(12, 92, BSP_LCD_GetXSize() - 24, BSP_LCD_GetYSize() - 104);
  BSP_LCD_SetTextColor(LCD_COLOR_BLACK);

  switch (feature)
  {
    case 1:
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
      break;

    case 2:

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
      break;

    case 0:
      /* Draw Bitmap */
      /*BSP_LCD_DrawBitmap(20, 100, (uint8_t *)stlogo);
      HAL_Delay(100);

      BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, 100, (uint8_t *)stlogo);
      HAL_Delay(100);

      BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, 100, (uint8_t *)stlogo);
      HAL_Delay(100);

      BSP_LCD_DrawBitmap(20, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
      HAL_Delay(100);

      BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
      HAL_Delay(100);

      BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);
      HAL_Delay(100);*/

    	OrgTick = HAL_GetTick();
    	FPS = 0;


    	BSP_LCD_SelectLayer(LTDC_BACKGROUND_LAYER);
    	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    	BSP_LCD_SetFont(&Font16);

    	BSP_LCD_DisplayStringAt(20, 40, (uint8_t *)"Back (Layer0)", LEFT_MODE);

    	BSP_LCD_SelectLayer(LTDC_FOREGROUND_LAYER);
    	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
    	    	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
    	    	BSP_LCD_SetFont(&Font16);
    	BSP_LCD_DisplayStringAt(20, 60, (uint8_t *)"Fore (Layer1)", LEFT_MODE);

    	cpt=0;
    	//ImageBuffer = (uint8_t *)0xC0080000;
    	ImageBuffer = (uint8_t *)0x2004C000;
    	for (y=56;y>=0; y--)
    	{
    		for (x=0; x<160; x++) {
    			ImageBuffer[cpt]= (uint8_t)stlogo[x+y*160+54];
    			cpt++;
    		}
    	}


    	while (1)
    	{
    		/* Draw to numbers */
    		CoordX = RNG_GetNumber();
    		CoordY = RNG_GetNumber();

    		CoordX = (uint32_t)(((uint64_t)CoordX *(480-40-80))/0xFFFFFFFF)+20;
    		CoordY = (uint32_t)(((uint64_t)CoordY *(272-120-60))/0xFFFFFFFF)+100;

    		BSP_LCD_DrawBitmap(CoordX, CoordY, (uint8_t *)ImageBuffer);

    		FPS++;

    		CurrentTick= HAL_GetTick();
    		if(CurrentTick - OrgTick >=1000) {
    			OrgTick = CurrentTick;

    			sprintf (StrBuffer,"FPS = %lu     ", FPS);
    			BSP_LCD_DisplayStringAt(20, 20, (uint8_t *)StrBuffer, LEFT_MODE);

    			FPS=0;
    		}
    	}

	BSP_LCD_DrawBitmap(20, 100, (uint8_t *)stlogo);


	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, 100, (uint8_t *)stlogo);


	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, 100, (uint8_t *)stlogo);


	BSP_LCD_DrawBitmap(20, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);


	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() / 2 - 40, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);


	BSP_LCD_DrawBitmap(BSP_LCD_GetXSize() - 100, BSP_LCD_GetYSize() - 80, (uint8_t *)stlogo);

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
