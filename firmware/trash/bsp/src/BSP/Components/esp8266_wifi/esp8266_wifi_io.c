/**
 ******************************************************************************
 * @file    esp8266_wifi_io.c
 * @author  dimercur
 * @brief   This file contains the common defines and functions prototypes for
 *          the stm32746g_discovery_esp_wifi.c driver.
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

#include "stm32f7xx_hal.h"
#include "esp8266_wifi_conf.h"
#include "esp8266_wifi_io.h"
#include "esp8266_wifi.h"

USART_HandleTypeDef _WIFI_USART;

/**
 * @brief  Initializes WIFI interface.
 * @retval WIFI status
 */
uint8_t ESP8266_WIFI_IO_Init(Wifi_t *wifi)
{
	_WIFI_USART.Instance = USART6;

	/* Call the DeInit function to reset the driver */
	if (HAL_USART_DeInit(&_WIFI_USART) != HAL_OK) {
		return WIFI_ERROR;
	}

	/* System level initialization */
	ESP8266_WIFI_IO_MspInit();

	/* SPI2 initialization */
	_WIFI_USART.Init.BaudRate = 115200;
	_WIFI_USART.Init.Mode = USART_MODE_TX_RX;
	_WIFI_USART.Init.OverSampling = USART_OVERSAMPLING_16;
	_WIFI_USART.Init.Parity = USART_PARITY_NONE;
	_WIFI_USART.Init.StopBits = USART_STOPBITS_1;
	_WIFI_USART.Init.WordLength = USART_WORDLENGTH_8B;

	if (HAL_USART_Init(&_WIFI_USART) != HAL_OK) {
		return WIFI_ERROR;
	}

	HAL_USART_Receive_IT(&_WIFI_USART, &(wifi->usartBuff), 1);
	ESP8266_WIFI_IO_RxClear(wifi);
	ESP8266_WIFI_IO_TxClear(wifi);

	return WIFI_OK;
}

/**
 * @brief  De-Initializes WIFI interface.
 * @retval WIFIstatus
 */
uint8_t ESP8266_WIFI_IO_DeInit(Wifi_t *wifi) {
	_WIFI_USART.Instance = USART6;

	HAL_USART_Receive_IT(&_WIFI_USART, &(wifi->usartBuff), 0);
	ESP8266_WIFI_IO_RxClear(wifi);
	ESP8266_WIFI_IO_TxClear(wifi);

	/* Call the DeInit function to reset the driver */
	if (HAL_USART_DeInit(&_WIFI_USART) != HAL_OK) {
		return WIFI_ERROR;
	}

	/* System level De-initialization */
	ESP8266_WIFI_IO_MspDeInit();

	return WIFI_OK;
}

/**
 * @brief WIFI MSP Initialization
 *        This function configures the hardware resources used in this example:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 *           - NVIC configuration for QSPI interrupt
 * @retval None
 */
void ESP8266_WIFI_IO_MspInit(void) {
	GPIO_InitTypeDef gpio_init_structure;

	/*##-1- Enable peripherals and GPIO Clocks #################################*/
	/* Enable the Keys (SPI) interface clock */
	WIFI_CLK_ENABLE();

	/* Enable GPIO clocks */
	WIFI_TX_GPIO_CLK_ENABLE();
	WIFI_RX_GPIO_CLK_ENABLE();

	/*##-2- Configure peripheral GPIO ##########################################*/
	/* WIFI TX GPIO pin configuration  */
	gpio_init_structure.Pin = WIFI_TX_PIN;
	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull = GPIO_NOPULL;
	gpio_init_structure.Speed = GPIO_SPEED_HIGH;
	gpio_init_structure.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(WIFI_TX_GPIO_PORT, &gpio_init_structure);

	/* WIFI RX GPIO pin configuration  */
	gpio_init_structure.Pin = WIFI_RX_PIN;
	gpio_init_structure.Mode = GPIO_MODE_AF_PP;
	gpio_init_structure.Pull = GPIO_NOPULL;
	gpio_init_structure.Alternate = GPIO_AF8_USART6;
	HAL_GPIO_Init(WIFI_RX_GPIO_PORT, &gpio_init_structure);

	/*##-3- Configure the NVIC for USART6 #########################################*/
	/* NVIC configuration for USART6 interrupt */
	HAL_NVIC_SetPriority(USART6_IRQn, 0x0F, 0);
	HAL_NVIC_EnableIRQ(USART6_IRQn);
}

/**
 * @brief WIFI MSP De-Initialization
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * @retval None
 */
void ESP8266_WIFI_IO_MspDeInit(void) {
	/*##-1- Disable the NVIC for WIFI ###########################################*/
	HAL_NVIC_DisableIRQ(USART6_IRQn);

	/*##-2- Disable peripherals and GPIO Clocks ################################*/
	/* De-Configure WIFI pins */
	HAL_GPIO_DeInit(WIFI_TX_GPIO_PORT, WIFI_TX_PIN);
	HAL_GPIO_DeInit(WIFI_RX_GPIO_PORT, WIFI_RX_PIN);

	/* Disable wifi interface clock */
	WIFI_CLK_DISABLE();
}

//#########################################################################################################
uint8_t ESP8266_WIFI_IO_SendRaw(Wifi_t *wifi, uint8_t *data, uint16_t len) {
	if (len <= _WIFI_TX_SIZE) {
		memcpy(wifi->TxBuffer, data, len);
		if (HAL_USART_Transmit(&_WIFI_USART, data, len, 100) == HAL_OK)
			return WIFI_ERROR;
		else
			return WIFI_ERROR;
	} else
		return WIFI_OK;
}

//#########################################################################################################
void ESP8266_WIFI_IO_RxClear(Wifi_t *wifi) {
	memset(wifi->RxBuffer, 0, _WIFI_RX_SIZE);
	wifi->RxIndex = 0;
	HAL_USART_Receive_IT(&_WIFI_USART, &(wifi->usartBuff), 1);
}
//#########################################################################################################
void ESP8266_WIFI_IO_TxClear(Wifi_t *wifi) {
	memset(wifi->TxBuffer, 0, _WIFI_TX_SIZE);
}
//#########################################################################################################
void ESP8266_WIFI_IO_RxCallBack(void) {
	//+++ at command buffer
	if (Wifi.RxIsData == false) {
		Wifi.RxBuffer[Wifi.RxIndex] = Wifi.usartBuff;
		if (Wifi.RxIndex < _WIFI_RX_SIZE)
			Wifi.RxIndex++;
	}
	//--- at command buffer
	//+++  data buffer
	else {
		if (HAL_GetTick() - Wifi.RxDataLastTime > 50)
			Wifi.RxIsData = false;
		//+++ Calculate Data len after +IPD
		if (Wifi.RxDataLen == 0) {
			//+++ Calculate Data len after +IPD ++++++ Multi Connection OFF
			if (Wifi.TcpIpMultiConnection == false) {
				Wifi.RxBufferForDataTmp[Wifi.RxIndexForDataTmp] =
						Wifi.usartBuff;
				Wifi.RxIndexForDataTmp++;
				if (Wifi.RxBufferForDataTmp[Wifi.RxIndexForDataTmp - 1]
						== ':') {
					Wifi.RxDataConnectionNumber = 0;
					Wifi.RxDataLen = atoi((char*) &Wifi.RxBufferForDataTmp[1]);
				}
			}
			//--- Calculate Data len after +IPD ++++++ Multi Connection OFF
			//+++ Calculate Data len after +IPD ++++++ Multi Connection ON
			else {
				Wifi.RxBufferForDataTmp[Wifi.RxIndexForDataTmp] =
						Wifi.usartBuff;
				Wifi.RxIndexForDataTmp++;
				if (Wifi.RxBufferForDataTmp[2] == ',') {
					Wifi.RxDataConnectionNumber = Wifi.RxBufferForDataTmp[1]
							- 48;
				}
				if ((Wifi.RxIndexForDataTmp > 3)
						&& (Wifi.RxBufferForDataTmp[Wifi.RxIndexForDataTmp - 1]
								== ':'))
					Wifi.RxDataLen = atoi((char*) &Wifi.RxBufferForDataTmp[3]);
			}
			//--- Calculate Data len after +IPD ++++++ Multi Connection ON
		}
		//--- Calculate Data len after +IPD
		//+++ Fill Data Buffer
		else {
			Wifi.RxBufferForData[Wifi.RxIndexForData] = Wifi.usartBuff;
			if (Wifi.RxIndexForData < _WIFI_RX_FOR_DATA_SIZE)
				Wifi.RxIndexForData++;
			if (Wifi.RxIndexForData >= Wifi.RxDataLen) {
				Wifi.RxIsData = false;
				Wifi.GotNewData = true;
			}
		}
		//--- Fill Data Buffer
	}
	//--- data buffer
	HAL_USART_Receive_IT(&_WIFI_USART, &Wifi.usartBuff, 1);

	//+++ check +IPD in At command buffer
	if (Wifi.RxIndex > 4) {
		if ((Wifi.RxBuffer[Wifi.RxIndex - 4] == '+')
				&& (Wifi.RxBuffer[Wifi.RxIndex - 3] == 'I')
				&& (Wifi.RxBuffer[Wifi.RxIndex - 2] == 'P')
				&& (Wifi.RxBuffer[Wifi.RxIndex - 1] == 'D')) {
			memset(Wifi.RxBufferForDataTmp, 0, sizeof(Wifi.RxBufferForDataTmp));
			Wifi.RxBuffer[Wifi.RxIndex - 4] = 0;
			Wifi.RxBuffer[Wifi.RxIndex - 3] = 0;
			Wifi.RxBuffer[Wifi.RxIndex - 2] = 0;
			Wifi.RxBuffer[Wifi.RxIndex - 1] = 0;
			Wifi.RxIndex -= 4;
			Wifi.RxIndexForData = 0;
			Wifi.RxIndexForDataTmp = 0;
			Wifi.RxIsData = true;
			Wifi.RxDataLen = 0;
			Wifi.RxDataLastTime = HAL_GetTick();
		}
	}
	//--- check +IPD in At command buffer
}

//#########################################################################################################
