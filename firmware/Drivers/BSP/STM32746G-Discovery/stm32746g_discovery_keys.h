/**
  ******************************************************************************
  * @file    stm32746g_discovery_keys.h
  * @author  dimercur
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32746g_discovery_keys.c driver.
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
#ifndef __STM32746G_DISCOVERY_KEYS_H
#define __STM32746G_DISCOVERY_KEYS_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"

/** @addtogroup STM32746G_DISCOVERY_KEYS
  * @{
  */    

  
/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32746G_DISCOVERY_KEYS_Exported_Constants STM32746G_DISCOVERY_KEYS Exported Constants
  * @{
  */
/* KEYS Error codes */
#define KEYS_OK            ((uint8_t)0x00)
#define KEYS_ERROR         ((uint8_t)0x01)
#define KEYS_BUSY          ((uint8_t)0x02)

#define KEYS_PRESSED       ((uint8_t)0x81)
#define KEYS_RELEASED      ((uint8_t)0x80)

/* Definition for SPI clock resources */
#define KEYS_CLK_ENABLE()            __HAL_RCC_SPI2_CLK_ENABLE()
#define KEYS_CLK_DISABLE()           __HAL_RCC_SPI2_CLK_DISABLE()
#define KEYS_CS_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOG_CLK_ENABLE()
#define KEYS_CLK_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOI_CLK_ENABLE()
#define KEYS_MISO_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOB_CLK_ENABLE()

/* Definition for SPI Pins */
#define KEYS_CS_PIN                GPIO_PIN_7
#define KEYS_CS_GPIO_PORT          GPIOG
#define KEYS_CLK_PIN               GPIO_PIN_1
#define KEYS_CLK_GPIO_PORT         GPIOI
#define KEYS_MISO_PIN              GPIO_PIN_14
#define KEYS_MISO_GPIO_PORT        GPIOB

/* Definition for keys position */
#define KEYS_A					   ((uint8_t)1>>0)
#define KEYS_B					   ((uint8_t)1>>1)
#define KEYS_X					   ((uint8_t)1>>2)
#define KEYS_Y					   ((uint8_t)1>>3)
#define KEYS_UP					   ((uint8_t)1>>4)
#define KEYS_DOWN				   ((uint8_t)1>>5)
#define KEYS_LEFT				   ((uint8_t)1>>6)
#define KEYS_RIGHT				   ((uint8_t)1>>7)

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32746G_DISCOVERY_KEYS_Exported_Types STM32746G_DISCOVERY_KEYS Exported Types
  * @{
  */

 /**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32746G_DISCOVERY_KEYS_Exported_Functions
  * @{
  */  
uint8_t BSP_KEYS_Init       (void);
uint8_t BSP_KEYS_DeInit     (void);
uint8_t BSP_KEYS_Read       (void);
uint8_t BSP_KEYS_GetKey     (uint8_t key);
uint8_t BSP_KEYS_GetKeys    (void);

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void BSP_KEYS_MspInit		(void);
void BSP_KEYS_MspDeInit		(void);

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_KEYS_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
