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
//register char* stack_ptr asm("sp");

extern const uint32_t* __heap_start;
extern const uint32_t* __heap_end;

FILE __stdout;
FILE __stdin;
FILE __console;
FILE __lcd;
FILE __stderr;

uint8_t *__env[1] = { 0 };
uint8_t **environ = __env;

void RETARGET_Init (void)
{
	__stdout._file=1;
	__stdin._file=1;
	__console._file=10;
	__lcd._file=10;
	__stderr._file=2;
}
/* Functions */

int write (int fd, char *ptr, int len)
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

int read (int fd, char *ptr, int len)
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

/* Functions */


/*int _getpid(void)
{
	return 1;
}*/

int
getpid (void)
{
  return 1;
}

//int _gettimeofday(struct timeval  *ptimeval, void *ptimezone)
int gettimeofday(struct timeval  *ptimeval, void *ptimezone)
{
  errno = ENOSYS;
  return -1;
}

int _kill(int32_t pid, int32_t sig)
{
	errno = ENOSYS;
	return -1;
}

int
kill (int pid, int sig)
{
  errno = EINVAL;
  return -1; /* Always fails */
}

void _exit(int exit_code)
{
	PANIC_SoftwarePanic("Unexpected exit", "System requests to exit");

	while (1);
}

int _fstat(int file, struct stat *st) {
	st->st_mode = S_IFCHR;
	return 0;
}

int fstat (int fd, struct stat*buf)
{
  return _fstat(fd, buf);
}

int _isatty(int file) {
  return 1;
}

int
isatty (int fd)
{
  return 1;
}

off_t _lseek(int file, int ptr, int dir)
{ errno = ESPIPE;
  return -1; }

off_t
lseek (int fd, off_t offset, int whence)
{
   return _lseek(fd, offset, whence);
}
/**
 *_sbrk
 * Increase program data space. Malloc and related functions depend on this
 */

caddr_t sbrk(int incr)
{
	static char *heap_end;
	char *prev_heap_end;

	if (heap_end == 0)
		heap_end = (char*)__heap_start;

	prev_heap_end = heap_end;

	if (heap_end + incr > (char*)__heap_end)
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

int _readlink(const char *path, char *buf, size_t bufsize)
{
  errno = ENOSYS;
  return -1;
}

int _open(const uint8_t *path, int32_t flags, int32_t mode)
{
	errno = ENOSYS;
	return -1;
}

int _close(int file)
{
	return 0;
}

int
close (int fd)
{
  return _close(fd);
}

int _wait(int32_t *status)
{
	errno = ENOSYS;
	return -1;
}

int _unlink(const uint8_t *name)
{
	errno = ENOSYS;
	return -1;
}


int _stat(const uint8_t *file, struct stat *st)
{
	errno = ENOSYS;
	return -1;
}

int _symlink(const char *path1, const char *path2)
{
  errno = ENOSYS;
  return -1;
}

int _link(const uint8_t *old, const uint8_t *new)
{
	errno = ENOSYS;
	return -1;
}

int _fork(void)
{
	errno = ENOSYS;
	return -1;
}

int _execve(const uint8_t *name, uint8_t * const *argv, uint8_t * const *env)
{
	errno = ENOSYS;
	return -1;
}

/* to make libc init happy, we need to provide a _init function.  */

//void _init() __attribute__((section(".init")));


