/******************************************************************************/
/* AudioSynth.c: Sound synthetizer                                            */
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

#include "audio-synth.h"
#include "audio.h"
#include "audio-synth-const.h"

typedef struct {
	SYNTH_Instrument *instrument;

	// Partie table d'onde (wavetable)
	SYNTH_Note 	note;
	float 		counter;
	float 		increment;
	uint8_t 	volume;

	// Partie AHDSR
	uint32_t 	AHDSR_counter;
	float 	 	AHDSR_increment;
	uint8_t  	AHDSR_level;
	SYNTH_Instrument_State AHDSR_state;
} SYNTH_Channel;

SYNTH_Channel SYNTH_Channels[SYNTH_ChannelsNbr];

uint8_t SYNTH_MainVolume;

static void SYNTH_AudioCallback(int buffer_nbr);
static void SYNTH_FillBuffer(int buffer_nbr, SYNTH_Channel *channels);

//int16_t SYNTH_LocalBuffer[AUDIO_BUFFER_SIZE];
uint8_t SYNTH_LocalBuffer[AUDIO_BUFFER_SIZE];

SYNTH_Status SYNTH_Start(void) {
	int i;

	AUDIO_Stop();

	AUDIO_SetEventCallback(SYNTH_AudioCallback);
	//SYNTH_Buffer_1 = AUDIO_Buffer.buffer1;
	//SYNTH_Buffer_2 = AUDIO_Buffer.buffer2;
	//SYNTH_Buffer_1 = AUDIO_Buffer.buffer1;
	//SYNTH_Buffer_2 = AUDIO_Buffer.buffer2;

	for (i=0; i<SYNTH_ChannelsNbr; i++)
	{
		SYNTH_Channels[i].counter=0.0f;
		SYNTH_Channels[i].increment=0.0f;
		SYNTH_Channels[i].volume=0;
		SYNTH_Channels[i].note = MUTE;
		SYNTH_Channels[i].instrument = (SYNTH_Instrument*)&SYNTH_Inst_Piano;
		SYNTH_Channels[i].AHDSR_state = AHDSR_IDLE;
	}

	SYNTH_FillBuffer(1, SYNTH_Channels);
	SYNTH_FillBuffer(2, SYNTH_Channels);

	AUDIO_Start();
	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_Stop(void) {
	int i;

	AUDIO_Stop();

	AUDIO_SetEventCallback((AUDIO_EventCallback)0x0);

	for (i=0; i<SYNTH_ChannelsNbr; i++)
	{
		SYNTH_Channels[i].counter=0.0f;
		SYNTH_Channels[i].increment=0.0f;
		SYNTH_Channels[i].volume=0;
		SYNTH_Channels[i].note = MUTE;
		SYNTH_Channels[i].instrument = (SYNTH_Instrument*)&SYNTH_Inst_Piano;
		SYNTH_Channels[i].AHDSR_state = AHDSR_IDLE;
	}

	SYNTH_FillBuffer(1, SYNTH_Channels);
	SYNTH_FillBuffer(2, SYNTH_Channels);

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetMainVolume(int volume) {

	SYNTH_MainVolume = volume;

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetVolume(int channel, int volume) {
	if ((channel <0) || (channel >= SYNTH_ChannelsNbr)) return SYNTH_INVALID_CHANNEL;

	SYNTH_Channels[channel].volume=volume;
	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_SetInstrument(int channel, SYNTH_Instrument *instrument) {
	if ((channel <0) || (channel >= SYNTH_ChannelsNbr)) return SYNTH_INVALID_CHANNEL;

	SYNTH_Channels[channel].instrument=instrument;
	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_NoteOn(int channel, SYNTH_Note note) {
	if ((channel <0) || (channel >= SYNTH_ChannelsNbr)) return SYNTH_INVALID_CHANNEL;
	if (note!=MUTE)
	{
		if ((note<C0) || (note>=B7)) return SYNTH_INVALID_NOTE;
	}

	if (note != MUTE) {
		SYNTH_Channels[channel].note = note;
		SYNTH_Channels[channel].increment = ((55.0f/44100.0f)*SYNTH_NoteFrequencies[note])/100;
		SYNTH_Channels[channel].counter = 0.0f;
		SYNTH_Channels[channel].AHDSR_state = AHDSR_ATTACK;
		SYNTH_Channels[channel].AHDSR_counter = 0;
		SYNTH_Channels[channel].AHDSR_increment=0.0f;
		SYNTH_Channels[channel].AHDSR_level=0;
	}
	else {
		SYNTH_Channels[channel].increment = 0.0f;
		SYNTH_Channels[channel].AHDSR_state = AHDSR_IDLE;
	}

	return SYNTH_SUCCESS;
}

SYNTH_Status SYNTH_NoteOff(int channel)
{
	if ((channel <0) || (channel >= SYNTH_ChannelsNbr)) return SYNTH_INVALID_CHANNEL;

	SYNTH_Channels[channel].counter=0.0f;
	SYNTH_Channels[channel].increment=0.0f;
	SYNTH_Channels[channel].AHDSR_state = AHDSR_IDLE;

	return SYNTH_SUCCESS;
}

static void SYNTH_FillBuffer(int buffer_nbr, SYNTH_Channel *channels)
{
	int 		channel_nbr;

	int 		i;
	float 		counter;
	float 		increment;
	float 		AHDSR_increment;
	uint32_t 	AHDSR_counter;
	uint8_t  	AHDSR_level;
	SYNTH_Instrument_State AHDSR_state;
	SYNTH_Instrument *instrument;

	SYNTH_Wave 	*wave;
	//SYNTH_Wave 	*buffer;
	uint8_t 	volume;
	volatile int cnt_int;
	uint32_t 	tmp;

	for (channel_nbr=0; channel_nbr<SYNTH_ChannelsNbr; channel_nbr++)
	{
		increment = channels[channel_nbr].increment;

		if ((increment == 0.0f) || (channels[channel_nbr].AHDSR_state==AHDSR_IDLE)) {
			if (channel_nbr==0) { // Si le canal est le canal 0 (premier canal), on rempli le buffer avec des zeros, sinon, on ne fait rien
				for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
					SYNTH_LocalBuffer[i]=0;
				}
			}
		} else {
			counter = channels[channel_nbr].counter;
			wave = channels[channel_nbr].instrument->wavetable;
			volume = channels[channel_nbr].volume;
			AHDSR_state = channels[channel_nbr].AHDSR_state;
			AHDSR_level=channels[channel_nbr].AHDSR_level;
			AHDSR_increment=channels[channel_nbr].AHDSR_increment;
			AHDSR_counter=channels[channel_nbr].AHDSR_counter;
			instrument = channels[channel_nbr].instrument;

			for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
				cnt_int = (int)counter;
				tmp = (SYNTH_Wave)(((uint32_t)wave[cnt_int]*volume)>>8);
				counter = counter + increment;
				if (counter >= (float)WaveTableLength) counter = counter - (float)WaveTableLength;

				switch (AHDSR_state)
				{
				case AHDSR_ATTACK:
					tmp = (uint32_t)(tmp * AHDSR_increment);
					AHDSR_increment += instrument->attack_increment;

					if (AHDSR_increment >= 1.0f)
					{
						AHDSR_state = AHDSR_HOLD;
						AHDSR_counter=0;
					}
					break;
				case AHDSR_HOLD:
					AHDSR_counter++;

					if (AHDSR_counter>=instrument->hold_time)
					{
						AHDSR_state = AHDSR_DECAY;
						AHDSR_increment = 1.0f;
					}
					break;
				case AHDSR_DECAY:
					tmp = (uint32_t)(tmp * AHDSR_increment);
					AHDSR_increment -= instrument->decay_increment;

					if (AHDSR_increment <= instrument->decay_level)
					{
						AHDSR_state = AHDSR_SUSTAIN;
						AHDSR_counter=0;
					}
					break;
				case AHDSR_SUSTAIN:
					AHDSR_counter++;

					tmp = (uint32_t)(tmp * instrument->decay_level);

					if (AHDSR_counter>=instrument->sustain_time)
					{
						AHDSR_state = AHDSR_RELEASE;
						AHDSR_increment = instrument->decay_level;
					}
					break;
				case AHDSR_RELEASE:
					tmp = (uint32_t)(tmp * AHDSR_increment);
					AHDSR_increment -= instrument->release_increment;

					if (AHDSR_increment <= 0.0f)
					{
						AHDSR_state = AHDSR_IDLE;
						AHDSR_counter=0;
						AHDSR_increment=0;
					}
					break;
				default: // AHDSR_IDLE
					tmp=0;
				}

				if (channel_nbr == 0)
					SYNTH_LocalBuffer[i]=(SYNTH_Wave)tmp;	// Si c'est le premier canal, on ecrit direct dans le buffer
				else
					SYNTH_LocalBuffer[i]+=(SYNTH_Wave)tmp; // si on ajoute aux valeur déjà ecrites
			}

			channels[channel_nbr].counter = counter;
			channels[channel_nbr].AHDSR_state = AHDSR_state;
			channels[channel_nbr].AHDSR_counter = AHDSR_counter;
			channels[channel_nbr].AHDSR_level = AHDSR_level;
			channels[channel_nbr].AHDSR_increment = AHDSR_increment;
		}

		/* Application du volume principal */
		for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
			tmp = ((uint32_t)SYNTH_LocalBuffer[i]*(uint32_t)SYNTH_MainVolume)>>8;
			if (tmp >=256) tmp=255;
			SYNTH_LocalBuffer[i] = (uint8_t)tmp;
		}

		/* Recopie des echantillons */
		AUDIO_FillBuffer(buffer_nbr, SYNTH_LocalBuffer);
	}
}

//static void SYNTH_FillBuffer16(int buffer_nbr, SYNTH_Channel *channels)
//{
//	int 		channel_nbr;
//
//	int 		i;
//	float 		counter;
//	float 		increment;
//	float 		AHDSR_increment;
//	uint32_t 	AHDSR_counter;
//	uint8_t  	AHDSR_level;
//	SYNTH_Instrument_State AHDSR_state;
//	SYNTH_Instrument *instrument;
//
//	SYNTH_Wave 	*wave;
//	uint8_t 	volume;
//	volatile int cnt_int;
//	int32_t 	tmp;
//
//	for (channel_nbr=0; channel_nbr<SYNTH_ChannelsNbr; channel_nbr++)
//	{
//		increment = channels[channel_nbr].increment;
//
//		if ((increment == 0.0f) || (channels[channel_nbr].AHDSR_state==AHDSR_IDLE)) {
//			if (channel_nbr==0) { // Si le canal est le canal 0 (premier canal), on rempli le buffer avec des zeros, sinon, on ne fait rien
//				for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
//					SYNTH_LocalBuffer[i]=0;
//				}
//			}
//		} else {
//			counter = channels[channel_nbr].counter;
//			wave = channels[channel_nbr].instrument->wavetable;
//			volume = channels[channel_nbr].volume;
//			AHDSR_state = channels[channel_nbr].AHDSR_state;
//			AHDSR_level=channels[channel_nbr].AHDSR_level;
//			AHDSR_increment=channels[channel_nbr].AHDSR_increment;
//			AHDSR_counter=channels[channel_nbr].AHDSR_counter;
//			instrument = channels[channel_nbr].instrument;
//
//			for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
//				cnt_int = (int)counter;
//
//				tmp = (SYNTH_Wave)(((int32_t)wave[cnt_int]*volume)/256);
//
//				counter = counter + increment;
//				if (counter >= (float)WaveTableLength) counter = counter - (float)WaveTableLength;
//
//				switch (AHDSR_state)
//				{
//				case AHDSR_ATTACK:
//					tmp = (int32_t)(tmp * AHDSR_increment);
//					AHDSR_increment += instrument->attack_increment;
//
//					if (AHDSR_increment >= 1.0f)
//					{
//						AHDSR_state = AHDSR_HOLD;
//						AHDSR_counter=0;
//					}
//					break;
//				case AHDSR_HOLD:
//					AHDSR_counter++;
//
//					if (AHDSR_counter>=instrument->hold_time)
//					{
//						AHDSR_state = AHDSR_DECAY;
//						AHDSR_increment = 1.0f;
//					}
//					break;
//				case AHDSR_DECAY:
//					tmp = (int32_t)(tmp * AHDSR_increment);
//					AHDSR_increment -= instrument->decay_increment;
//
//					if (AHDSR_increment <= instrument->decay_level)
//					{
//						AHDSR_state = AHDSR_SUSTAIN;
//						AHDSR_counter=0;
//					}
//					break;
//				case AHDSR_SUSTAIN:
//					AHDSR_counter++;
//
//					tmp = (int32_t)(tmp * instrument->decay_level);
//
//					if (AHDSR_counter>=instrument->sustain_time)
//					{
//						AHDSR_state = AHDSR_RELEASE;
//						AHDSR_increment = instrument->decay_level;
//					}
//					break;
//				case AHDSR_RELEASE:
//					tmp = (int32_t)(tmp * AHDSR_increment);
//					AHDSR_increment -= instrument->release_increment;
//
//					if (AHDSR_increment <= 0.0f)
//					{
//						AHDSR_state = AHDSR_IDLE;
//						AHDSR_counter=0;
//						AHDSR_increment=0;
//					}
//					break;
//				default: // AHDSR_IDLE
//
//					tmp=0;
//				}
//
//				if (channel_nbr == 0)
//					SYNTH_LocalBuffer[i]=(SYNTH_Wave)tmp;	// Si c'est le premier canal, on ecrit direct dans le buffer
//				else
//					SYNTH_LocalBuffer[i]+=(SYNTH_Wave)tmp; // si on ajoute aux valeur déjà ecrites
//
//				//SYNTH_LocalBuffer[i]=(int16_t)tmp;
//				//				if (i<10) {
//				//					SYNTH_LocalBuffer[i]=32760;
//				//				} else {
//				//					SYNTH_LocalBuffer[i]=0;
//				//				}
//			}
//
//			channels[channel_nbr].counter = counter;
//			channels[channel_nbr].AHDSR_state = AHDSR_state;
//			channels[channel_nbr].AHDSR_counter = AHDSR_counter;
//			channels[channel_nbr].AHDSR_level = AHDSR_level;
//			channels[channel_nbr].AHDSR_increment = AHDSR_increment;
//		}
//
//		/* Application du volume principal */
//		for (i=0; i< AUDIO_BUFFER_SIZE; i++) {
//			tmp = ((int32_t)SYNTH_LocalBuffer[i]*(int32_t)SYNTH_MainVolume)/256;
//
//			if (tmp >=32760) tmp=32760;
//			else if (tmp <=-32760) tmp=-32760;
//			SYNTH_LocalBuffer[i] = (int16_t)tmp;
//		}
//
//		/* Recopie des echantillons */
//		AUDIO_FillBuffer16(buffer_nbr, SYNTH_LocalBuffer);
//	}
//}

static void SYNTH_AudioCallback(int buffer_nbr)
{
	SYNTH_FillBuffer(buffer_nbr, SYNTH_Channels);
}
