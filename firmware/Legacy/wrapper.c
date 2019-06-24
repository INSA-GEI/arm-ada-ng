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

// Basic OS services
void API_InvalidFunction(void) {
	while (1);
}

void Delay(volatile uint32_t nTime) {
	HAL_Delay(nTime);
}

void GLCD_Clear (COLOR color) {

}

void GLCD_SetTextColor (COLOR color) {

}

void GLCD_SetBackColor (COLOR color) {

}

void GLCD_PutPixel (uint32_t x, uint32_t y, COLOR color) {

}

void GLCD_DrawChar (uint32_t x,  uint32_t y, uint8_t c) {

}

void GLCD_DrawString (uint32_t x,  uint32_t y, const char *str) {

}

void GLCD_DrawADAString (uint32_t x, uint32_t y, uint32_t len, const char *str) {

}

void GLCD_DrawLine (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {

}

void GLCD_DrawRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {

}

void GLCD_DrawFillRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2) {

}

void GLCD_DrawCircle (uint32_t x, uint32_t y, uint32_t radius) {

}

void GLCD_DrawFillCircle (uint32_t x, uint32_t y, uint32_t radius) {

}

void GLCD_DrawImage (COLOR* data, uint32_t x, uint32_t y, uint32_t w, int32_t h) {

}

// Second set of function for GLCD
void GLCD_DrawImagefromSRAM (uint32_t SRAM_Ptr, uint32_t x, uint32_t y, uint32_t w, int32_t h) {

}

void GLCD_LayerScrollMode(uint8_t mode) {

}

void GLCD_SetScrollWindow (uint32_t x, uint32_t y, uint32_t w, uint32_t h) {

}

void GLCD_ScrollVertical (uint32_t dy) {

}

void GLCD_ScrollHorizontal (uint32_t dy) {

}

void GLCD_LayerDisplayMode(uint8_t mode) {

}

void GLCD_LayerTransparency(uint8_t layer1_trans, uint8_t layer2_trans) {

}

void GLCD_SetLayer(uint8_t layerNbr) {

}

void GLCD_BTESetSource(uint32_t X, uint32_t Y, uint8_t layer) {

}

void GLCD_BTESetDestination(uint32_t X, uint32_t Y, uint8_t layer) {

}

void GLCD_BTESetSize(uint32_t width, uint32_t height) {

}

void GLCD_BTESetBackgroundColor(uint32_t red, uint32_t green, uint32_t blue) {

}

void GLCD_BTESetForegroundColor(uint32_t red, uint32_t green, uint32_t blue) {

}

void GLCD_BTESetPatternNumber(uint8_t pattern) {

}

void GLCD_SetTransparentColor(COLOR color) {

}

void GLCD_BTEStart (uint8_t source_mode, uint8_t dest_mode, uint8_t ROP, uint8_t operation) {

}

void GLCD_BTEStartAndFillFromSRAM(uint8_t dest_mode, uint8_t ROP, uint8_t operation, uint32_t SRAM_Ptr, uint32_t size) {

}


// Graphics widgets
void GUI_ProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t val, uint8_t maxval) {

}

void GUI_CenterBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int val, uint32_t absolutemaxval) {

}

void GUI_CreateWindow(const char *title, COLOR background, COLOR titlebarText, COLOR titlebarBgnd) {

}

// Keys and potar services
KEY_STATE KEYS_GetState(KEY_ID key)  {

	return KEY_UP;
}

uint8_t POT_GetValue(POT_ID pot)  {

	return 0;
}

// Led services
void LED_Set(LED_STATE state) {

}


// Random generator services
uint16_t RNG_GetValue(void) {

	return (uint16_t)(BSP_RNG_GetNumber());
}

// Sound services
void AUDIO_Start(void) {

}

void AUDIO_Stop(void) {

}

void AUDIO_FillBuffer(int buffer_nbr, uint8_t* buffer) {

}

void AUDIO_SetEventCallback(AUDIO_EventCallback callback) {

}

// Sensors services
float val[3]={0.0,0.0,0.0};

float* L3GD20_GetGyroscopicValues (void) {

	return val;
}

float* LSM303DLHC_GetMagneticValues (void) {

	return val;
}

float* LSM303DLHC_GetAccelerometerValues(void) {

	return val;
}

// External RAM
uint8_t SRAM_ReadByte(uint32_t addr) {

	return 0;
}

void SRAM_WriteByte(uint32_t addr, uint8_t data) {

}

void SRAM_ReadBuffer(uint32_t addr, uint8_t *buffer, int length) {

}

void SRAM_WriteBuffer(uint32_t addr, uint8_t *buffer, int length) {

}

// Timer event managment
int  TIMER_Start(void) {

	return 1;
}

void TIMER_Stop(void) {

}

void TIMER_SetEventCallback(TIMER_EventCallback callback) {

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
