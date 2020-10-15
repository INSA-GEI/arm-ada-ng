/*
 * memory_mapping.h
 *
 *  Created on: 19 juin 2019
 *      Author: dimercur
 */
#include "stm32746g_discovery_sdram.h"

#ifndef CONFIGURATION_MEMORY_MAPPING_H_
#define CONFIGURATION_MEMORY_MAPPING_H_

#define RGB565_BYTE_PER_PIXEL     2
#define ARBG8888_BYTE_PER_PIXEL   4

/**
  * @brief  LCD FB_StartAddress
  * LCD Frame buffer start address : starts at beginning of SDRAM
  */
extern const uint32_t _framebuffer_foreground_start;
extern const uint32_t _framebuffer_background_start;

//#define LCD_FRAME_BUFFER          	SDRAM_DEVICE_ADDR
#define LCD_FRAME_BUFFER_LAYER_FOREGROUND  	((uint32_t)&_framebuffer_foreground_start)
#define LCD_FRAME_BUFFER_LAYER_BACKGROUND 	((uint32_t)&_framebuffer_background_start)
/**
  * @brief  Camera frame buffer start address
  * Assuming LCD frame buffer is of size 480x272 and format RGB565 (16 bits per pixel) with 2 layers.
  */
extern uint32_t _memory_sram_start;
#define SDRAM_WRITE_READ_ADDR       ((uint32_t)&_memory_sram_start)

/**
  * @brief  SDRAM Write read buffer start address after CAM Frame buffer
  * Assuming Camera frame buffer is of size 640x480 and format RGB565 (16 bits per pixel).
  */

#define SDRAM_WRITE_READ_ADDR_OFFSET ((uint32_t)0x0800)
#define SRAM_WRITE_READ_ADDR_OFFSET  SDRAM_WRITE_READ_ADDR_OFFSET

#define AUDIO_REC_START_ADDR         SDRAM_WRITE_READ_ADDR
#define AUDIO_REC_END_ADDR           ((uint32_t)(SDRAM_WRITE_READ_ADDR+0x1000)

/* The Audio file is flashed with ST-Link Utility @ flash address =  AUDIO_SRC_FILE_ADDRESS */
#define AUDIO_SRC_FILE_ADDRESS       0x08080000   /* Audio file address in flash */

#endif /* CONFIGURATION_MEMORY_MAPPING_H_ */
