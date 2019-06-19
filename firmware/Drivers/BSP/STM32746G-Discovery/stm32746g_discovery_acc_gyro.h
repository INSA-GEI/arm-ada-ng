/**
 ******************************************************************************
 * @file    stm32746g_discovery_mag.h
 * @author  dimercur
 * @brief   This file contains the common defines and functions prototypes for
 *          the stm32746g_discovery_mag.c driver.
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
#ifndef __STM32746G_DISCOVERY_ACC_GYRO_H
#define __STM32746G_DISCOVERY_ACC_GYRO_H

#ifdef __cplusplus
extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery.h"
#include "../Components/lsm6ds3/lsm6ds3_reg.h"
#include <string.h>
/** @addtogroup STM32746G_DISCOVERY_ACC_GYRO
 * @{
 */


/* Exported constants --------------------------------------------------------*/ 
/** @defgroup STM32746G_DISCOVERY_ACC_GYRO_Exported_Constants STM32746G_DISCOVERY_ACC_GYRO Exported Constants
 * @{
 */
/* ACCelerometre Error codes */
#define ACC_OK            ((uint8_t)0x00)
#define ACC_ERROR         ((uint8_t)0x01)
#define ACC_BUSY          ((uint8_t)0x02)
#define ACC_NO_DATA       ((uint8_t)0x03)

/* Definition for I2C peripheral */
#define ACC_GYRO_I2Cx 					DISCOVERY_EXT_I2Cx

/* Definition for SPI clock resources */
#define ACC_GYRO_I2Cx_CLK_ENABLE()            __HAL_RCC_I2C1_CLK_ENABLE()
#define ACC_GYRO_I2Cx_CLK_DISABLE()           __HAL_RCC_I2C1_CLK_DISABLE()
#define ACC_GYRO_I2Cx_SDA_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOG_CLK_ENABLE()
#define ACC_GYRO_I2Cx_SCL_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOI_CLK_DISABLE()

/* Definition for I2C Pins */
#define ACC_GYRO_I2Cx_SCL_PIN               GPIO_PIN_1
#define ACC_GYRO_I2Cx_SCL_GPIO_PORT         GPIOI
#define ACC_GYRO_I2Cx_SDA_PIN              	GPIO_PIN_14
#define ACC_GYRO_I2Cx_SDA_GPIO_PORT        	GPIOB

#define ACC_GYRO_I2Cx_FORCE_RESET()         __HAL_RCC_I2C1_FORCE_RESET()
#define ACC_GYRO_I2Cx_RELEASE_RESET()       __HAL_RCC_I2C1_RELEASE_RESET()
#define ACC_GYRO_I2Cx_SCL_SDA_AF            GPIO_AF4_I2C1

#define ACC_GYRO_RCC_PERIPHCLK_I2Cx         RCC_PERIPHCLK_I2C1
#define ACC_GYRO_RCC_I2CxCLKSOURCE_SYSCLK   RCC_I2C1CLKSOURCE_PCLK1

#define ACC_GYRO_I2C_TIMING 				DISCOVERY_I2Cx_TIMING
/**
 * @}
 */

/* Exported types ------------------------------------------------------------*/
/** @defgroup STM32746G_DISCOVERY_ACC_GYRO_Exported_Types STM32746G_DISCOVERY_ACC_GYRO Exported Types
 * @{
 */
typedef struct
{
	float x;
	float y;
	float z;
} acceleration_t ;

typedef struct
{
	float x;
	float y;
	float z;
} angularRate_t;
/**
 * @}
 */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup STM32746G_DISCOVERY_ACC_GYRO_Exported_Functions
 * @{
 */
uint8_t BSP_ACC_GYRO_Init       (void);
uint8_t BSP_ACC_GYRO_DeInit     (void);
uint8_t BSP_ACC_ReadRawValues(axis3bit16_t *data_raw_acceleration);
uint8_t BSP_GYRO_ReadRawValues(axis3bit16_t *data_raw_angular_rate);
uint8_t BSP_ACC_ReadValues(acceleration_t *acceleration);
uint8_t BSP_GYRO_ReadValues(angularRate_t *angular_rate);
uint8_t BSP_ACC_ReadTemperature(float *temperature_degC);

/* These functions can be modified in case the current settings
   need to be changed for specific application needs */
void BSP_ACC_GYRO_MspInit		(void);
void BSP_ACC_GYRO_MspDeInit		(void);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_ACC_GYRO_H */
/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
