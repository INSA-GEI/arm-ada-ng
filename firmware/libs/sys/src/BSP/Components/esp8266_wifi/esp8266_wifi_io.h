/**
  ******************************************************************************
  * @file    esp8266_wifi_io.c
  * @author  dimercur
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32746g_discovery_esp_wifi.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#ifndef	__ESP8266_WIFI_IO_H
#define	__ESP8266_WIFI_IO_H


#include "stm32f7xx_hal.h"
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

//#include <stdbool.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdarg.h>

#include "esp8266_wifi_conf.h"
#include "esp8266_wifi.h"

//###################################################################################################

uint8_t ESP8266_WIFI_IO_Init(Wifi_t *wifi);
uint8_t ESP8266_WIFI_IO_DeInit(Wifi_t *wifi);
void ESP8266_WIFI_IO_MspInit(void);
void ESP8266_WIFI_IO_MspDeInit(void);

uint8_t ESP8266_WIFI_IO_SendRaw(Wifi_t *wifi, uint8_t *data, uint16_t len);
void ESP8266_WIFI_IO_RxClear(Wifi_t *wifi);
void ESP8266_WIFI_IO_TxClear(Wifi_t *wifi);

void ESP8266_WIFI_IO_RxCallBack(void);

#endif /* __ESP8266_WIFI_IO_H */

