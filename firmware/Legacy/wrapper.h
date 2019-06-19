/*
 * wrapper.h
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */

#ifndef LEGACY_WRAPPER_H_
#define LEGACY_WRAPPER_H_

// Basic OS services
void API_InvalidFunction(void);
void Delay(__IO uint32_t nTime);

// Graphics services
#define Black           0x00      /*   0,   0,   0 */
#define Navy            0x01      /*   0,   0, 1 */
#define DarkGreen       0x0C      /*   0, 3,   0 */
#define DarkCyan        0x0D      /*   0, 3, 1 */
#define Maroon          0x60      /* 3,   0,   0 */
#define Purple          0x61      /* 3,   0, 1 */
#define Olive           0x6C      /* 3, 3,   0 */
#define LightGrey       0xB5      /* 5, 5, 2 */
#define DarkGrey        0x6D      /* 3, 3, 1 */
#define Blue            0x03      /*   0,   0, 3 */
#define Green           0x1C      /*   0, 7,   0 */
#define Cyan            0x1F      /*   0, 7, 3 */
#define Red             0xE0      /* 7,   0,   0 */
#define Magenta         0xE3      /* 7,   0, 3 */
#define Yellow          0xFC      /* 7, 7, 0   */
#define White           0xFF      /* 7, 7, 3 */

typedef uint8_t COLOR;
struct FONT_ST
{
	uint32_t height;
	uint32_t width;
	uint8_t data;
};

typedef struct FONT_ST FONT;

#define GLCD_MAX_COLUMN	(320/8)
#define GLCD_MAX_ROW	(240/16)

#define GLCD_LAYER1 0
#define GLCD_LAYER2 1

#define GLCD_LAYER_SCROLL_BOTH	  0
#define GLCD_LAYER_SCROLL_LAYER1	1
#define GLCD_LAYER_SCROLL_LAYER2	2

#define GLCD_LAYER_DISPLAY_LAYER1 0
#define GLCD_LAYER_DISPLAY_LAYER2 1
#define GLCD_LAYER_DISPLAY_LIGHTEN 2
#define GLCD_LAYER_DISPLAY_TRANSPARENT 3
#define GLCD_LAYER_DISPLAY_OR 		4
#define GLCD_LAYER_DISPLAY_AND 		5

#define GLCD_LAYER_TRANSPARENT_TOTAL 0
#define GLCD_LAYER_TRANSPARENT_7_8 1
#define GLCD_LAYER_TRANSPARENT_3_4 2
#define GLCD_LAYER_TRANSPARENT_5_8 3
#define GLCD_LAYER_TRANSPARENT_1_2 4
#define GLCD_LAYER_TRANSPARENT_3_8 5
#define GLCD_LAYER_TRANSPARENT_1_4 6
#define GLCD_LAYER_TRANSPARENT_1_8 7
#define GLCD_LAYER_TRANSPARENT_DISABLE 8

#define GLCD_BTE_OPERATION_0 0x0
#define GLCD_BTE_OPERATION_1 0x1
#define GLCD_BTE_OPERATION_2 0x2
#define GLCD_BTE_OPERATION_3 0x3
#define GLCD_BTE_OPERATION_4 0x4
#define GLCD_BTE_OPERATION_5 0x5
#define GLCD_BTE_OPERATION_6 0x6
#define GLCD_BTE_OPERATION_7 0x7
#define GLCD_BTE_OPERATION_8 0x8
#define GLCD_BTE_OPERATION_9 0x9
#define GLCD_BTE_OPERATION_10 0xA
#define GLCD_BTE_OPERATION_11 0xB
#define GLCD_BTE_OPERATION_12 0xC

#define GLCD_ROP_FUNCTION_0 0x0
#define GLCD_ROP_FUNCTION_1 0x1
#define GLCD_ROP_FUNCTION_2 0x2
#define GLCD_ROP_FUNCTION_3 0x3
#define GLCD_ROP_FUNCTION_4 0x4
#define GLCD_ROP_FUNCTION_5 0x5
#define GLCD_ROP_FUNCTION_6 0x6
#define GLCD_ROP_FUNCTION_7 0x7
#define GLCD_ROP_FUNCTION_8 0x8
#define GLCD_ROP_FUNCTION_9 0x9
#define GLCD_ROP_FUNCTION_10 0xA
#define GLCD_ROP_FUNCTION_11 0xB
#define GLCD_ROP_FUNCTION_12 0xC
#define GLCD_ROP_FUNCTION_13 0xD
#define GLCD_ROP_FUNCTION_14 0xE
#define GLCD_ROP_FUNCTION_15 0xF

void GLCD_Clear (COLOR color);
void GLCD_SetTextColor (COLOR color);
void GLCD_SetBackColor (COLOR color);
void GLCD_PutPixel (uint32_t x, uint32_t y, COLOR color);
void GLCD_DrawChar (uint32_t x,  uint32_t y, uint8_t c);
void GLCD_DrawADAString (uint32_t x, uint32_t y, uint32_t len, const char *str);
void GLCD_DrawLine (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void GLCD_DrawRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void GLCD_DrawFillRectangle (uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
void GLCD_DrawCircle (uint32_t x, uint32_t y, uint32_t radius);
void GLCD_DrawFillCircle (uint32_t x, uint32_t y, uint32_t radius);
void GLCD_DrawImage (COLOR* data, uint32_t x, uint32_t y, uint32_t w, int32_t h);

// Second set of function for GLCD
void GLCD_DrawImagefromSRAM (uint32_t SRAM_Ptr, uint32_t x, uint32_t y, uint32_t w, int32_t h);
void GLCD_LayerScrollMode(uint8_t mode);
void GLCD_SetScrollWindow (uint32_t x, uint32_t y, uint32_t w, uint32_t h);
void GLCD_ScrollVertical (uint32_t dy);
void GLCD_ScrollHorizontal (uint32_t dy);
void GLCD_LayerDisplayMode(uint8_t mode);
void GLCD_LayerTransparency(uint8_t layer1_trans, uint8_t layer2_trans);
void GLCD_SetLayer(uint8_t layerNbr);
void GLCD_BTESetSource(uint32_t X, uint32_t Y, uint8_t layer);
void GLCD_BTESetDestination(uint32_t X, uint32_t Y, uint8_t layer);
void GLCD_BTESetSize(uint32_t width, uint32_t height);
void GLCD_BTESetBackgroundColor(uint32_t red, uint32_t green, uint32_t blue);
void GLCD_BTESetForegroundColor(uint32_t red, uint32_t green, uint32_t blue);
void GLCD_BTESetPatternNumber(uint8_t pattern);
void GLCD_SetTransparentColor(COLOR color);
void GLCD_BTEStart (uint8_t source_mode, uint8_t dest_mode, uint8_t ROP, uint8_t operation);
void GLCD_BTEStartAndFillFromSRAM(uint8_t dest_mode, uint8_t ROP, uint8_t operation, uint32_t SRAM_Ptr, uint32_t size);

// Graphics widgets
void GUI_ProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t val, uint8_t maxval);
void GUI_CenterBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int val, uint32_t absolutemaxval);

// Keys and potar services
enum KEY_ID_ENUM
{
	KEY_A=0,
	KEY_B,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_CENTER,
	KEY_RIGHT,
	KEY_LEFT_UP,
	KEY_LEFT_DOWN,
	KEY_RIGHT_UP,
	KEY_RIGHT_DOWN,
	KEY_SYSTEM
};

enum KEY_STATE_ENUM
{
	KEY_RELEASED=0,
	KEY_PRESSED
};

typedef enum KEY_ID_ENUM KEY_ID;
typedef enum KEY_STATE_ENUM KEY_STATE;

KEY_STATE KEYS_GetState(KEY_ID key);

enum POT_ID_ENUM
{
	POT_LEFT=0,
	POT_RIGHT
};

typedef enum POT_ID_ENUM POT_ID;

uint8_t POT_GetValue(POT_ID pot);

// Led services
enum LED_STATE_ENUM
{
	LED_OFF=0,
	LED_ON
};

typedef enum LED_STATE_ENUM LED_STATE;

void LED_Set(LED_STATE state);

// Random generator services
        .word   RNG_GetValue

// Sound services
        .word	AUDIO_Start
        .word	AUDIO_Stop
        .word	AUDIO_FillBuffer
        .word	AUDIO_SetEventCallback

// Sensors services
		.word	L3GD20_GetGyroscopicValues
		.word	LSM303DLHC_GetMagneticValues
		.word	LSM303DLHC_GetAccelerometerValues

// External RAM
		.word 	SRAM_ReadByte
		.word	SRAM_WriteByte
		.word	SRAM_ReadBuffer
		.word	SRAM_WriteBuffer

// Timer event managment
		.word 	TIMER_Start
		.word  	TIMER_Stop
		.word  	TIMER_SetEventCallback

// Functions related to Synthetizer
		.word 	SYNTH_Start
		.word 	SYNTH_Stop

		.word 	SYNTH_SetMainVolume
		.word 	SYNTH_SetVolume
		.word 	SYNTH_SetInstrument
		.word 	SYNTH_NoteOn
		.word 	SYNTH_NoteOff

		.word 	MELODY_Start
		.word 	MELODY_Stop
		.word 	MELODY_GetPosition



#endif /* LEGACY_WRAPPER_H_ */
