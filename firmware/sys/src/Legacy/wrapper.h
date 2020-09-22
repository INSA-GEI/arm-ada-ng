/*
 * wrapper.h
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */

#ifndef LEGACY_WRAPPER_H_
#define LEGACY_WRAPPER_H_

// Basic OS services
void WRAPPER_Init (void);
void API_InvalidFunction(void);
void Delay(volatile uint32_t nTime);

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
void GLCD_DrawString (uint32_t x,  uint32_t y, const char *str);
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
void GUI_CreateWindow(const char *title, COLOR background, COLOR titlebarText, COLOR titlebarBgnd);

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
uint16_t RNG_GetValue(void);

// Sound services
typedef void (*AUDIO_EventCallback)(int buffer_nbr);

void AUDIO_Start(void);
void AUDIO_Stop(void);
void AUDIO_FillBuffer(int buffer_nbr, uint8_t* buffer);
void AUDIO_SetEventCallback(AUDIO_EventCallback callback);

// Sensors services
float* L3GD20_GetGyroscopicValues (void);
float* LSM303DLHC_GetMagneticValues (void);
float* LSM303DLHC_GetAccelerometerValues(void);

// External RAM
uint8_t SRAM_ReadByte(uint32_t addr);
void SRAM_WriteByte(uint32_t addr, uint8_t data);
void SRAM_ReadBuffer(uint32_t addr, uint8_t *buffer, int length);
void SRAM_WriteBuffer(uint32_t addr, uint8_t *buffer, int length);

// Timer event managment
typedef void (*TIMER_EventCallback)(void);

int  TIMER_Start(void);
void TIMER_Stop(void);
void TIMER_SetEventCallback(TIMER_EventCallback callback);
//
//// Functions related to Synthetizer
//typedef struct {
//	uint8_t note;
//	uint8_t channel;
//	uint16_t duree;
//} MELODY_Notes;
//
//typedef struct {
//	//uint16_t instruments_length;
//	uint32_t music_length;
//	//SYNTH_Instrument **instrument;
//	//uint8_t *channels_volume;
//	MELODY_Notes *notes;
//} MELODY_Music;
//
//typedef enum MELODY_Status_ST {
//	MELODY_SUCCESS=0,
//	MELODY_ERROR
//} MELODY_Status;
//
//typedef uint8_t 	SYNTH_Wave;
//typedef uint32_t 	SYNTH_Frequencies;
//
//typedef enum SYNTH_Status_ST {
//	SYNTH_SUCCESS=0,
//	SYNTH_ERROR,
//	SYNTH_INVALID_CHANNEL,
//	SYNTH_INVALID_NOTE
//} SYNTH_Status;
//
//typedef enum SYNTH_Note_ST {
//	C0=0,C0_S,D0,D0_S,E0,F0,F0_S,G0,G0_S,A0,A0_S,B0,
//	C1,C1_S,D1,D1_S,E1,F1,F1_S,G1,G1_S,A1,A1_S,B1,
//	C2,C2_S,D2,D2_S,E2,F2,F2_S,G2,G2_S,A2,A2_S,B2,
//	C3,C3_S,D3,D3_S,E3,F3,F3_S,G3,G3_S,A3,A3_S,B3,
//	C4,C4_S,D4,D4_S,E4,F4,F4_S,G4,G4_S,A4,A4_S,B4,
//	C5,C5_S,D5,D5_S,E5,F5,F5_S,G5,G5_S,A5,A5_S,B5,
//	C6,C6_S,D6,D6_S,E6,F6,F6_S,G6,G6_S,A6,A6_S,B6,
//	C7,C7_S,D7,D7_S,E7,F7,F7_S,G7,G7_S,A7,A7_S,B7,
//	MUTE=0xFF
//} SYNTH_Note;
//
//typedef enum SYNTH_Instrument_State_ST {
//	AHDSR_IDLE=0,
//	AHDSR_ATTACK,
//	AHDSR_SUSTAIN,
//	AHDSR_DECAY,
//	AHDSR_HOLD,
//	AHDSR_RELEASE
//} SYNTH_Instrument_State;
//
//typedef struct {
//	uint32_t hold_time;
//	uint32_t sustain_time;
//	float attack_increment;
//	float decay_increment;
//	float decay_level;
//	float release_increment;
//
//	SYNTH_Wave *wavetable;
//} SYNTH_Instrument;
//
//SYNTH_Status SYNTH_Start(void);
//SYNTH_Status SYNTH_Stop(void);
//
//SYNTH_Status SYNTH_SetMainVolume(int volume);
//SYNTH_Status SYNTH_SetVolume(int channel, int volume);
//SYNTH_Status SYNTH_SetInstrument(int channel, SYNTH_Instrument *instrument);
//SYNTH_Status SYNTH_NoteOn(int channel, SYNTH_Note note);
//SYNTH_Status SYNTH_NoteOff(int channel);
//
//MELODY_Status MELODY_Start(MELODY_Notes *music, uint32_t length);
//MELODY_Status MELODY_Stop(void);
//MELODY_Status MELODY_GetPosition(uint8_t *pos);

#endif /* LEGACY_WRAPPER_H_ */
