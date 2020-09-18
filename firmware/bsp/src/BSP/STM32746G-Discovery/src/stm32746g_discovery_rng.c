/**
  ******************************************************************************
  * @file    BSP/Src/rng.c
  * @author  MCD Application Team
  * @brief   Random number generator
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

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery_rng.h"

/** @addtogroup STM32F7xx_HAL_Examples
  * @{
  */

/** @addtogroup BSP
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static RNG_HandleTypeDef RNG_Handle;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Random number generator initialisation
  * @param  RNG_HandleTypeDef
  * @retval None
  */
void BSP_RNG_InitGenerator(void)
{
	RNG_Handle.State = HAL_RNG_STATE_RESET;
	HAL_RNG_Init(&RNG_Handle);
}

/**
  * @brief  Get random number
  * @param  RNG_HandleTypeDef
  * @retval 32 bit random value
  */
uint32_t BSP_RNG_GetNumber(void)
{
uint32_t val;

	if (HAL_RNG_GenerateRandomNumber(&RNG_Handle, &val) == HAL_OK)
		return val;
	else
		return RNG_Handle.RandomNumber;
}

/**
  * @brief  Low level Init (clock)
  * @param  RNG_HandleTypeDef
  * @retval None
  */
void HAL_RNG_MspInit(RNG_HandleTypeDef *hrng)
{
	/* Reset RNG */
	__HAL_RCC_RNG_FORCE_RESET();

	/* Release Reset RNG */
	__HAL_RCC_RNG_RELEASE_RESET();

	/* Enable clock for RNG */
	__HAL_RCC_RNG_CLK_ENABLE();

	hrng->Instance = RNG;
}

/**
  * @brief  Low level deinit
  * @param  RNG_HandleTypeDef
  * @retval None
  */
void HAL_RNG_MspDeInit(RNG_HandleTypeDef *hrng)
{
	/* Reset RNG */
	__HAL_RCC_RNG_FORCE_RESET();

	/* Release Reset RNG */
	__HAL_RCC_RNG_RELEASE_RESET();

	/* Disable clock for RNG */
	__HAL_RCC_RNG_CLK_DISABLE();

	hrng->Instance = 0x0;
}
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
