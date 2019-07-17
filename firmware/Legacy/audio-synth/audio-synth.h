/******************************************************************************/
/* AudioSynth.h: header for sound synthetizer                                 */
/*                                                                            */
/******************************************************************************/
/* This program is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    This program is distributed in the hope that it will be useful,         */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>.   */
/******************************************************************************/

#ifndef __AUDIOSYNTH_H__
#define __AUDIOSYNTH_H__

//#include "stm32f30x.h"
#include "stm32746g_discovery.h"

//typedef int16_t 	SYNTH_Wave;
typedef uint8_t 	SYNTH_Wave;
typedef uint32_t 	SYNTH_Frequencies;

typedef enum SYNTH_Status_ST {
	SYNTH_SUCCESS=0,
	SYNTH_ERROR,
	SYNTH_INVALID_CHANNEL,
	SYNTH_INVALID_NOTE
} SYNTH_Status;

typedef enum SYNTH_Note_ST {
	C0=0,C0_S,D0,D0_S,E0,F0,F0_S,G0,G0_S,A0,A0_S,B0,
	C1,C1_S,D1,D1_S,E1,F1,F1_S,G1,G1_S,A1,A1_S,B1,
	C2,C2_S,D2,D2_S,E2,F2,F2_S,G2,G2_S,A2,A2_S,B2,
	C3,C3_S,D3,D3_S,E3,F3,F3_S,G3,G3_S,A3,A3_S,B3,
	C4,C4_S,D4,D4_S,E4,F4,F4_S,G4,G4_S,A4,A4_S,B4,
	C5,C5_S,D5,D5_S,E5,F5,F5_S,G5,G5_S,A5,A5_S,B5,
	C6,C6_S,D6,D6_S,E6,F6,F6_S,G6,G6_S,A6,A6_S,B6,
	C7,C7_S,D7,D7_S,E7,F7,F7_S,G7,G7_S,A7,A7_S,B7,
	MUTE=0xFF
} SYNTH_Note;

typedef enum SYNTH_Instrument_State_ST {
	AHDSR_IDLE=0,
	AHDSR_ATTACK,
	AHDSR_SUSTAIN,
	AHDSR_DECAY,
	AHDSR_HOLD,
	AHDSR_RELEASE
} SYNTH_Instrument_State;

typedef struct {
	uint32_t hold_time;
	uint32_t sustain_time;
	float attack_increment;
	float decay_increment;
	float decay_level;
	float release_increment;

	SYNTH_Wave *wavetable;
} SYNTH_Instrument;

#define SYNTH_ChannelsNbr 4

#include "audio-synth-const-16.h"

//SYNTH_Status SYNTH_Init(void);
SYNTH_Status SYNTH_Start(void);
SYNTH_Status SYNTH_Stop(void);

SYNTH_Status SYNTH_SetMainVolume(int volume);
SYNTH_Status SYNTH_SetVolume(int channel, int volume);
SYNTH_Status SYNTH_SetInstrument(int channel, SYNTH_Instrument *instrument);
SYNTH_Status SYNTH_NoteOn(int channel, SYNTH_Note note);
SYNTH_Status SYNTH_NoteOff(int channel);

#endif /* __AUDIOSYNTH_H__ */
