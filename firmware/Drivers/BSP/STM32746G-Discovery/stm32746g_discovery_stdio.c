/**
 ******************************************************************************
 * @file    stm32746g_discovery_stdio.c
 * @author  dimercur
 * @brief   This file includes a standard driver for standard input/output over COM1 (USART1)
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
#include <stm32746g_discovery_stdio.h>

/** @addtogroup BSP
 * @{
 */

/** @addtogroup STM32746G_DISCOVERY
 * @{
 */

/** @defgroup STM32746G_DISCOVERY_STDIO STM32746G-Discovery stdio
 * @{
 */


/* Private variables ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_STDIO_Private_Variables STM32746G_DISCOVERY STDIO Private Variables
 * @{
 */
static UART_HandleTypeDef UARTHandle;

char stdinBuffer[100];
char stdoutBuffer[100];
/**
 * @}
 */



/* Private functions ---------------------------------------------------------*/

/** @defgroup STM32746G_DISCOVERY_STDIO_Private_Functions STM32746G_DISCOVERY STDIO Private Functions
 * @{
 */
__weak void BSP_STDIO_MspInit(void);
__weak void BSP_STDIO_MspDeInit(void);

/**
 * @}
 */

/** @defgroup STM32746G_DISCOVERY_STDIO_Exported_Functions STM32746G_DISCOVERY STDIO Exported Functions
 * @{
 */

/**
 * @brief  Initializes STDIO interface.
 * @retval STDIO status
 */
uint8_t BSP_STDIO_Init(void)
{ 
	UARTHandle.Instance = USART1;

	/* Call the DeInit function to reset the driver */
	if (HAL_UART_DeInit(&UARTHandle) != HAL_OK)
	{
		return STDIO_ERROR;
	}

	/* COM1 initialization */
	UARTHandle.Init.BaudRate = 115200;
	UARTHandle.Init.Mode = USART_MODE_TX_RX;
	UARTHandle.Init.OverSampling = USART_OVERSAMPLING_16;
	UARTHandle.Init.Parity = USART_PARITY_NONE;
	UARTHandle.Init.StopBits = USART_STOPBITS_1;
	UARTHandle.Init.WordLength = USART_WORDLENGTH_8B;

	if (BSP_COM_Init(COM1, &UARTHandle) != HAL_OK)
	{
		return STDIO_ERROR;
	}

	BSP_STDIO_MspInit();

	HAL_UART_Receive_IT(&UARTHandle,(uint8_t*)stdinBuffer, 1);

	return STDIO_OK;
}

/**
 * @brief  De-Initializes STDIO interface.
 * @retval STDIO status
 */
uint8_t BSP_STDIO_DeInit(void)
{ 
	/* Call the DeInit function to reset the driver */
	if (BSP_COM_DeInit(COM1, &UARTHandle) != HAL_OK)
	{
		return STDIO_ERROR;
	}

	BSP_STDIO_MspDeInit();

	return STDIO_OK;
}

/**
 * @brief  Send data
 * @retval STDIO status
 */
uint8_t BSP_STDIO_SendData   (uint8_t* data, uint16_t len)
{
	uint8_t status;

	for (int i=0; i<len; i++)
	{
		stdoutBuffer[i] = (char)data[i];
	}

	status = HAL_UART_Transmit(&UARTHandle, (uint8_t*)stdoutBuffer, len, 100);

	if (status != HAL_OK)
	{
		return STDIO_ERROR;
	}

	return STDIO_OK;
}

void BSP_STDIO_IRQHandler	(void)
{
	HAL_UART_IRQHandler(&UARTHandle);
}

__weak void BSP_STDIO_DataReceived	(char* data, uint16_t length)
{
	//volatile uint8_t status;

	for (int i=0; i<length;i++)
	{
		stdoutBuffer[i] = data[i];
	}

	HAL_UART_Transmit(&UARTHandle, (uint8_t*)stdoutBuffer, length, 100);

	HAL_UART_Receive_IT(&UARTHandle,(uint8_t*)stdinBuffer, 1);
}

/**
 * @}
 */

/** @addtogroup STM32746G_DISCOVERY_STDIO_Private_Functions
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
__weak void BSP_STDIO_MspInit(void)
{
	/*##-3- Configure the NVIC for USART1 #########################################*/
	/* NVIC configuration for USART1 interrupt */
	HAL_NVIC_SetPriority(DISCOVERY_COM1_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(DISCOVERY_COM1_IRQn);
}

/**
 * @brief WIFI MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
__weak void BSP_STDIO_MspDeInit(void)
{
	/*##-1- Disable the NVIC for WIFI ###########################################*/
	HAL_NVIC_DisableIRQ(DISCOVERY_COM1_IRQn);
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

