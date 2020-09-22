/**
 ******************************************************************************
 * @file    stm32746g_discovery_keys.c
 * @author  dimercur
 * @brief   This file includes a standard driver for key
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================  
  [..] 
   (#) This driver is used to drive the N25Q128A QSPI external
       memory mounted on STM32746G-Discovery board.

   (#) This driver need a specific component driver (N25Q128A) to be included with.

   (#) Initialization steps:
       (++) Initialize the QPSI external memory using the BSP_QSPI_Init() function. This 
            function includes the MSP layer hardware resources initialization and the
            QSPI interface with the external memory.

   (#) QSPI memory operations
       (++) QSPI memory can be accessed with read/write operations once it is
            initialized.
            Read/write operation can be performed with AHB access using the functions
            BSP_QSPI_Read()/BSP_QSPI_Write(). 
       (++) The function BSP_QSPI_GetInfo() returns the configuration of the QSPI memory. 
            (see the QSPI memory data sheet)
       (++) Perform erase block operation using the function BSP_QSPI_Erase_Block() and by
            specifying the block address. You can perform an erase operation of the whole 
            chip by calling the function BSP_QSPI_Erase_Chip(). 
       (++) The function BSP_QSPI_GetStatus() returns the current status of the QSPI memory. 
            (see the QSPI memory data sheet)
  @endverbatim
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

/* Dependencies
- stm32f7xx_hal_spi.c
- stm32f7xx_hal_gpio.c
- stm32f7xx_hal_cortex.c
- stm32f7xx_hal_rcc_ex.h
EndDependencies */

/* Includes ------------------------------------------------------------------*/
#include "stm32746g_discovery_keys.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_KEYS STM32746G-Discovery Keys
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_KEYS_Private_Variables STM32746G_DISCOVERY KEYS Private Variables
 * @{
 */
SPI_HandleTypeDef SPIHandle;


uint8_t KEYSBuffer;

/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_KEYS_Private_Functions STM32746G_DISCOVERY Keys Private Functions
 * @{
 */


/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_KEYS_Exported_Functions STM32746G_DISCOVERY KEYS Exported Functions
 * @{
 */

/**
 * @brief  Initializes the KEYS interface.
 * @retval KEYS memory status
 */
uint8_t BSP_KEYS_Init(void)
{ 
	/* SPi Configuration */
	SPIHandle.Instance = KEYS_SPIx;

	/* Call the DeInit function to reset the driver */
	if (HAL_SPI_DeInit(&SPIHandle) != HAL_OK)
	{
		return KEYS_ERROR;
	}

	/* System level initialization */
	BSP_KEYS_MspInit();

	/* SPI2 initialization */
	SPIHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	SPIHandle.Init.CLKPhase 		= SPI_PHASE_1EDGE;
	SPIHandle.Init.CLKPolarity 		= SPI_POLARITY_LOW;
	SPIHandle.Init.DataSize 		= SPI_DATASIZE_8BIT;
	SPIHandle.Init.Direction 		= SPI_DIRECTION_2LINES;
	SPIHandle.Init.FirstBit 		= SPI_FIRSTBIT_MSB;
	SPIHandle.Init.Mode 			=  SPI_MODE_MASTER;
	SPIHandle.Init.NSS 				= SPI_NSS_SOFT;
	SPIHandle.Init.TIMode           = SPI_TIMODE_DISABLE;
	SPIHandle.Init.CRCCalculation   = SPI_CRCCALCULATION_DISABLE;
	SPIHandle.Init.CRCPolynomial    = 7;

	if (HAL_SPI_Init(&SPIHandle) != HAL_OK)
	{
		return KEYS_ERROR;
	}

	KEYS_CS_DISABLE();
	KEYS_SET_SERIAL_MODE();

	return KEYS_OK;
}

/**
 * @brief  De-Initializes the SPI interface.
 * @retval KEYS memory status
 */
uint8_t BSP_KEYS_DeInit(void)
{ 
	KEYS_CS_DISABLE();
	KEYS_SET_SERIAL_MODE();

	BSP_KEYS_MspDeInit();

	return KEYS_OK;
}

/**
 * @brief  Reads keys
 * @retval KEYS memory status
 */
uint8_t BSP_KEYS_Read(void)
{
	uint8_t status;
	uint8_t dummy;

	/* TODO: Supprimer apres test */
	//__disable_irq();

	/* Enable Keys serializer */
	KEYS_CS_ENABLE();

	/* Enable Parallel load (KEY_LOAD=0, PE) */
	KEYS_SET_PARALLEL_MODE();

	/* Do a dummy read (just to have 1 clock event for loading parallel data) */
	status = HAL_SPI_Receive(&SPIHandle, &dummy,1,100);

	/* Switch to serial mode */
	KEYS_SET_SERIAL_MODE();

	/* Read data */
	status = HAL_SPI_Receive(&SPIHandle, &KEYSBuffer,1,100);
	KEYSBuffer = ~KEYSBuffer; // on inverse la polarité des touches: a 0 si relachée, à 1 si appuyée

	/* Disable Keys serializer (free spi bus) */
	KEYS_CS_DISABLE();

	if (status != HAL_OK)
	{
		return KEYS_ERROR;
	}

	/* TODO: Supprimer apres test */
	//__enable_irq();

	return KEYS_OK;
}

/**
 * @brief  Check if given key is pressed
 * @retval KEYS_PRESSED or KEYS_RELEASE
 */
uint8_t BSP_KEYS_GetKey(uint8_t key)
{
	BSP_KEYS_Read();

	if (KEYSBuffer & key)
	{
		return KEYS_PRESSED;
	}

	return KEYS_RELEASED;
}

/**
 * @brief  Return whole keys status
 * @retval Keys status
 */
uint8_t BSP_KEYS_GetKeys (void)
{
	BSP_KEYS_Read();

	return KEYSBuffer;
}
/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_KEYS_Private_Functions
 * @{
 */

/**
 * @brief KEYS MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
__weak void BSP_KEYS_MspInit(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable the Keys (SPI) interface clock */
	KEYS_CLK_ENABLE();

	/* Enable GPIO clocks */
	KEYS_CS_GPIO_CLK_ENABLE();
	KEYS_CLK_GPIO_CLK_ENABLE();
	KEYS_MISO_GPIO_CLK_ENABLE();
	KEYS_LOAD_GPIO_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* KEYS CS GPIO pin configuration  */
	gpio_init_structure.Pin       = KEYS_CS_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull      = GPIO_NOPULL;
	gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(KEYS_CS_GPIO_PORT, &gpio_init_structure);

	/* KEYS CS GPIO pin configuration  */
	gpio_init_structure.Pin       = KEYS_LOAD_PIN;
	HAL_GPIO_Init(KEYS_LOAD_GPIO_PORT, &gpio_init_structure);

	//TODO: A supprimer quand le driver BMP280 sera pret
	/* BMP280 CS GPIO pin configuration , to put it high */
	gpio_init_structure.Pin       = GPIO_PIN_8;
	HAL_GPIO_Init(GPIOA, &gpio_init_structure);

	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
	//TODO: Fin de suppression

	/* KEYS CLK GPIO pin configuration  */
	gpio_init_structure.Pin       = KEYS_CLK_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull      = GPIO_NOPULL;
	gpio_init_structure.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(KEYS_CLK_GPIO_PORT, &gpio_init_structure);

	/* KEYS MISO GPIO pin configuration  */
	gpio_init_structure.Pin       = KEYS_MISO_PIN;
	gpio_init_structure.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(KEYS_MISO_GPIO_PORT, &gpio_init_structure);

	/*##-3- Configure the NVIC for SPI2 #########################################*/
	/* NVIC configuration for SPI2 interrupt */
	HAL_NVIC_SetPriority(SPI2_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
}

/**
 * @brief KEYS MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_KEYS_MspDeInit(void)
{
	/*##-1- Disable the NVIC for QSPI ###########################################*/
	HAL_NVIC_DisableIRQ(SPI2_IRQn);

	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* De-Configure QSPI pins */
	HAL_GPIO_DeInit(KEYS_CS_GPIO_PORT, KEYS_CS_PIN);
	HAL_GPIO_DeInit(KEYS_CLK_GPIO_PORT, KEYS_CLK_PIN);
	HAL_GPIO_DeInit(KEYS_MISO_GPIO_PORT, KEYS_MISO_PIN);
	HAL_GPIO_DeInit(KEYS_LOAD_GPIO_PORT, KEYS_MISO_PIN);
	/* Disable the QuadSPI memory interface clock */

	KEYS_CLK_DISABLE();
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

