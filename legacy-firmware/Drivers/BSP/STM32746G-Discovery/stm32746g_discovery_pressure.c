/**
 ******************************************************************************
 * @file    stm32746g_discovery_pressure.c
 * @author  dimercur
 * @brief   This file includes a standard driver for barometric pressure
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
#include "stm32746g_discovery_pressure.h"
//#include "stm32746g_discovery_mag_conf.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_PRESSURE STM32746G-Discovery PRESSURE
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_PRESSURE_Private_Variables STM32746G_DISCOVERY PRESSURE Private Variables
 * @{
 */
static SPI_HandleTypeDef SPIHandle;
BMP280_HandleTypedef PressureHandle;
BMP280_HandleTypedef* PressureHandlePtr;
static char pressureSensorEnabled=0;
/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_PRESSURE_Private_Functions STM32746G_DISCOVERY PRESSURE Private Functions
 * @{
 */


/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_PRESSURE_Exported_Functions STM32746G_DISCOVERY PRESSURE Exported Functions
 * @{
 */

/**
 * @brief  Initializes interface for pressure sensor.
 * @retval Initialization status
 */
uint8_t BSP_PRESSURE_Init(void)
{ 
	/* SPi Configuration */
	SPIHandle.Instance = PRESSURE_SPIx;
	PressureHandle.hspi = &SPIHandle;
	PressureHandle.cs_gpio = PRESSURE_CS_GPIO_PORT;
	PressureHandle.cs_pin = PRESSURE_CS_PIN;
	PressureHandlePtr = &PressureHandle;

	/* Call the DeInit function to reset the driver */
	if (HAL_SPI_DeInit(&SPIHandle) != HAL_OK)
	{
		return PRESSURE_ERROR;
	}

	__disable_irq(); // Set PRIMASK

	/* System level initialization */
	BSP_PRESSURE_MspInit();

	/* SPI2 initialization */
	SPIHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
	SPIHandle.Init.CLKPhase 		= SPI_PHASE_1EDGE;
	SPIHandle.Init.CLKPolarity 		= SPI_POLARITY_LOW;
	SPIHandle.Init.DataSize 		= SPI_DATASIZE_8BIT;
	SPIHandle.Init.Direction 		= SPI_DIRECTION_2LINES;
	SPIHandle.Init.FirstBit 		= SPI_FIRSTBIT_MSB;
	SPIHandle.Init.Mode 			= SPI_MODE_MASTER;
	SPIHandle.Init.NSS 				= SPI_NSS_SOFT;
	SPIHandle.Init.TIMode           = SPI_TIMODE_DISABLE;
	SPIHandle.Init.CRCCalculation   = SPI_CRCCALCULATION_DISABLE;
	SPIHandle.Init.CRCPolynomial    = 7;

	if (HAL_SPI_Init(&SPIHandle) != HAL_OK)
	{
		return PRESSURE_ERROR;
	}

	PRESSURE_CS_DISABLE(PressureHandlePtr);

	bmp280_init_default_params(&PressureHandle.params);

	if (!bmp280_init(&PressureHandle, &PressureHandle.params)) {
		return PRESSURE_ERROR;
	}

	if (PressureHandle.id != BMP280_CHIP_ID) {
		return PRESSURE_ERROR;
	}

	pressureSensorEnabled=1;

	__enable_irq(); // Clear PRIMASK
	return PRESSURE_OK;
}

/**
 * @brief  De-Initializes pressure sensor interface.
 * @retval De-init status
 */
uint8_t BSP_PRESSURE_DeInit(void)
{ 
	PRESSURE_CS_DISABLE(PressureHandlePtr);

	BSP_PRESSURE_MspDeInit();

	return PRESSURE_OK;
}

/**
 * @brief  Pressure value in pascal
 * @retval Read status
 */
uint8_t BSP_PRESSURE_ReadValues(uint32_t *pressure)
{
	uint8_t status= PRESSURE_OK;
	int32_t temperature;
	uint32_t humidity;

	if (pressureSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		while (bmp280_is_measuring(&PressureHandle));

		if (!bmp280_read_raw(&PressureHandle, &temperature, pressure, &humidity))
		{
			status =  PRESSURE_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		__enable_irq(); // Clear PRIMASK
	}
	else
	{
		*pressure=0;
		status =  PRESSURE_NO_DATA;
	}

	return status;
}

/**
 * @brief  Reads T° values in °C
 * @retval Read status
 */
uint8_t BSP_PRESSURE_ReadTemperature(int32_t *temperature_degC)
{
	uint8_t status= PRESSURE_OK;
	uint32_t pressure;
	uint32_t humidity;

	if (pressureSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		while (bmp280_is_measuring(&PressureHandle));

		if (!bmp280_read_raw(&PressureHandle, temperature_degC, &pressure, &humidity))
		{
			status =  PRESSURE_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		__enable_irq(); // Clear PRIMASK
	}
	else
	{ *temperature_degC=0;
	status =  PRESSURE_NO_DATA;
	}

	return status;
}

/**
 * @brief  Pressure and temperature compensated
 * @retval Read status
 */
uint8_t BSP_PRESSURE_ReadCompensatedValues(float *pressure, float *temperature)
{
	uint8_t status= PRESSURE_OK;
	float humidity;

	if (pressureSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		while (bmp280_is_measuring(&PressureHandle));

		if (bmp280_read_float(&PressureHandle, temperature, pressure, &humidity)==false)
		{
			status =  PRESSURE_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		__enable_irq(); // Clear PRIMASK
	}
	else
	{
		*pressure=0.0;
		*temperature=0.0;
		status =  PRESSURE_NO_DATA;
	}

	return status;
}
/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_PRESSURE_Private_Functions
 * @{
 */

/**
 * @brief PRESSURE MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
__weak void BSP_PRESSURE_MspInit(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable the Keys (SPI) interface clock */
	PRESSURE_CLK_ENABLE();

	/* Enable GPIO clocks */
	PRESSURE_CS_GPIO_CLK_ENABLE();
	PRESSURE_CLK_GPIO_CLK_ENABLE();
	PRESSURE_MISO_GPIO_CLK_ENABLE();
	PRESSURE_MOSI_GPIO_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* PRESSURE CS GPIO pin configuration  */
	gpio_init_structure.Pin       = PRESSURE_CS_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull      = GPIO_NOPULL;
	gpio_init_structure.Speed     = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(PRESSURE_CS_GPIO_PORT, &gpio_init_structure);

	HAL_GPIO_WritePin(PRESSURE_CS_GPIO_PORT, PRESSURE_CS_PIN, GPIO_PIN_SET );

	/* PRESSURE CLK GPIO pin configuration  */
	gpio_init_structure.Pin       = PRESSURE_CLK_PIN;
	gpio_init_structure.Mode      = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull      = GPIO_NOPULL;
	gpio_init_structure.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(PRESSURE_CLK_GPIO_PORT, &gpio_init_structure);

	/* PRESSURE MISO GPIO pin configuration  */
	gpio_init_structure.Pin       = PRESSURE_MISO_PIN;
	gpio_init_structure.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(PRESSURE_MISO_GPIO_PORT, &gpio_init_structure);

	/* PRESSURE MISO GPIO pin configuration  */
	gpio_init_structure.Pin       = PRESSURE_MOSI_PIN;
	gpio_init_structure.Alternate = GPIO_AF5_SPI2;
	HAL_GPIO_Init(PRESSURE_MOSI_GPIO_PORT, &gpio_init_structure);

	/*##-3- Configure the NVIC for SPI2 #########################################*/
	/* NVIC configuration for SPI2 interrupt */
	HAL_NVIC_SetPriority(SPI2_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(SPI2_IRQn);
}

/**
 * @brief PRESSURE MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_PRESSURE_MspDeInit(void)
{
	/*##-1- Disable the NVIC for QSPI ###########################################*/
	HAL_NVIC_DisableIRQ(SPI2_IRQn);

	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* De-Configure QSPI pins */
	HAL_GPIO_DeInit(PRESSURE_CS_GPIO_PORT, PRESSURE_CS_PIN);
	HAL_GPIO_DeInit(PRESSURE_CLK_GPIO_PORT, PRESSURE_CLK_PIN);
	HAL_GPIO_DeInit(PRESSURE_MISO_GPIO_PORT, PRESSURE_MISO_PIN);
	HAL_GPIO_DeInit(PRESSURE_MOSI_GPIO_PORT, PRESSURE_MOSI_PIN);
	/* Disable the QuadSPI memory interface clock */

	PRESSURE_CLK_DISABLE();
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

