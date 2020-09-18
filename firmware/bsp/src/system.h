/******************************************************************************/
/* system.h: Header file for system include                                   */
/*                                                                            */
/******************************************************************************/
/* This program is free software: you can redistribute it and/or modify       */
/*    it under the terms of the GNU General Public License as published by    */
/*    the Free Software Foundation, either version 3 of the License, or       */
/*    (at your option) any later version.                                     */
/*                                                                            */
/*    This program is distributed in the hope that it will be useful,         */
/*    but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/*    GNU General Public License for more details.                            */
/*                                                                            */
/*    You should have received a copy of the GNU General Public License       */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>.   */
/******************************************************************************/
#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_ts.h"
#include "stm32746g_discovery_lcd_dma2d.h"
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_sd.h"
#include "stm32746g_discovery_eeprom.h"
#include "stm32746g_discovery_camera.h"
#include "stm32746g_discovery_audio.h"
#include "stm32746g_discovery_qspi.h"
#include "stm32746g_discovery_keys.h"
#include "stm32746g_discovery_mag.h"
#include "stm32746g_discovery_rng.h"
#include "stm32746g_discovery_acc_gyro.h"
#include "stm32746g_discovery_pressure.h"
#include "stm32746g_discovery_wifi.h"
#include "stm32746g_discovery_stdio.h"

#include "version.h"
#include "abi.h"
#include "panic.h"

#include "console.h"
#include "wrapper.h"
#include "config.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

//#include "m_alloc.h"

extern FILE __stdout;
extern FILE __stdin;
extern FILE __console;
extern FILE __lcd;
extern FILE __stderr;

#endif /* __SYSTEM_H__ */
