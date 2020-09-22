#ifndef	_WIFICONFIG_H
#define	_WIFICONFIG_H

#include "stm32f7xx_hal.h"

#define		_WIFI_USART					WIFIUSARTHandler

#define		_WIFI_RX_SIZE					512
#define		_WIFI_RX_FOR_DATA_SIZE			1024
#define		_WIFI_TX_SIZE					256
#define		_WIFI_TASK_SIZE					512

#define		_WIFI_WAIT_TIME_LOW				1000
#define		_WIFI_WAIT_TIME_MED				10000
#define		_WIFI_WAIT_TIME_HIGH			25000
#define		_WIFI_WAIT_TIME_VERYHIGH		60000

/* Definition for Usart clock resources */
#define WIFI_CLK_ENABLE()            __HAL_RCC_USART6_CLK_ENABLE()
#define WIFI_CLK_DISABLE()           __HAL_RCC_USART6_CLK_DISABLE()
#define WIFI_TX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()
#define WIFI_RX_GPIO_CLK_ENABLE()    __HAL_RCC_GPIOC_CLK_ENABLE()

/* Definition for SPI Pins */
#define WIFI_TX_PIN                GPIO_PIN_6
#define WIFI_TX_GPIO_PORT          GPIOC
#define WIFI_RX_PIN                GPIO_PIN_7
#define WIFI_RX_GPIO_PORT          GPIOC

#endif /* _WIFICONFIG_H */
