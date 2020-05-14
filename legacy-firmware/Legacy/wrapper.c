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
#include "audio-synth/audio.h"
#include "audio-synth/audio-synth.h"
#include "audio-synth/audio-melody.h"

#include <math.h>

#define LEGACY_LCD_WIDTH 	320
#define LEGACY_LCD_HEIGHT	240

ALIGN_32BYTES (AUDIO_BufferTypeDef  AUDIO_Buffer);// __attribute__((section("DMA_BUFFERS")));
AUDIO_EventCallback AUDIO_Callback;

#define HORIZONTAL_COORD_CONVERSION(x) (((RK043FN48H_WIDTH-LEGACY_LCD_WIDTH)/2)+x)
#define VERTICAL_COORD_CONVERSION(y) (((RK043FN48H_HEIGHT-LEGACY_LCD_HEIGHT)/2)+y)

#define ABS(x) (x>=0 ? x: -x)
uint32_t WRAPPER_ColorConvertion_32bpp (COLOR color);
uint16_t WRAPPER_ColorConvertion_16bpp (COLOR color);

extern const uint32_t _legacysram_start; // Define allocated sram block used to simulate external ram in legacy system

float val[3]={0.0,0.0,0.0};
acceleration_t acc;
magnetic_t mag;
angularRate_t ang;

TIM_HandleTypeDef LegacyTimHandle;
TIMER_EventCallback LegacyTimerCallback=0x0;

uint8_t POT_LastVal;
MELODY_Status MELODY_Init(void);

/**
 * Init function for legacy wrapper, in charge of initializing Timer 7, for example
 */
void WRAPPER_Init (void) {
	RCC_ClkInitTypeDef    clkconfig;
	uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
	uint32_t              uwPrescalerValue = 0U;
	uint32_t              pFLatency;
	uint8_t  			  status = 0;

	/* Configure the TIM7 IRQ priority */
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

	/* Init du Touchscreen */
	status = BSP_TS_Init(BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
	if (status != TS_OK) {
		while (1);
	}

	/* Init audio */
	AUDIO_Callback =0x0;
	AUDIO_Init();

	/* Init Melody timer */
	MELODY_Init();

	POT_LastVal=1;
}

uint32_t WRAPPER_ColorConvertion_32bpp (COLOR color) {
	uint32_t val;

	if (color == 0xFF) val = 0xFFFFFFFF;
	else
	{
		/* Convertion 3:3:2 to 8:8:8:8 */
		val = (uint32_t)0xFF000000 | (((uint32_t)(color&0xE0))<<16) | (((uint32_t)(color&0x1C))<<11) | (((uint32_t)(color&0x03))<<6);
	}

	return val;
}

uint16_t WRAPPER_ColorConvertion_16bpp (COLOR color) {
	uint16_t val;

	if (color == 0xFF) val = 0xFFFF;
	else
	{
		/* Convertion 3:3:2 to 5:6:5 */
		val = (((uint16_t)(color&0xE0))<<8) | (((uint16_t)(color&0x1C))<<6) | (((uint16_t)(color&0x03))<<3);
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
	uint32_t color_save;

	/* sauvegarde la couleur en cours: GLCD_Clear ne modifie pas la couleur de premier plan */
	color_save=BSP_LCD_GetTextColor();

	BSP_LCD_SetTextColor(WRAPPER_ColorConvertion_32bpp(color));
	GLCD_DrawFillRectangle (0, 0, 320-1, 240-1);

	/* Restaure la couleur de premier plan */
	BSP_LCD_SetTextColor(color_save);
}

void GLCD_SetTextColor (COLOR color) {
	BSP_LCD_SetTextColor(WRAPPER_ColorConvertion_32bpp(color));
}

void GLCD_SetBackColor (COLOR color) {
	BSP_LCD_SetBackColor(WRAPPER_ColorConvertion_32bpp(color));
}

void GLCD_PutPixel (uint32_t x, uint32_t y, COLOR color) {
	BSP_LCD_DrawPixel(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y),WRAPPER_ColorConvertion_16bpp(color));
}

void GLCD_DrawChar (uint32_t x,  uint32_t y, uint8_t c) {
	uint8_t str[2] = {c, 0};
	uint32_t col,row;

	if (x>((320/8)-1)) x= ((320/8)-1);
	if (y>((240/16)-1)) y= ((240/16)-1);

	col = x*8;
	row = (y*16)-1;

	BSP_LCD_SetFont(&FontLegacy);
	BSP_LCD_DisplayStringAt(HORIZONTAL_COORD_CONVERSION(col),VERTICAL_COORD_CONVERSION(row), (uint8_t *)str, LEFT_MODE);
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
	BSP_LCD_DrawRect(HORIZONTAL_COORD_CONVERSION(x1),VERTICAL_COORD_CONVERSION(y1), ABS(x2-x1)+1, ABS(y2-y1)+1);
}

void GLCD_DrawFillRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {
	BSP_LCD_FillRect(HORIZONTAL_COORD_CONVERSION(x1),VERTICAL_COORD_CONVERSION(y1), ABS(x2-x1)+1, ABS(y2-y1)+1);
}

void GLCD_DrawCircle (uint32_t x, uint32_t y, uint32_t radius) {
	BSP_LCD_DrawCircle(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y), radius);
}

void GLCD_DrawFillCircle (uint32_t x, uint32_t y, uint32_t radius) {
	BSP_LCD_FillCircle(HORIZONTAL_COORD_CONVERSION(x),VERTICAL_COORD_CONVERSION(y), radius);
}

void GLCD_DrawImage (COLOR* data, uint32_t x, uint32_t y, uint32_t w, int32_t h) {
	uint32_t counter_x, counter_y=0;

	for (counter_y=0; counter_y<h; counter_y++)
	{
		for (counter_x=0; counter_x<w; counter_x++)
		{
			GLCD_PutPixel(x+counter_x, y+counter_y, data[(counter_y*w)+counter_x]);
		}
	}
}

// Second set of function for GLCD
void GLCD_DrawImagefromSRAM (uint32_t SRAM_Ptr, uint32_t x, uint32_t y, uint32_t w, int32_t h) {
	uint32_t counter_x, counter_y=0;

	for (counter_y=0; counter_y<h; counter_y++)
	{
		for (counter_x=0; counter_x<w; counter_x++)
		{
			GLCD_PutPixel(x+counter_x, y+counter_y, (COLOR)SRAM_ReadByte(SRAM_Ptr + (counter_y*w) + counter_x));
		}
	}
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
	//	BSP_LCD_SetTransparency(LTDC_BACKGROUND_LAYER, 100-layer2_trans);
	//	BSP_LCD_SetTransparency(LTDC_FOREGROUND_LAYER, 100-layer1_trans);
}

void GLCD_SetLayer(uint8_t layerNbr) {
	//	if (layerNbr==0) BSP_LCD_SelectLayer(LTDC_FOREGROUND_LAYER);
	//	else if (layerNbr==1) BSP_LCD_SelectLayer(LTDC_BACKGROUND_LAYER);
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
	//	BSP_LCD_SetColorKeying(BSP_LCD_GetLayer(),WRAPPER_ColorConvertion_32bpp(color));
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
	KEY_STATE state=KEY_RELEASED;

	switch (key)
	{
	case KEY_A:
		if (BSP_PB_GetState(BUTTON_A)) state = KEY_PRESSED;
		break;
	case KEY_B:
		if (BSP_PB_GetState(BUTTON_B)) state = KEY_PRESSED;
		break;
	case KEY_CENTER:
		if (BSP_PB_GetState(BUTTON_Y)) state = KEY_PRESSED;
		break;
	case KEY_UP:
		if (BSP_PB_GetState(BUTTON_UP)) state = KEY_PRESSED;
		break;
	case KEY_DOWN:
		if (BSP_PB_GetState(BUTTON_DOWN)) state = KEY_PRESSED;
		break;
	case KEY_RIGHT:
		if (BSP_PB_GetState(BUTTON_RIGHT)) state = KEY_PRESSED;
		break;
	case KEY_LEFT:
		if (BSP_PB_GetState(BUTTON_LEFT)) state = KEY_PRESSED;
		break;
	case KEY_LEFT_UP:
		if (BSP_PB_GetState(BUTTON_UP) && BSP_PB_GetState(BUTTON_LEFT)) state = KEY_PRESSED;
		break;
	case KEY_RIGHT_UP:
		if (BSP_PB_GetState(BUTTON_UP) && BSP_PB_GetState(BUTTON_RIGHT)) state = KEY_PRESSED;
		break;
	case KEY_LEFT_DOWN:
		if (BSP_PB_GetState(BUTTON_DOWN) && BSP_PB_GetState(BUTTON_LEFT)) state = KEY_PRESSED;
		break;
	case KEY_RIGHT_DOWN:
		if (BSP_PB_GetState(BUTTON_DOWN) && BSP_PB_GetState(BUTTON_RIGHT)) state = KEY_PRESSED;
		break;
	case KEY_SYSTEM:
		if (BSP_PB_GetState(BUTTON_X)) state = KEY_PRESSED;
		break;
	default:
		break;
	}

	return state;
}

uint8_t POT_GetValue(POT_ID pot)  {
	TS_StateTypeDef  TS_State;
	uint16_t ts_x;

	BSP_TS_GetState(&TS_State);

	if (TS_State.touchDetected) {
		ts_x = TS_State.touchX[0];

		if (ts_x<=HORIZONTAL_COORD_CONVERSION(50)) POT_LastVal=0;
		else if (ts_x>=HORIZONTAL_COORD_CONVERSION(270)) POT_LastVal=255;
		else {
			POT_LastVal = ((ts_x-HORIZONTAL_COORD_CONVERSION(50))*255)/(HORIZONTAL_COORD_CONVERSION(270)-HORIZONTAL_COORD_CONVERSION(50));
		}
	}

	if (POT_LastVal ==0) POT_LastVal=1;

	return POT_LastVal;
}

// Led services
void LED_Set(LED_STATE state) {
	//
}

// Random generator services
uint16_t RNG_GetValue(void) {
	return (uint16_t)(BSP_RNG_GetNumber());
}

// Sound services
void AUDIO_Init(void) {
	uint32_t freq=44100;

	BSP_AUDIO_OUT_DeInit();
	BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_BOTH, 92, freq);
}

void AUDIO_Start(void) {
	/* Clean Data Cache to update the content of the SRAM */
	SCB_CleanDCache_by_Addr((uint32_t*)&AUDIO_Buffer.buffer1[0], AUDIO_BUFFER_SIZE*8);

	BSP_AUDIO_OUT_Play((uint16_t*)&AUDIO_Buffer.buffer1[0], AUDIO_BUFFER_SIZE*8);
}

void AUDIO_Stop(void) {
	BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
}

void AUDIO_FillBuffer(int buffer_nbr, uint8_t* buffer) {
	int i;
	int16_t *ptr;
	int16_t tmp;

	if (buffer_nbr == 1) ptr = &AUDIO_Buffer.buffer1[0];
	else ptr =  &AUDIO_Buffer.buffer2[0];

	for (i=0; i<AUDIO_BUFFER_SIZE; i++)
	{
		tmp = buffer[i];
		tmp = tmp -128;
		tmp = tmp *256;

		*ptr=tmp;
		ptr++;
		*ptr=tmp;
		ptr++;
	}

	if (buffer_nbr == 1) SCB_CleanDCache_by_Addr((uint32_t*)&AUDIO_Buffer.buffer1[0], AUDIO_BUFFER_SIZE*4);
	else SCB_CleanDCache_by_Addr((uint32_t*)&AUDIO_Buffer.buffer2[0], AUDIO_BUFFER_SIZE*4);
}

void AUDIO_FillBuffer16(int buffer_nbr, int16_t* buffer) {
	int i;
	int16_t *ptr;

	if (buffer_nbr == 1) ptr = &AUDIO_Buffer.buffer1[0];
	else ptr =  &AUDIO_Buffer.buffer2[0];

	for (i=0; i<AUDIO_BUFFER_SIZE; i++)
	{
		*ptr=buffer[i];
		ptr++;
		*ptr=buffer[i];
		ptr++;
	}

	if (buffer_nbr == 1) SCB_CleanDCache_by_Addr((uint32_t*)&AUDIO_Buffer.buffer1[0], AUDIO_BUFFER_SIZE*4);
	else SCB_CleanDCache_by_Addr((uint32_t*)&AUDIO_Buffer.buffer2[0], AUDIO_BUFFER_SIZE*4);
}

void AUDIO_SetEventCallback(AUDIO_EventCallback callback) {
	if (callback != 0x00)
	{
		AUDIO_Callback= callback;
	}
}

/**
 * @brief  Manages the full Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
	if (AUDIO_Callback != 0x00)
	{
		AUDIO_Callback(2);
	}
}

/**
 * @brief  Manages the DMA Half Transfer complete event.
 * @param  None
 * @retval None
 */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{
	if (AUDIO_Callback != 0x00)
	{
		AUDIO_Callback(1);
	}
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
	float tmp;
	//	char str[20];
	//	volatile int val;

	HAL_Delay(25);

	while (BSP_ACC_ReadValues(&acc) != ACC_OK) {
	}

	//	val = (int)acc.x;
	//	sprintf (str, "X= %i     ", val);
	//	GLCD_DrawString(1,13, str);
	//
	//	val = (int)acc.y;
	//	sprintf (str, "Y= %i     ", val);
	//	GLCD_DrawString(1,14, str);

	// invert X and Y
	tmp = -acc.y;
	acc.y=acc.x;
	acc.x=tmp;

	return (float*)&acc;
}

// External RAM
uint8_t SRAM_ReadByte(uint32_t addr) {
	uint8_t *p=(uint8_t*)(&_legacysram_start);
	p+=addr;
	return *p;
}

void SRAM_WriteByte(uint32_t addr, uint8_t data) {
	uint8_t *p=(uint8_t*)(&_legacysram_start);
	p+=addr;
	*p = data;
}

void SRAM_ReadBuffer(uint32_t addr, uint8_t *buffer, int length) {
	uint8_t *p=(uint8_t*)(&_legacysram_start);
	p+=addr;

	for (int i=0;i < length; i++)
	{
		*(buffer++)= *(p++);
	}
}

void SRAM_WriteBuffer(uint32_t addr, uint8_t *buffer, int length) {
	uint8_t *p=(uint8_t*)(&_legacysram_start);
	p+=addr;

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
//
//// Soft Synthetizer
//SYNTH_Status SYNTH_Start(void)  {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_Stop(void)  {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_SetMainVolume(int volume) {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_SetVolume(int channel, int volume) {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_SetInstrument(int channel, SYNTH_Instrument *instrument) {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_NoteOn(int channel, SYNTH_Note note) {
//
//	return SYNTH_SUCCESS;
//}
//
//SYNTH_Status SYNTH_NoteOff(int channel) {
//
//	return SYNTH_SUCCESS;
//}
//
//MELODY_Status MELODY_Start(MELODY_Notes *music, uint32_t length) {
//
//	return MELODY_SUCCESS;
//}
//
//MELODY_Status MELODY_Stop(void) {
//
//	return MELODY_SUCCESS;
//}
//
//MELODY_Status MELODY_GetPosition(uint8_t *pos) {
//
//	return MELODY_SUCCESS;
//}
