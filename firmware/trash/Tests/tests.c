/*
 * tests.c
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */
#include "stm32746g_discovery.h"
#include "stm32746g_discovery_lcd_dma2d.h"
#include "stm32746g_discovery_keys.h"

#include "tests.h"
#include "stdio.h"
#include "../Ressources/stlogo.h"

typedef struct
{
	void   (*DemoFunc)(void);
	uint8_t DemoName[50];
	uint32_t DemoIndex;
}BSP_DemoTypedef;

void Keys_demo(void);
void LCD_demo(void);
void SENSORS_Demo(void);
void Touchscreen_demo(void);
void AudioRec_demo(void);
void AudioLoopback_demo(void);
void AudioPlay_Demo(void);
void SDRAM_demo(void);
void SDRAM_DMA_demo(void);
void QSPI_demo(void);
void FATFSSD_demo(void);

BSP_DemoTypedef  BSP_examples[] =
{
		{Keys_demo, "KEYS", 0},
		{LCD_demo, "LCD", 0},
		{SENSORS_Demo, "SENSORS", 0},
		//{SD_demo, "mSD", 0},
		{Touchscreen_demo, "TOUCHSCREEN", 0},
		{AudioRec_demo, "AUDIO RECORD", 0},
		{AudioLoopback_demo, "AUDIO LOOPBACK", 0},
		{AudioPlay_Demo, "AUDIO PLAY", 0},
		{SDRAM_demo, "SDRAM", 0},
		{SDRAM_DMA_demo, "SDRAM DMA", 0},
		{QSPI_demo, "QSPI", 0},
		{FATFSSD_demo, "FATFS", 0}
};

#define COUNT_OF_EXAMPLE(x)    (sizeof(x)/sizeof(BSP_DemoTypedef))

static uint8_t DemoIndex = 0;
uint8_t NbLoop = 1;

/**
 * @brief  Check for user input.
 * @param  None
 * @retval Input state (1 : active / 0 : Inactive)
 */
uint8_t CheckForUserInput(void)
{
	if (BSP_PB_GetState(BUTTON_A) != RESET)
	{
		HAL_Delay(10);
		while (BSP_PB_GetState(BUTTON_A) != RESET);
		return 1 ;
	}
	return 0;
}

/**
 * @brief  Display main demo messages.
 * @param  None
 * @retval None
 */
static void Display_DemoDescription(void)
{
	uint8_t desc[50];

	/* Set LCD Background Layer  */
	BSP_LCD_SelectLayer(LTDC_FOREGROUND_LAYER);
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	BSP_LCD_SetColorKeying(LTDC_FOREGROUND_LAYER, LCD_COLOR_BLACK);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_Clear(LCD_COLOR_BLACK);

	/* Set LCD Background Layer  */
	BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	/* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);

	/* Display LCD messages */
	BSP_LCD_DisplayStringAt(0, 10, (uint8_t *)"ARM-ADA Next Gen", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 35, (uint8_t *)"Firmware tests", CENTER_MODE);

	/* Draw Bitmap */
	BSP_LCD_DrawBitmap((BSP_LCD_GetXSize() - 80) / 2, 65, (uint8_t *)stlogo);

	BSP_LCD_SetFont(&Font12);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 20, (uint8_t *)"INSA - GEI 2019", CENTER_MODE);

	BSP_LCD_SetFont(&Font16);
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
	BSP_LCD_FillRect(0, BSP_LCD_GetYSize() / 2 + 15, BSP_LCD_GetXSize(), 60);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 + 30, (uint8_t *)"Press A (Red) to start ", CENTER_MODE);
	sprintf((char *)desc, "%s example", BSP_examples[DemoIndex].DemoName);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 + 45, (uint8_t *)desc, CENTER_MODE);
}

void TESTS_Run(void)
{
	Display_DemoDescription();

	/* Wait For User inputs */
	while (1)
	{
		if (BSP_PB_GetState(BUTTON_A) != RESET)
		{
			HAL_Delay(100);
			while (BSP_PB_GetState(BUTTON_A) != RESET);

			BSP_examples[DemoIndex++].DemoFunc();

			if (DemoIndex >= COUNT_OF_EXAMPLE(BSP_examples))
			{
				/* Increment number of loops which be used by EEPROM example */
				NbLoop++;
				DemoIndex = 0;
			}
			Display_DemoDescription();
		}
	}
}


