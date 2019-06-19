/**
 ******************************************************************************
 * @file    stm32746g_discovery_pressure.h
 * @author  dimercur
 * @brief   This file contains the common defines and functions prototypes for
 *          the stm32746g_discovery_pressure.c driver.
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
#ifndef __STM32746G_DISCOVERY_PRESSURE_H
#define __STM32746G_DISCOVERY_PRESSURE_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include "../Components/bmp280/bmp280.h"
#include <string.h>
/** @addtogroup STM32746G_DISCOVERY_PRESSURE
 * @{
 */


/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32746G_DISCOVERY_PRESSURE_Exported_Constants STM32746G_DISCOVERY_PRESSURE Exported Constants
 * @{
 */
/* PRESSURE Error codes */
#define PRESSURE_OK            ((uint8_t)0x00)
#define PRESSURE_ERROR         ((uint8_t)0x01)
#define PRESSURE_BUSY          ((uint8_t)0x02)
#define PRESSURE_NO_DATA       ((uint8_t)0x03)

#define PRESSURE_SPIx 			DISCOVERY_SPIx

/* Definition for SPI clock resources */
#define PRESSURE_CLK_ENABLE()            DISCOVERY_SPIx_CLK_ENABLE()
#define PRESSURE_CLK_DISABLE()           DISCOVERY_SPIx_CLK_DISABLE()
#define PRESSURE_CS_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOA_CLK_ENABLE()
#define PRESSURE_CLK_GPIO_CLK_ENABLE()   DISCOVERY_SPIx_CLK_GPIO_CLK_ENABLE()
#define PRESSURE_MISO_GPIO_CLK_ENABLE()  DISCOVERY_SPIx_MISO_GPIO_CLK_ENABLE()
#define PRESSURE_MOSI_GPIO_CLK_ENABLE()  DISCOVERY_SPIx_MOSI_GPIO_CLK_ENABLE()

/* Definition for SPI Pins */
#define PRESSURE_CS_PIN                GPIO_PIN_8
#define PRESSURE_CS_GPIO_PORT          GPIOA
#define PRESSURE_CLK_PIN               DISCOVERY_SPIx_CLK_PIN
#define PRESSURE_CLK_GPIO_PORT         DISCOVERY_SPIx_CLK_GPIO_PORT
#define PRESSURE_MISO_PIN              DISCOVERY_SPIx_MISO_PIN
#define PRESSURE_MISO_GPIO_PORT        DISCOVERY_SPIx_MISO_GPIO_PORT
#define PRESSURE_MOSI_PIN              DISCOVERY_SPIx_MOSI_PIN
#define PRESSURE_MOSI_GPIO_PORT        DISCOVERY_SPIx_MOSI_GPIO_PORT

#define PRESSURE_CS_ENABLE(dev) 	   BMP280_CS_ENABLE(dev)
#define PRESSURE_CS_DISABLE(dev)	   BMP280_CS_DISABLE(dev)
/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32746G_DISCOVERY_PRESSURE_Exported_Types STM32746G_DISCOVERY_PRESSURE Exported Types
 * @{
 */

/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32746G_DISCOVERY_PRESSURE_Exported_Functions
 * @{
 */
uint8_t BSP_PRESSURE_Init       (void);
uint8_t BSP_PRESSURE_DeInit     (void);
uint8_t BSP_PRESSURE_ReadValues(uint32_t *pressure);
uint8_t BSP_PRESSURE_ReadTemperature(int32_t *temperature_degC);
uint8_t BSP_PRESSURE_ReadCompensatedValues(float *pressure, float *temperature);

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void BSP_PRESSURE_MspInit		(void);
void BSP_PRESSURE_MspDeInit		(void);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_MAG_H */
/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
