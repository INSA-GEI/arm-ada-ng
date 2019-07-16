/*
 * audio-melody.h
 *
 *  Created on: 9 nov. 2017
 *      Author: dimercur
 */

#ifndef AUDIO_MELODY_H_
#define AUDIO_MELODY_H_

#include "audio-synth.h"

typedef struct {
	uint8_t note;
	uint8_t channel;
	uint16_t duree;
} MELODY_Notes;

typedef struct {
	//uint16_t instruments_length;
	uint32_t music_length;
	//SYNTH_Instrument **instrument;
	//uint8_t *channels_volume;
	MELODY_Notes *notes;
} MELODY_Music;

typedef enum MELODY_Status_ST {
	MELODY_SUCCESS=0,
	MELODY_ERROR
} MELODY_Status;

MELODY_Status MELODY_Init(void);
MELODY_Status MELODY_Start(MELODY_Notes *music, uint32_t length);
MELODY_Status MELODY_Stop(void);
MELODY_Status MELODY_GetPosition(uint8_t *pos);

#endif /* AUDIO_MELODY_H_ */
