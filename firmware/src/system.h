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

#include "stm32f30x.h"

#include "config.h"
#include "version.h"
#include "abi.h"
#include "panic.h"

#include "timer.h"
#include "glcd.h"
#include "packedbmp.h"
#include "unpackbmp.h"
#include "usart.h"
#include "keys.h"
#include "led.h"
#include "potentiometers.h"
#include "rng.h"
#include "audio.h"
#include "sram.h"
//#include "ff.h"
//#include "sd_spi_drv.h"
//#include "stm32303c_eval_spi_sd.h"
#include "l3gd20.h"
#include "lsm303dlhc.h"
#include "console.h"

#include "audio-synth.h"
#include "audio-melody.h"

#include "gui.h"

#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "m_alloc.h"

#include "reprog.h"

extern FILE __stdout;
extern FILE __stdin;
extern FILE __console;
extern FILE __lcd;
extern FILE __stderr;

#endif /* __SYSTEM_H__ */
