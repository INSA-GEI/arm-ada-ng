/**
  ******************************************************************************
  * @file    stm32746g_discovery_esp_wifi.h
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

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup STM32746G_DISCOVERY
  * @{
  */
    
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32746G_DISCOVERY_ESP_WIFI_H
#define __STM32746G_DISCOVERY_ESP_WIFI_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include <string.h>

/** @addtogroup STM32746G_DISCOVERY_ESP_WIFI
  * @{
  */    

  
/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32746G_DISCOVERY_ESP_WIFI_Exported_Constants STM32746G_DISCOVERY_ESP_WIFI Exported Constants
  * @{
  */
/* WIFI Error codes */
#define WIFI_OK            ((uint8_t)0x00)
#define WIFI_ERROR         ((uint8_t)0x01)
#define WIFI_BUSY          ((uint8_t)0x02)

 /* Definition for SPI clock resources */
 #define WIFI_RESET_CLK_ENABLE()    __HAL_RCC_GPIOB_CLK_ENABLE()
 #define WIFI_RESET_CLK_DISABLE()   __HAL_RCC_GPIOB_CLK_DISABLE()
 #define WIFI_ENABLE_CLK_ENABLE()   __HAL_RCC_GPIOG_CLK_ENABLE()
 #define WIFI_ENABLE_CLK_DISABLE()   __HAL_RCC_GPIOG_CLK_DISABLE()

 /* Definition for I2C Pins */
 #define WIFI_RESET_PIN               GPIO_PIN_4
 #define WIFI_RESET_GPIO_PORT         GPIOB
 #define WIFI_ENABLE_PIN              GPIO_PIN_6
 #define WIFI_ENABLE_GPIO_PORT        GPIOG

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32746G_DISCOVERY_ESP_WIFI_Exported_Types STM32746G_DISCOVERY_ESP_WIFI Exported Types
  * @{
  */

 /**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32746G_DISCOVERY_ESP_WIFI_Exported_Functions
  * @{
  */  
uint8_t BSP_WIFI_Init       (void);
uint8_t BSP_WIFI_DeInit     (void);
uint8_t BSP_WIFI_SendCommand(char* cmd, char* ans);

void BSP_WIFI_IRQHandler	(void);
__weak void BSP_WIFI_DataReceived	(char* data, uint16_t length);

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void BSP_WIFI_MspInit		(void);
void BSP_WIFI_MspDeInit		(void);

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_ESP_WIFI_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
