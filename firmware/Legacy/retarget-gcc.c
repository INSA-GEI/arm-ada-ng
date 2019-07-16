/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the �Vision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "stm32746g_discovery.h"
#include "stm32746g_discovery_stdio.h"

#include <stdio.h>
#include <time.h>
#include <string.h>

#include "system.h"
#include "console.h"
#include "panic.h"
#include <sys/stat.h>

#include <errno.h>

/* Variables */
extern int errno;
register char* stack_ptr asm("sp");

extern const uint32_t* _dynamicsram_start;
extern const uint32_t* _dynamicsram_end;

FILE __stdout;
FILE __stdin;
FILE __console;
FILE __lcd;
FILE __stderr;

void RETARGET_Init (void)
{
	__stdout._file=1;
	__stdin._file=1;
	__console._file=10;
	__lcd._file=10;
	__stderr._file=2;
}
/* Functions */

int _write (int fd, char *ptr, int len)
{
	int i;

	for (i=0; i<len; i++)
	{
		if (fd == 1)  BSP_STDIO_SendData((uint8_t *)&ptr[i],1);
		if (fd == 2) // used for ADA exception
		{
			BSP_STDIO_SendData((uint8_t *)&ptr[1],1);
			CONSOLE_PrintChar(ptr[i]);
		}
		if (fd == 10) CONSOLE_PrintChar(ptr[i]);
	}

	return len;
}

int _read (int fd, char *ptr, int len)
{
	int count=-1;
	int i;

	for (i=0; i<len; i++)
	{
		if (fd == 1)
		{
			//USART_Receive(USART1, &ptr[i]);
			count++;
		}
	}

	return (count);
}

void _exit(int exit_code)
{
	PANIC_SoftwarePanic("Unexpected exit", "System requests to exit");

	while (1);
}

int _close(int file)
{
	return -1;
}

int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

int _isatty(int file) { return 1; }
int _lseek(int file, int ptr, int dir) { return 0; }

/**
 *_sbrk
 * Increase program data space. Malloc and related functions depend on this
 */

caddr_t _sbrk(int incr)
{
	//extern char end asm("end");
	#define HEAP_BASE_ADDRESS	_dynamicsram_start
	#define HEAP_END_ADDRESS	_dynamicsram_end

	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0)
		heap_end = (char*)HEAP_BASE_ADDRESS;

	prev_heap_end = heap_end;

	if (heap_end + incr > (char*)HEAP_END_ADDRESS)
	{
		errno = ENOMEM;
		return (caddr_t) -1;
	}

	heap_end += incr;

	return (caddr_t) prev_heap_end;
}

void abort (void)
{
	while (1) {}
}

void _ttywrch(int c) {
	BSP_STDIO_SendData((uint8_t*)&c,1);
}


void _sys_exit(int return_code) {
	label:  goto label;  /* endless loop */
}
