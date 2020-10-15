/**
 ******************************************************************************
 * @file    stm32746g_discovery_acc_gyro.c
 * @author  dimercur
 * @brief   This file includes a standard driver for lsm6ds3 sensor
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
#include "stm32746g_discovery_acc_gyro.h"
//#include "stm32746g_discovery_acc_gyro_conf.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_ACC_GYRO STM32746G-Discovery ACC_GYRO
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_ACC_GYRO_Private_Variables STM32746G_DISCOVERY ACC_GYRO Private Variables
 * @{
 */
static I2C_HandleTypeDef I2CHandle;

uint8_t KEYSBuffer;

static int32_t platform_write(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
		uint16_t len);

lsm6ds3_ctx_t sensorCtx;
static char accSensorEnabled=0;

/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_ACC_GYRO_Private_Functions STM32746G_DISCOVERY ACC_GYRO Private Functions
 * @{
 */


/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_ACC_GYRO_Exported_Functions STM32746G_DISCOVERY ACC_GYRO Exported Functions
 * @{
 */

/**
 * @brief  Initializes interface for magnetic sensor.
 * @retval Initialization status
 */
uint8_t BSP_ACC_GYRO_Init(void)
{ 
	uint8_t whoamI,rst;
	//lsm6ds3_int1_route_t int_1_reg;

	/* I2C Configuration */
	I2CHandle.Instance = ACC_GYRO_I2Cx;

	/* Call the DeInit function to reset the driver */
	if (HAL_I2C_DeInit(&I2CHandle) != HAL_OK)
	{
		return ACC_ERROR;
	}

	/* System level initialization */
	BSP_ACC_GYRO_MspInit();

	I2CHandle.Init.Timing          = ACC_GYRO_I2C_TIMING;
	I2CHandle.Init.OwnAddress1     = 0xFF;
	I2CHandle.Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
	I2CHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CHandle.Init.OwnAddress2     = 0xFF;
	I2CHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2CHandle.Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

	if (HAL_I2C_Init(&I2CHandle) != HAL_OK)
	{
		return ACC_ERROR;
	}

	/* Enable the Analog I2C Filter */
	HAL_I2CEx_ConfigAnalogFilter(&I2CHandle,I2C_ANALOGFILTER_ENABLE);

	sensorCtx.write_reg = platform_write;
	sensorCtx.read_reg = platform_read;
	sensorCtx.handle = &I2CHandle;

	/*
	 *  Check device ID
	 */
	lsm6ds3_device_id_get(&sensorCtx, &whoamI);
	if (whoamI != LSM6DS3_ID)
	{
		return ACC_ERROR;
	}

	/*
	 * Restore default configuration
	 */
	lsm6ds3_reset_set(&sensorCtx, PROPERTY_ENABLE);
	do {
		lsm6ds3_reset_get(&sensorCtx, &rst);
	} while (rst);

	/*
	 * Enable Block Data Update
	 */
	lsm6ds3_block_data_update_set(&sensorCtx, PROPERTY_ENABLE);

	/*
	 * Set full scale
	 */
	lsm6ds3_xl_full_scale_set(&sensorCtx, LSM6DS3_4g);
	lsm6ds3_gy_full_scale_set(&sensorCtx, LSM6DS3_1000dps);

	/*
	 * Set Output Data Rate
	 */
	lsm6ds3_xl_data_rate_set(&sensorCtx, LSM6DS3_XL_ODR_833Hz);
	lsm6ds3_gy_data_rate_set(&sensorCtx, LSM6DS3_GY_ODR_833Hz);

	/*
	 * Enable interrupt generation on DRDY INT1 pin
	 */
	//	lsm6ds3_pin_int1_route_get(&sensorCtx, &int_1_reg);
	//	int_1_reg.int1_drdy_g = PROPERTY_ENABLE;
	//	int_1_reg.int1_drdy_xl = PROPERTY_ENABLE;
	//	lsm6ds3_pin_int1_route_set(&sensorCtx, &int_1_reg);

	accSensorEnabled = 1;
	return ACC_OK;
}

/**
 * @brief  De-Initializes the magnetic sensor interface.
 * @retval De-init status
 */
uint8_t BSP_ACC_GYRO_DeInit(void)
{ 
	BSP_ACC_GYRO_MspDeInit();
	accSensorEnabled =0;

	return ACC_OK;
}

/**
 * @brief  Reads acceleration values
 * @retval Read status
 */
uint8_t BSP_ACC_ReadRawValues(axis3bit16_t *data_raw_acceleration)
{
	uint8_t status= ACC_OK;
	uint8_t reg;

	if (accSensorEnabled)
	{
		/* TODO: Supprimer apres test */
	//	__disable_irq(); // Set PRIMASK

		/*
		 * Read status register
		 */
		lsm6ds3_xl_flag_data_ready_get(&sensorCtx, &reg);

		if (reg)
		{
			/*
			 * Read accelerometer field data
			 */
			memset(data_raw_acceleration->u8bit, 0, 3 * sizeof(int16_t));
			lsm6ds3_acceleration_raw_get(&sensorCtx, data_raw_acceleration->u8bit);
		}

		/* TODO: Supprimer apres test */
	//	__enable_irq(); // Clear PRIMASK
	} else status = ACC_ERROR;

	return status;
}

/**
 * @brief  Reads acceleration values
 * @retval Read status
 */
uint8_t BSP_GYRO_ReadRawValues(axis3bit16_t *data_raw_angular_rate)
{
	uint8_t status= ACC_OK;
	uint8_t reg;

	if (accSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		lsm6ds3_gy_flag_data_ready_get(&sensorCtx, &reg);

		if (reg)
		{
			/*
			 * Read gyroscope field data
			 */
			memset(data_raw_angular_rate->u8bit, 0, 3 * sizeof(int16_t));
			lsm6ds3_angular_rate_raw_get(&sensorCtx, data_raw_angular_rate->u8bit);
		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK
	} else status = ACC_ERROR;

	return status;
}

/**
 * @brief  Reads acceleration values
 * @retval Read status
 */
uint8_t BSP_ACC_ReadValues(acceleration_t *acceleration)
{
	axis3bit16_t data_raw_acceleration;
	uint8_t status= ACC_OK;

	if (accSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		status = BSP_ACC_ReadRawValues(&data_raw_acceleration);

		if (status == ACC_OK)
		{
			acceleration->x =
					lsm6ds3_from_fs2g_to_mg(data_raw_acceleration.i16bit[0]);
			acceleration->y =
					lsm6ds3_from_fs2g_to_mg(data_raw_acceleration.i16bit[1]);
			acceleration->z =
					lsm6ds3_from_fs2g_to_mg(data_raw_acceleration.i16bit[2]);

		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK
	} else status = ACC_ERROR;

	return status;
}

/**
 * @brief  Reads acceleration values
 * @retval Read status
 */
uint8_t BSP_GYRO_ReadValues(angularRate_t *angular_rate)
{
	axis3bit16_t data_raw_angular_rate;
	uint8_t status= ACC_OK;

	if (accSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		status = BSP_GYRO_ReadRawValues(&data_raw_angular_rate);

		if (status == ACC_OK)
		{
			/*
			 * Read gyroscope field data
			 */

			angular_rate->x =
					lsm6ds3_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[0]);
			angular_rate->y =
					lsm6ds3_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[1]);
			angular_rate->z =
					lsm6ds3_from_fs2000dps_to_mdps(data_raw_angular_rate.i16bit[2]);

		}

		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK
	} else status = ACC_ERROR;

	return status;
}

/**
 * @brief  Reads T° values in °C
 * @retval Read status
 */
uint8_t BSP_ACC_ReadTemperature(float *temperature_degC)
{
	uint8_t status= ACC_OK;
	uint8_t reg;
	axis1bit16_t data_raw_temperature;

	if (accSensorEnabled)
	{
		/* TODO: Supprimer apres test */
		//__disable_irq(); // Set PRIMASK

		/*
		 * Read output only if new value is available
		 */
		lsm6ds3_temp_flag_data_ready_get(&sensorCtx, &reg);

		if (reg)
		{
			/*
			 * Read temperature data
			 */
			memset(data_raw_temperature.u8bit, 0x00, sizeof(int16_t));
			lsm6ds3_temperature_raw_get(&sensorCtx, data_raw_temperature.u8bit);
			*temperature_degC = lsm6ds3_from_lsb_to_celsius(data_raw_temperature.i16bit);

		}
		else
		{
			status =  ACC_NO_DATA;
		}



		/* TODO: Supprimer apres test */
		//__enable_irq(); // Clear PRIMASK
	} else status = ACC_ERROR;

	return status;
}

/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_ACC_GYRO_Private_Functions
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

	HAL_I2C_Mem_Write(handle, LSM6DS3_I2C_ADD_H, reg,
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

	HAL_I2C_Mem_Read(handle, LSM6DS3_I2C_ADD_H, reg,
			I2C_MEMADD_SIZE_8BIT, bufp, len, 1000);


	return 0;
}

/**
 * @brief ACC Gyro MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
__weak void BSP_ACC_GYRO_MspInit(void)
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

	//	/* IT DRDY GPIO pin configuration  */
	//	gpio_init_structure.Pin       = ACC_GYRO_DRDY_PIN;
	//	gpio_init_structure.Pull 	  = GPIO_NOPULL;
	//	gpio_init_structure.Speed 	  = GPIO_SPEED_FAST;
	//	gpio_init_structure.Mode 	  = GPIO_MODE_IT_RISING;
	//	HAL_GPIO_Init(ACC_GYRO_DRDY_GPIO_PORT, &gpio_init_structure);

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

	//	/* Enable and set EXTI9-5 Interrupt to the lowest priority */
	//	HAL_NVIC_SetPriority(ACC_GYRO_DRDY_EXTI_IRQn, 0xFF, 0);
	//	HAL_NVIC_EnableIRQ(ACC_GYRO_DRDY_EXTI_IRQn);
}

/**
 * @brief ACC GYRO MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_ACC_GYRO_MspDeInit(void)
{
	/*##-1- Disable NVIC for IT_LIS2MDL ###########################################*/
	//	HAL_NVIC_DisableIRQ(SPI2_IRQn);
	ACC_GYRO_I2Cx_FORCE_RESET();
	ACC_GYRO_I2Cx_RELEASE_RESET();

	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* De-Configure QSPI pins */
	HAL_GPIO_DeInit(ACC_GYRO_I2Cx_SDA_GPIO_PORT, ACC_GYRO_I2Cx_SDA_PIN);
	HAL_GPIO_DeInit(ACC_GYRO_I2Cx_SCL_GPIO_PORT, ACC_GYRO_I2Cx_SCL_PIN);

	HAL_NVIC_DisableIRQ(ACC_GYRO_DRDY_EXTI_IRQn);

	ACC_GYRO_I2Cx_CLK_DISABLE();
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

