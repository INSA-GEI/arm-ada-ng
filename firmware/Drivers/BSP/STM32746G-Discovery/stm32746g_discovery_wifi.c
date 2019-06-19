/**
 ******************************************************************************
 * @file    stm32746g_discovery_esp_wifi.c
 * @author  dimercur
 * @brief   This file includes a standard driver for esp wroom 2 wifi module
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
#include <stm32746g_discovery_wifi.h>

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_ESP_WIFI STM32746G-Discovery esp Wifi
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_ESP_WIFI_Private_Variables STM32746G_DISCOVERY ESP WIFI Private Variables
 * @{
 */
static UART_HandleTypeDef UARTHandle;
char wifiBufferIn[100];
char wifiBufferOut[100];

/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_ESP_WIFI_Private_Functions STM32746G_DISCOVERY Esp Wifi Private Functions
 * @{
 */


/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_ESP_WIFI_Exported_Functions STM32746G_DISCOVERY ESP WIFI Exported Functions
 * @{
 */

/**
 * @brief  Initializes WIFI interface.
 * @retval WIFI status
 */
uint8_t BSP_WIFI_Init(void)
{ 
	UARTHandle.Instance = USART6;

	/* Call the DeInit function to reset the driver */
	if (HAL_UART_DeInit(&UARTHandle) != HAL_OK)
	{
		return WIFI_ERROR;
	}

	/* com2 initialization */
	UARTHandle.Init.BaudRate = 115200;
	UARTHandle.Init.Mode = USART_MODE_TX_RX;
	UARTHandle.Init.OverSampling = USART_OVERSAMPLING_16;
	UARTHandle.Init.Parity = USART_PARITY_NONE;
	UARTHandle.Init.StopBits = USART_STOPBITS_1;
	UARTHandle.Init.WordLength = USART_WORDLENGTH_8B;

	if (BSP_COM_Init(COM2, &UARTHandle) != HAL_OK)
	{
		return WIFI_ERROR;
	}

	/* System level initialization */
	BSP_WIFI_MspInit();

	HAL_UART_Receive_IT(&UARTHandle,(uint8_t*)wifiBufferIn, 1);

	HAL_GPIO_WritePin(WIFI_ENABLE_GPIO_PORT, WIFI_ENABLE_PIN, GPIO_PIN_RESET); /* LE module Wifi consomme trop, on le desactive */
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_PORT, WIFI_RESET_PIN, GPIO_PIN_RESET);

	HAL_Delay(100);
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_PORT, WIFI_RESET_PIN, GPIO_PIN_SET);

	return WIFI_ERROR; /* LE module Wifi consomme trop, on le desactive */
}

/**
 * @brief  De-Initializes WIFI interface.
 * @retval WIFIstatus
 */
uint8_t BSP_WIFI_DeInit(void)
{ 
	/* Call the DeInit function to reset the driver */
	if (BSP_COM_DeInit(COM2, &UARTHandle) != HAL_OK)
	{
		return WIFI_ERROR;
	}

	/* System level De-initialization */
	BSP_WIFI_MspDeInit();

	return WIFI_OK;
}

/**
 * @brief  Send command and get answer
 * @retval WIFI status
 */
uint8_t BSP_WIFI_SendCommand(char* cmd, char* ans)
{
	uint8_t status;

	status = HAL_UART_Transmit(&UARTHandle, (uint8_t*)cmd, strlen(cmd), 100);

	if (status != HAL_OK)
	{
		return WIFI_ERROR;
	}

	return WIFI_OK;
}

void BSP_WIFI_IRQHandler	(void)
{
	HAL_UART_IRQHandler(&UARTHandle);
}

__weak void BSP_WIFI_DataReceived	(char* data, uint16_t length)
{
	//volatile uint8_t status;
	static char *ptr=wifiBufferOut;

	for (int i=0; i<length;i++)
	{
		*ptr++ = data[i];
	}

	HAL_UART_Transmit(&UARTHandle, (uint8_t*)wifiBufferOut, length, 100);

	HAL_UART_Receive_IT(&UARTHandle,(uint8_t*)wifiBufferIn, 1);
}
/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_ESP_WIFI_Private_Functions
 * @{
 */

/**
 * @brief WIFI MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
__weak void BSP_WIFI_MspInit(void)
{
	GPIO_InitTypeDef gpio_init_structure;

	WIFI_ENABLE_CLK_ENABLE();
	WIFI_RESET_CLK_ENABLE();

	/* KEYS CS GPIO pin configuration  */
	gpio_init_structure.Pin = WIFI_RESET_PIN;
	gpio_init_structure.Mode = GPIO_MODE_OUTPUT_OD;
	gpio_init_structure.Pull = GPIO_NOPULL;
	gpio_init_structure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(WIFI_RESET_GPIO_PORT, &gpio_init_structure);

	gpio_init_structure.Pin = WIFI_ENABLE_PIN;
	gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_structure.Pull = GPIO_NOPULL;
	gpio_init_structure.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(WIFI_ENABLE_GPIO_PORT, &gpio_init_structure);

	/*##-3- Configure the NVIC for COM2  #########################################*/
	/* NVIC configuration for COM2 interrupt */
	HAL_NVIC_SetPriority(DISCOVERY_COM2_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DISCOVERY_COM2_IRQn);
}

/**
 * @brief WIFI MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_WIFI_MspDeInit(void)
{
	/*##-1- Disable the NVIC for WIFI ###########################################*/
	HAL_NVIC_DisableIRQ(DISCOVERY_COM2_IRQn);

	HAL_GPIO_WritePin(WIFI_ENABLE_GPIO_PORT, WIFI_ENABLE_PIN, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(WIFI_RESET_GPIO_PORT, WIFI_RESET_PIN, GPIO_PIN_RESET);
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

