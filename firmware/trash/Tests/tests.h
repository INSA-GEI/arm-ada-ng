/*
 * tests.h
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */

#ifndef __TESTS_H_
#define __TESTS_H_


typedef enum {
  AUDIO_ERROR_NONE = 0,
  AUDIO_ERROR_NOTREADY,
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
}AUDIO_ErrorTypeDef;

uint8_t Audio_Test_Process(void);
void TESTS_Run(void);
uint8_t CheckForUserInput(void);

#endif /* __TESTS_H_ */
