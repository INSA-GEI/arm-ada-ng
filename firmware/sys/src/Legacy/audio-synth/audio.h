/******************************************************************************/
/* audio.h: Header for audio driver                                           */
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
#ifndef __AUDIO_H__
#define __AUDIO_H__

#include "stm32746g_discovery.h"

#define AUDIO_BUFFER_SIZE   512

typedef struct {
	int16_t buffer1[AUDIO_BUFFER_SIZE*2];
	int16_t buffer2[AUDIO_BUFFER_SIZE*2];
}AUDIO_BufferTypeDef;

//
//#define AUDIO_BUFFER_LENGTH 512
//
//struct AUDIO_BUFFER_ST
//{
//	uint8_t buffer1[AUDIO_BUFFER_LENGTH];
//	uint8_t buffer2[AUDIO_BUFFER_LENGTH];
//};
//
//typedef struct AUDIO_BUFFER_ST  AUDIO_BUFFER_TYPE;
//AUDIO_BUFFER_TYPE AUDIO_Buffer;

typedef void (*AUDIO_EventCallback)(int buffer_nbr);

void AUDIO_Init(void);
void AUDIO_Start(void);
void AUDIO_Stop(void);
void AUDIO_FillBuffer(int buffer_nbr, uint8_t* buffer);
void AUDIO_FillBuffer16(int buffer_nbr, int16_t* buffer);
void AUDIO_GetBuffersPtr(uint8_t **buffer_1, uint8_t **buffer_2);
void AUDIO_SetEventCallback(AUDIO_EventCallback callback);

#endif /* __AUDIO_H__ */
