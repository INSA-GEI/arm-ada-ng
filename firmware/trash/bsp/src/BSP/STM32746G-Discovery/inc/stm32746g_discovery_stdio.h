/**
  ******************************************************************************
  * @file    stm32746g_discovery_stdio.h
  * @author  dimercur
  * @brief   This file contains the common defines and functions prototypes for
  *          the stm32746g_discovery_stdio.c driver.
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
#ifndef __STM32746G_DISCOVERY_STDIO_H
#define __STM32746G_DISCOVERY_STDIO_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include <string.h>

/** @addtogroup STM32746G_DISCOVERY_STDIO
  * @{
  */    

  
/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32746G_DISCOVERY_STDIO_Exported_Constants STM32746G_DISCOVERY_STDIO Exported Constants
  * @{
  */
/* STDIO Error codes */
#define STDIO_OK            ((uint8_t)0x00)
#define STDIO_ERROR         ((uint8_t)0x01)

/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32746G_DISCOVERY_STDIO_Exported_Types STM32746G_DISCOVERY_STDIO Exported Types
  * @{
  */

 /**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32746G_DISCOVERY_STDIO_Exported_Functions
  * @{
  */  
uint8_t BSP_STDIO_Init       (void);
uint8_t BSP_STDIO_DeInit     (void);
uint8_t BSP_STDIO_SendData   (uint8_t* data, uint16_t len);

void BSP_STDIO_IRQHandler	(void);
void BSP_STDIO_DataReceived	(char* data, uint16_t length);

/**
  * @}
  */ 

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_STDIO_H */
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
