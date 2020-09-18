/**
 ******************************************************************************
 * @file    stm32746g_discovery_mag.c
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
#include "stm32746g_discovery_mag.h"
//#include "stm32746g_discovery_mag_conf.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_MAG STM32746G-Discovery MAG
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_MAG_Private_Variables STM32746G_DISCOVERY MAG Private Variables
 * @{
 */
static I2C_HandleTypeDef I2CHandle;

uint8_t KEYSBuffer;

static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);

lis2mdl_ctx_t magCtx;

static char magSensorEnabled=0;
/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_MAG_Private_Functions STM32746G_DISCOVERY MAG Private Functions
 * @{
 */


/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_MAG_Exported_Functions STM32746G_DISCOVERY MAG Exported Functions
 * @{
 */

/**
 * @brief  Initializes interface for magnetic sensor.
 * @retval Initialization status
 */
uint8_t BSP_MAG_Init(void)
{ 
	uint8_t whoamI,rst;

	/* I2C Configuration */
	I2CHandle.Instance = MAG_I2Cx;

	/* Call the DeInit function to reset the driver */
	if (HAL_I2C_DeInit(&I2CHandle) != HAL_OK)
	{
		return MAG_ERROR;
	}

	/* System level initialization */
	BSP_MAG_MspInit();

	I2CHandle.Instance             = MAG_I2Cx;
	I2CHandle.Init.Timing          = MAG_I2C_TIMING;
	I2CHandle.Init.OwnAddress1     = 0xFF;
	I2CHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2CHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CHandle.Init.OwnAddress2     = 0xFF;
	I2CHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2CHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&I2CHandle) != HAL_OK)
	{
		return MAG_ERROR;
	}

	/* Enable the Analog I2C Filter */
	//HAL_I2CEx_ConfigAnalogFilter(&I2CHandle,I2C_ANALOGFILTER_ENABLE);

	magCtx.write_reg = platform_write;
	magCtx.read_reg = platform_read;
	magCtx.handle = &I2CHandle;

	/*
	 *  Check device ID
	 */
	lis2mdl_device_id_get(&magCtx, &whoamI);
	if (whoamI != LIS2MDL_ID)
	{
		return MAG_ERROR;
	}

	/*
	 *  Restore default configuration
	 */
	lis2mdl_reset_set(&magCtx, PROPERTY_ENABLE);
	do {
		lis2mdl_reset_get(&magCtx, &rst);
	} while (rst);

	/*
	 *  Enable Block Data Update
	 */
	lis2mdl_block_data_update_set(&magCtx, PROPERTY_ENABLE);

	/*
	 * Set Output Data Rate
	 */
	lis2mdl_data_rate_set(&magCtx, LIS2MDL_ODR_100Hz);

	/*
	 * Set / Reset sensor mode
	 */
	lis2mdl_set_rst_mode_set(&magCtx, LIS2MDL_SENS_OFF_CANC_EVERY_ODR);

	/*
	 * Enable temperature compensation
	 */
	lis2mdl_offset_temp_comp_set(&magCtx, PROPERTY_ENABLE);

	/*
	 * Set Low-pass bandwidth to ODR/4
	 */
	lis2mdl_low_pass_bandwidth_set(&magCtx, LIS2MDL_ODR_DIV_4);

	/*
	 * Set device in continuous mode
	 */
	lis2mdl_operating_mode_set(&magCtx, LIS2MDL_CONTINUOUS_MODE);

	/*
	 * Enable interrupt generation on new data ready
	 */
	lis2mdl_drdy_on_pin_set(&magCtx, PROPERTY_ENABLE);

	magSensorEnabled=1;
	return MAG_OK;
}

/**
 * @brief  De-Initializes the magnetic sensor interface.
 * @retval De-init status
 */
uint8_t BSP_MAG_DeInit(void)
{ 
	BSP_MAG_MspDeInit();

	magSensorEnabled=0;
	return MAG_OK;
}

/**
 * @brief  Reads magnetic values
 * @retval Read status
 */
uint8_t BSP_MAG_ReadRawValues(axis3bit16_t *data_raw_magnetic)
{
	uint8_t status= MAG_OK;
	uint8_t reg;

	if (magSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		lis2mdl_mag_data_ready_get(&magCtx, &reg);
		if (reg)
		{
			/*
			 * Read magnetic field data
			 */
			memset(data_raw_magnetic->u8bit, 0x00, 3 * sizeof(int16_t));
			lis2mdl_magnetic_raw_get(&magCtx, data_raw_magnetic->u8bit);
		}
		else
		{
			status =  MAG_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK
	}
	else status = MAG_ERROR;

	return status;
}

/**
 * @brief  Reads magnetic values in mgauss
 * @retval Read status
 */
uint8_t BSP_MAG_ReadValues(magnetic_t *magnetic)
{
	uint8_t status= MAG_OK;
	uint8_t reg;
	axis3bit16_t data_raw_magnetic;

	if (magSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		lis2mdl_mag_data_ready_get(&magCtx, &reg);
		if (reg)
		{
			/*
			 * Read magnetic field data
			 */
			memset(data_raw_magnetic.u8bit, 0x00, 3 * sizeof(int16_t));
			lis2mdl_magnetic_raw_get(&magCtx, data_raw_magnetic.u8bit);

			magnetic->x = lis2mdl_from_lsb_to_mgauss( data_raw_magnetic.i16bit[0]);
			magnetic->y = lis2mdl_from_lsb_to_mgauss( data_raw_magnetic.i16bit[1]);
			magnetic->z = lis2mdl_from_lsb_to_mgauss( data_raw_magnetic.i16bit[2]);
		}
		else
		{
			status =  MAG_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK

	}
	else status = MAG_ERROR;

	return status;
}

/**
 * @brief  Reads T° values in °C
 * @retval Read status
 */
uint8_t BSP_MAG_ReadTemperature(float *temperature_degC)
{
	uint8_t status= MAG_OK;
	uint8_t reg;
	axis1bit16_t data_raw_temperature;

	if (magSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		lis2mdl_mag_data_ready_get(&magCtx, &reg);
		if (reg)
		{
			/*
			 * Read temperature data
			 */
			memset(data_raw_temperature.u8bit, 0x00, sizeof(int16_t));
			lis2mdl_temperature_raw_get(&magCtx, data_raw_temperature.u8bit);
			*temperature_degC = lis2mdl_from_lsb_to_celsius(data_raw_temperature.i16bit);

		}
		else
		{
			status =  MAG_NO_DATA;
		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK

	}
	else status = MAG_ERROR;

	return status;
}

/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_KEYS_Private_Functions
 * @{
 */


/*
 * @brief  Write generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to write
 * @param  bufp      pointer to data to write in register reg
 * @param  len       number of consecutive register to write
 *
 */
static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len)
{
	/* Write multiple command */
	reg |= 0x80;
	HAL_I2C_Mem_Write(handle, LIS2MDL_I2C_ADD, reg,
			I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);

	return 0;
}

/*
 * @brief  Read generic device register (platform dependent)
 *
 * @param  handle    customizable argument. In this examples is used in
 *                   order to select the correct sensor bus handler.
 * @param  reg       register to read
 * @param  bufp      pointer to buffer that store the data read
 * @param  len       number of consecutive register to read
 *
 */
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len)
{
	/* Read multiple command */
	reg |= 0x80;
	HAL_I2C_Mem_Read(handle, LIS2MDL_I2C_ADD, reg,
			I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);

	return 0;
}

/**
 * @brief MAG MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
__weak void BSP_MAG_MspInit(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	DISCOVERY_EXT_I2Cx_SCL_SDA_GPIO_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* KEYS CS GPIO pin configuration  */
	gpio_init_structure.Pin = DISCOVERY_EXT_I2Cx_SCL_PIN;
	gpio_init_structure.Mode = GPIO_MODE_AF_OD;
	gpio_init_structure.Pull = GPIO_PULLUP;
	gpio_init_structure.Speed = GPIO_SPEED_FAST;
	gpio_init_structure.Alternate = DISCOVERY_EXT_I2Cx_SCL_SDA_AF;
	HAL_GPIO_Init(DISCOVERY_EXT_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

	/* Configure I2C Rx as alternate function */
	gpio_init_structure.Pin = DISCOVERY_EXT_I2Cx_SDA_PIN;
	HAL_GPIO_Init(DISCOVERY_EXT_I2Cx_SCL_SDA_GPIO_PORT, &gpio_init_structure);

	/* IT DRDY GPIO pin configuration  */
	gpio_init_structure.Pin       = MAG_DRDY_PIN;
	gpio_init_structure.Pull 	  = GPIO_NOPULL;
	gpio_init_structure.Speed 	  = GPIO_SPEED_FAST;
	gpio_init_structure.Mode 	  = GPIO_MODE_IT_RISING;
	HAL_GPIO_Init(MAG_DRDY_GPIO_PORT, &gpio_init_structure);

	/*##-3- Configure NVIC for IT_LIS2MDL #########################################*/
	/* NVIC configuration for SPI2 interrupt */
	//	HAL_NVIC_SetPriority(I2C1_IRQn, 0x0F, 0);
	//	HAL_NVIC_EnableIRQ(I2C1_  SPI2_IRQn);


	/*** Configure the I2C peripheral ***/
	/* Enable I2C clock */
	DISCOVERY_EXT_I2Cx_CLK_ENABLE();

	/* Force the I2C peripheral clock reset */
	DISCOVERY_EXT_I2Cx_FORCE_RESET();

	/* Release the I2C peripheral clock reset */
	DISCOVERY_EXT_I2Cx_RELEASE_RESET();

	/* Enable and set I2Cx Interrupt to a lower priority */
	HAL_NVIC_SetPriority(DISCOVERY_EXT_I2Cx_EV_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DISCOVERY_EXT_I2Cx_EV_IRQn);

	/* Enable and set I2Cx Interrupt to a lower priority */
	HAL_NVIC_SetPriority(DISCOVERY_EXT_I2Cx_ER_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DISCOVERY_EXT_I2Cx_ER_IRQn);

	/* Enable and set EXTI9-5 Interrupt to the lowest priority */
	HAL_NVIC_SetPriority(MAG_DRDY_EXTI_IRQn, 0xFF, 0);
	HAL_NVIC_EnableIRQ(MAG_DRDY_EXTI_IRQn);
}

/**
 * @brief MAG MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_MAG_MspDeInit(void)
{
	/*##-1- Disable NVIC for IT_LIS2MDL ###########################################*/
	//	HAL_NVIC_DisableIRQ(SPI2_IRQn);
	MAG_I2Cx_FORCE_RESET();
	MAG_I2Cx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* De-Configure QSPI pins */
	HAL_GPIO_DeInit(MAG_I2Cx_SDA_GPIO_PORT, MAG_I2Cx_SDA_PIN);
	HAL_GPIO_DeInit(MAG_I2Cx_SCL_GPIO_PORT, MAG_I2Cx_SCL_PIN);

	HAL_NVIC_DisableIRQ(MAG_DRDY_EXTI_IRQn);
	MAG_I2Cx_CLK_DISABLE();
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

