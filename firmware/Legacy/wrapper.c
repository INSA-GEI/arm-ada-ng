/*
 * legacy.c
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */

#include "stm32746g_discovery.h"
#include "wrapper.h"
#include "panic.h"

#include "stm32746g_discovery_acc_gyro.h"
#include "stm32746g_discovery_eeprom.h"
#include "stm32746g_discovery_keys.h"
#include "stm32746g_discovery_audio.h"
#include "stm32746g_discovery_lcd_dma2d.h"
#include "stm32746g_discovery_mag.h"
#include "stm32746g_discovery_rng.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_ts.h"

#include "GUI/progressbar.h"
#include "GUI/window.h"

#define LEGACY_LCD_WIDTH 	320
#define LEGACY_LCD_HEIGHT	240

#define HORIZONTAL_COORD_CONVERSION(x) (((RK043FN48H_WIDTH-LEGACY_LCD_WIDTH)/2)+x)
#define VERTICAL_COORD_CONVERSION(y) (((RK043FN48H_HEIGHT-LEGACY_LCD_HEIGHT)/2)+y)

#define ABS(x) (x>=0 ? x: -x)
uint32_t WRAPPER_ColorConvertion (COLOR color);

extern const uint32_t* _legacysram_start; // Define allocated sram block used to simulate external ram in legacy system

float val[3]={0.0,0.0,0.0};
acceleration_t acc;
magnetic_t mag;
angularRate_t ang;

TIM_HandleTypeDef LegacyTimHandle;
TIMER_EventCallback LegacyTimerCallback=0x0;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t w;
	uint16_t h;
} PROGRESSBAR_TypeDef;

PROGRESSBAR_TypeDef POT_LastProgressBar = {0,0,0,0};
uint8_t POT_LastVal=0;

/**
 * Init function for legacy wrapper, in charge of initializing Timer 7, for example
 */
void WRAPPER_Init (void) {
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
	uint32_t              uwPrescalerValue = 0U;
	uint32_t              pFLatency;

	/*Configure the TIM7 IRQ priority */
	HAL_NVIC_SetPriority(TIM7_IRQn, 0xFU ,0U);

	/* Enable the TIM7 global Interrupt */
	HAL_NVIC_EnableIRQ(TIM7_IRQn);

	/* Enable TIM7 clock */
	__HAL_RCC_TIM7_CLK_ENABLE();

	/* Get clock configuration */
	HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);

	/* Get APB1 prescaler */
	uwAPB1Prescaler = clkconfig.APB1CLKDivider;

	/* Compute TIM7 clock */
	if (uwAPB1Prescaler == RCC_HCLK_DIV1)
	{
		uwTimclock = HAL_RCC_GetPCLK1Freq();
	}
	else
	{
		uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
	}

	/* Compute the prescaler value to have TIM7 counter clock equal to 1MHz */
	uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);

	/* Initialize TIM7 */
	LegacyTimHandle.Instance = TIM7;

	/* Initialize TIMx peripheral as follow:
	  + Period = [(TIM7CLK/100) - 1]. to have a (1/100) s time base.
	  + Prescaler = (uwTimclock/100000 - 1) to have a 0.1MHz counter clock.
	  + ClockDivision = 0
	  + Counter direction = Up
	 */
	LegacyTimHandle.Init.Period = (1000000U / 100U) - 1U;
	LegacyTimHandle.Init.Prescaler = uwPrescalerValue*10;
	LegacyTimHandle.Init.ClockDivision = 0;
	LegacyTimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
	LegacyTimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

	if(HAL_TIM_Base_Init(&LegacyTimHandle) == HAL_OK)
	{
		/* Start the TIM time Base generation with interrupt disabled  */
		HAL_TIM_Base_Start(&LegacyTimHandle);
	}
}

uint32_t WRAPPER_ColorConvertion (COLOR color) {
	uint32_t val;

	if (color == 0xFF) val = 0xFFFFFFFF;
	else
	{
		/* Convertion 3:3:2 to 8:8:8:8 */
		val = 0xFF000000 + (((uint32_t)(color&0xE0))<<20)+(((uint32_t)(color&0x1C))<<12)+(((uint32_t)(color&0x03))<<6);
	}

	return val;
}

// Basic OS services
// void API_InvalidFunction(void)
// Already defined in abi-table.c

void Delay(volatile uint32_t nTime) {
	HAL_Delay(nTime);
}

void GLCD_Clear (COLOR color) {
	//BSP_LCD_Clear(WRAPPER_ColorConvertion(color));
	BSP_LCD_SetTextColor(WRAPPER_ColorConvertion(color));
	GLCD_DrawFillRectangle (0, 0, 320-1, 240-1);
}

void GLCD_SetTextColor (COLOR color) {
	BSP_LCD_SetTextColor(WRAPPER_ColorConvertion(color));
}

void GLCD_SetBackColor (COLOR color) {
	BSP_LCD_SetBackColor(WRAPPER_ColorConvertion(color));
}

void GLCD_PutPixel (uint32_t x, uint32_t y, COLOR color) {
	BSP_LCD_DrawPixel(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y),WRAPPER_ColorConvertion(color));
}

void GLCD_DrawChar (uint32_t x,  uint32_t y, uint8_t c) {
	uint8_t str[2] = {c, 0};
	BSP_LCD_DisplayStringAt(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y), str, LEFT_MODE);
}

void GLCD_DrawString (uint32_t x,  uint32_t y, const char *str) {
	uint32_t col,row;

	if (x>((320/8)-1)) x= ((320/8)-1);
	if (y>((240/16)-1)) y= ((240/16)-1);
	col = x*8;
	row = (y*16)-1;

	BSP_LCD_SetFont(&FontLegacy);
	BSP_LCD_DisplayStringAt(HORIZONTAL_COORD_CONVERSION(col),VERTICAL_COORD_CONVERSION(row), (uint8_t *)str, LEFT_MODE);
}

void GLCD_DrawADAString (uint32_t x, uint32_t y, uint32_t len, const char *str) {
	uint8_t buf[len+1];
	memcpy(buf,str,len);
	buf[len]=0;

	GLCD_DrawString (x,  y, (const char*)buf);
}

void GLCD_DrawLine (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	BSP_LCD_DrawLine(HORIZONTAL_COORD_CONVERSION(x1),VERTICAL_COORD_CONVERSION(y1),HORIZONTAL_COORD_CONVERSION(x2),VERTICAL_COORD_CONVERSION(y2));
}

void GLCD_DrawRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	BSP_LCD_DrawRect(HORIZONTAL_COORD_CONVERSION(x1),VERTICAL_COORD_CONVERSION(y1), ABS(x2-x1), ABS(y2-y1));
}

void GLCD_DrawFillRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	BSP_LCD_FillRect(HORIZONTAL_COORD_CONVERSION(x1),VERTICAL_COORD_CONVERSION(y1), ABS(x2-x1), ABS(y2-y1));
}

void GLCD_DrawCircle (uint32_t x, uint32_t y, uint32_t radius) {
	BSP_LCD_DrawCircle(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y), radius);
}

void GLCD_DrawFillCircle (uint32_t x, uint32_t y, uint32_t radius) {
	BSP_LCD_FillCircle(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y), radius);
}

void GLCD_DrawImage (COLOR* data, uint32_t x, uint32_t y, uint32_t w, int32_t h) {
	//BSP_LCD_DrawBitmap()
}

// Second set of function for GLCD
void GLCD_DrawImagefromSRAM (uint32_t SRAM_Ptr, uint32_t x, uint32_t y, uint32_t w, int32_t h) {
	//
}

void GLCD_LayerScrollMode(uint8_t mode) {
	//
}

void GLCD_SetScrollWindow (uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	//
}

void GLCD_ScrollVertical (uint32_t dy) {
	//
}

void GLCD_ScrollHorizontal (uint32_t dy) {
	//
}

void GLCD_LayerDisplayMode(uint8_t mode) {
	//
}

void GLCD_LayerTransparency(uint8_t layer1_trans, uint8_t layer2_trans) {
	BSP_LCD_SetTransparency(LTDC_BACKGROUND_LAYER, layer1_trans);
	BSP_LCD_SetTransparency(LTDC_FOREGROUND_LAYER, layer2_trans);
}

void GLCD_SetLayer(uint8_t layerNbr) {
	BSP_LCD_SelectLayer(layerNbr);
}

void GLCD_BTESetSource(uint32_t X, uint32_t Y, uint8_t layer) {
	//
}

void GLCD_BTESetDestination(uint32_t X, uint32_t Y, uint8_t layer) {
	//
}

void GLCD_BTESetSize(uint32_t width, uint32_t height) {
	//
}

void GLCD_BTESetBackgroundColor(uint32_t red, uint32_t green, uint32_t blue) {
	//
}

void GLCD_BTESetForegroundColor(uint32_t red, uint32_t green, uint32_t blue) {
	//
}

void GLCD_BTESetPatternNumber(uint8_t pattern) {
	//
}

void GLCD_SetTransparentColor(COLOR color) {
	BSP_LCD_SetColorKeying(BSP_LCD_GetLayer(),WRAPPER_ColorConvertion(color));
}

void GLCD_BTEStart (uint8_t source_mode, uint8_t dest_mode, uint8_t ROP, uint8_t operation) {
	//
}

void GLCD_BTEStartAndFillFromSRAM(uint8_t dest_mode, uint8_t ROP, uint8_t operation, uint32_t SRAM_Ptr, uint32_t size) {
	//
}

// Graphics widgets
void GUI_ProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t val, uint8_t maxval) {
	LEGACY_GUI_ProgressBar(x, y, w, h, val, maxval);
}

void GUI_CenterBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int val, uint32_t absolutemaxval) {
	LEGACY_GUI_CenterBar(x, y, w, h, val, absolutemaxval);
}

void GUI_CreateWindow(const char *title, COLOR background, COLOR titlebarText, COLOR titlebarBgnd) {
	LEGACY_GUI_CreateWindow(title, background, titlebarText, titlebarBgnd);
}

// Keys and potar services
KEY_STATE KEYS_GetState(KEY_ID key)  {

	return KEY_UP;
}

uint8_t POT_GetValue(POT_ID pot)  {
	uint8_t val =POT_LastVal;
	TS_StateTypeDef  TS_State;
	uint16_t ts_x, ts_y;
	uint16_t xorg, yorg, xend, yend;

	if ((POT_LastProgressBar.w != 0) || (POT_LastProgressBar.h!=0)) {

		BSP_TS_GetState(&TS_State);

		if (TS_State.touchDetected) {
			ts_x = TS_State.touchX[0];
			ts_y = TS_State.touchY[0];

			xorg = POT_LastProgressBar.x+((RK043FN48H_WIDTH-LEGACY_LCD_WIDTH)/2);
			yorg = POT_LastProgressBar.y+((RK043FN48H_HEIGHT-LEGACY_LCD_HEIGHT)/2);
			xend = xorg + POT_LastProgressBar.w;
			yend = yorg + POT_LastProgressBar.h;

			if ((ts_x >=xorg) && (ts_x <= xend)) {
				if ((ts_y >=yorg) && (ts_y <= yend)) {
					val = (ts_x-xorg*256)/POT_LastProgressBar.w;
				}
			}
		}
	}

	return val;
}

/* int16_t POT_GetValueTS(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
	int16_t val =-1;
	TS_StateTypeDef  TS_State;
	uint16_t ts_x, ts_y;
	uint16_t xorg, yorg, xend, yend;

	BSP_TS_GetState(&TS_State);

	if (TS_State.touchDetected) {
		ts_x = TS_State.touchX[0];
		ts_y = TS_State.touchY[0];

		xorg = x+((RK043FN48H_WIDTH-LEGACY_LCD_WIDTH)/2);
		yorg = y+((RK043FN48H_HEIGHT-LEGACY_LCD_HEIGHT)/2);
		xend = xorg + w;
		yend = yorg + h;

		if ((ts_x >=xorg) && (ts_x <= xend)) {
			if ((ts_y >=yorg) && (ts_y <= yend)) {
				val = (ts_x-xorg*256)/w;
			}
		}
	}

	return val;
}
 */

// Led services
void LED_Set(LED_STATE state) {
	//
}

// Random generator services
uint16_t RNG_GetValue(void) {
	return (uint16_t)(BSP_RNG_GetNumber());
}

// Sound services
void AUDIO_Start(void) {
	//
}

void AUDIO_Stop(void) {
	//
}

void AUDIO_FillBuffer(int buffer_nbr, uint8_t* buffer) {
	//
}

void AUDIO_SetEventCallback(AUDIO_EventCallback callback) {
	//
}

// Sensors services
float* L3GD20_GetGyroscopicValues (void) {
	if (BSP_GYRO_ReadValues(&ang)==ACC_OK) return (float*)&ang;
	else return val;
}

float* LSM303DLHC_GetMagneticValues (void) {
	if (BSP_MAG_ReadValues(&mag) == MAG_OK) return (float*)&mag;
	else return val;
}

float* LSM303DLHC_GetAccelerometerValues(void) {
	if (BSP_ACC_ReadValues(&acc) == ACC_OK) return (float*)&acc;
	else return val;
}

// External RAM
uint8_t SRAM_ReadByte(uint32_t addr) {
	uint8_t *p=(uint8_t*)(_legacysram_start+addr);
	return *p;
}

void SRAM_WriteByte(uint32_t addr, uint8_t data) {
	uint8_t *p=(uint8_t*)(_legacysram_start+addr);
	*p = data;
}

void SRAM_ReadBuffer(uint32_t addr, uint8_t *buffer, int length) {
	uint8_t *p=(uint8_t*)(_legacysram_start+addr);

	for (int i=0;i < length; i++)
	{
		*(buffer++)= *(p++);
	}
}

void SRAM_WriteBuffer(uint32_t addr, uint8_t *buffer, int length) {
	uint8_t *p=(uint8_t*)(_legacysram_start+addr);

	for (int i=0;i < length; i++)
	{
		*(p++) = *(buffer++);
	}
}

// Timer event managment

/**
 * @brief  This function handles TIM7 interrupt request.
 * @retval None
 */
void TIM7_IRQHandler (void)
{
	HAL_TIM_IRQHandler(&LegacyTimHandle);

	if (LegacyTimerCallback != 0x0) LegacyTimerCallback();
}

int TIMER_Start(void) {
	if (LegacyTimerCallback != 0x0) {
		/* Enable TIM7 Update interrupt */
		__HAL_TIM_ENABLE_IT(&LegacyTimHandle, TIM_IT_UPDATE);
		return 1;
	} else
		return 0;
}

void TIMER_Stop(void) {

	/* Disable TIM7 update Interrupt */
	__HAL_TIM_DISABLE_IT(&LegacyTimHandle, TIM_IT_UPDATE);
}

void TIMER_SetEventCallback(TIMER_EventCallback callback) {
	LegacyTimerCallback = callback;
}

// Soft Synthetizer
SYNTH_Status SYNTH_Start(void)  {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_Stop(void)  {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetMainVolume(int volume) {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetVolume(int channel, int volume) {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetInstrument(int channel, SYNTH_Instrument *instrument) {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_NoteOn(int channel, SYNTH_Note note) {

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_NoteOff(int channel) {

	return SYNTH_SUCCESS;
}

MELODY_Status MELODY_Start(MELODY_Notes *music, uint32_t length) {

	return MELODY_SUCCESS;
}

MELODY_Status MELODY_Stop(void) {

	return MELODY_SUCCESS;
}

MELODY_Status MELODY_GetPosition(uint8_t *pos) {

	return MELODY_SUCCESS;
}
