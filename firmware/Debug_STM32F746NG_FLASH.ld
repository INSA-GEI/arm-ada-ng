/*
******************************************************************************
File:     Debug_STM32F746NG_FLASH.ld
Info:     Generated by Atollic TrueSTUDIO(R) 9.0.1   2018-08-22

Abstract: Linker script for STM32F746NG device
          Set heap size, stack size, stack location, memory areas and 
          sections according to application requirements. 

The MIT License (MIT)
Copyright (c) 2018 STMicroelectronics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = 0x20001400;    /* end of RAM */
__initial_sp = _estack;
StartMemoryAlloc = 0x20000800;

/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size = 0;      /* required amount of heap  */
_Min_Stack_Size = 0x500; /* required amount of stack */

_App_Stack_Size = 0x1000; /* amount of stack for application */
_System_Stack_Size = 0x400; /* amount of stack for system */
__app_stack_start__ = 0x20000000;
__system_stack_start__ = 0x20001000;
__app_stack_end__ = __app_stack_start__ + _App_Stack_Size;
__system_stack_end__ = __system_stack_start__ + _System_Stack_Size;


__external_sram_base_address 	= 0xC0000000;
__qspi_base_address 			= 0x90000000;

__framebuffer_length			= (480*272*2);
__framebuffer_foreground_org	= __external_sram_base_address;
__framebuffer_background_org	= __framebuffer_foreground_org + __framebuffer_length;
__memory_sram_org				= __framebuffer_background_org + __framebuffer_length;
__legacy_sram_org 				= __memory_sram_org;
__legacy_sram_length			= (2*1024*1024);
__dynamic_sram_org 				= __external_sram_base_address + 0x300000;


/* Specify the memory areas */
MEMORY
{
  VECTORS (r)			: ORIGIN = 0x08000000,						LENGTH = 500
  FLASH (rx)      		: ORIGIN = 0x08080000, 						LENGTH = 512K
  MEMORY_BANK1 (rx)		: ORIGIN = __external_sram_base_address, 	LENGTH = 4M
  MEMORY_QSPI (r) 		: ORIGIN = __qspi_base_address, 			LENGTH = 16M
  
  RAM_STACK_APP(rw) 	: ORIGIN = __app_stack_start__, 			LENGTH = _App_Stack_Size
  RAM_STACK(rw)     	: ORIGIN = __system_stack_start__, 			LENGTH = _System_Stack_Size
  RAM_VECTOR(rw)		: ORIGIN = 0x20001400, 						LENGTH = 500
  RAM_SHARED_DATA(rw)	: ORIGIN = 0x20001600, 						LENGTH = 4
  RAM_BUFFERS(rw)		: ORIGIN = (0x20050000-0x2000), 			LENGTH = 8K
  RAM (xrw)				: ORIGIN = 0x2000B000, 						LENGTH = (0x20050000-0x2000-0x2000B000)
  LEGACY_ABI_ENTRYPOINT : ORIGIN = 0x8040000-8, 					LENGTH = 8
  
  /* Memory mapping for external SRAM */
  LCD_FRAMEBUFFER_FOREGROUND 	: ORIGIN = __framebuffer_foreground_org, LENGTH = __framebuffer_length
  LCD_FRAMEBUFFER_BACKGROUND 	: ORIGIN = __framebuffer_background_org, LENGTH = __framebuffer_length
  MEMORY_SRAM					: ORIGIN = __memory_sram_org, 	LENGTH = (4M-__framebuffer_length*2)
  LEGACY_SRAM					: ORIGIN = __legacy_sram_org, 	LENGTH = 2M
  DYNAMIC_SRAM					: ORIGIN = __dynamic_sram_org, 	LENGTH = 1M
}

/* Define output sections */
SECTIONS
{
  /* The startup code goes first into FLASH */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >VECTORS

  /* Legacy entrypoint */
  .legacy_isr_vector :
  {
    KEEP(*(.legacy_isr_vector)) /* Startup code */
  } >LEGACY_ABI_ENTRYPOINT
  
  /* The program code and other data goes into FLASH */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Constant data goes into FLASH */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >FLASH

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } >FLASH
  .ARM : {
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
  } >FLASH

  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  } >FLASH
  .init_array :
  {
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
  } >FLASH
  .fini_array :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
  } >FLASH

  /* used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections goes into RAM, load LMA copy after code */
  .data : 
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH
  
 /* _sidtcmram = LOADADDR(.dtcmram);*/

  /* DTCMRAM section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
 /* .dtcmram :
  {
    . = ALIGN(4);
    _sdtcmram = .; */      /* create a global symbol at dtcmram start */
 /*   *(.dtcmram)
    *(.dtcmram*)
    
    . = ALIGN(4);
    _edtcmram = .;   */    /* create a global symbol at dtcmram end */
 /* } >DTCMRAM AT> FLASH

 _sisram2 = LOADADDR(.sram2);
*/
  /* SRAM2 section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
 /* .sram2 :
  {
   . = ALIGN(4);
    _ssram2 = .;  */     /* create a global symbol at sram2 start */
/*    *(.sram2)
    *(.sram2*)
    
    . = ALIGN(4);
    _esram2 = .;    */   /* create a global symbol at sram2 end */
/*  } >SRAM2 AT> FLASH*/

  /* Uninitialized data section */
  . = ALIGN(4);
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss secion */
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
  } >RAM

  /* User_heap_stack section, used to check that there is enough RAM left */
  ._user_heap_stack :
  {
    . = ALIGN(4);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(4);
  } >RAM

  /* System stack section */
  ._system_stack :
  {
    KEEP(*(SYSSTACK))
  } >RAM_STACK
  
  /* Application stack section */
  ._app_stack :
  {
     KEEP(*(APPSTACK))
  } >RAM_STACK_APP
  
  /* MEMORY bank1 section       */
  .memory_bank1_text :
  {
  	_memory_bank1_start = .;       /* create a global symbol at memory bank1 start */

    _memory_bank1_end = .;       /* create a global symbol at memory bank1 end */
  } >MEMORY_BANK1

  /* MEMORY SRAM section, code must be located here explicitly            */
  /* Example: extern int foo(void) __attribute__ ((section (".mb1text"))); */
  .memory_sram_text :
  {
  	. = ALIGN(4);
  	_memory_sram_start = .;       /* create a global symbol at memory sram start */
  	
    *(.mb1text)        /* .mb1text sections (code) */
    *(.mb1text*)       /* .mb1text* sections (code)  */
    *(.mb1rodata)      /* read-only data (constants) */
    *(.mb1rodata*)
    
    _memory_sram_end = .;       /* create a global symbol at memory sram end */
  } >MEMORY_SRAM
  
  /* FRAMEBUFFER Background Section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
  ._lcd_framebuffer_background :
  {
    . = ALIGN(4);
    _framebuffer_background_start = .;       /* create a global symbol at framebuffer background start */
    
    . = ALIGN(4);
    _framebuffer_background_end = .;       /* create a global symbol at framebuffer background end */
  } >LCD_FRAMEBUFFER_BACKGROUND
  
  /* FRAMEBUFFER Foreground Section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
  ._lcd_framebuffer_foreground :
  {
    . = ALIGN(4);
    _framebuffer_foreground_start = .;       /* create a global symbol at framebuffer foreground start */
    
    . = ALIGN(4);
    _framebuffer_foreground_end = .;       /* create a global symbol at framebuffer foreground end */
  } >LCD_FRAMEBUFFER_FOREGROUND
  
 /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss_dma_buffer :
  {
    KEEP(*(DMA_BUFFERS))
  } >RAM_BUFFERS
  
  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss_vector :
  {
    KEEP(*(VectorTable))
    
    . = ALIGN(4);
  } >RAM_VECTOR
  
  /* Uninitialized data section into RAM memory */
  . = ALIGN(4);
  .bss_shared_data :
  {
    KEEP(*(PRG_ReprogAddrPattern))
  } >RAM_SHARED_DATA
  
  /* LEGACY SRAM Section 
  * 
  * IMPORTANT NOTE! 
  * If initialized variables will be placed in this section, 
  * the startup code needs to be modified to copy the init-values.  
  */
  ._legacy_sram :
  {
    . = ALIGN(4);
    _legacysram_start = .;       /* create a global symbol at legacy sram start */
    
    . = ALIGN(4);
    _legacysram_end = .;       /* create a global symbol at legacy sram end */
  } >LEGACY_SRAM
  
  /* DYNAMIC SRAM Section 
  * 
  * Used for memory allocation 
  */
  ._dynamic_sram :
  {
    . = ALIGN(4);
    _dynamicsram_start = .;       /* create a global symbol at dynamic sram start */
    
    . = ALIGN(4);
    _dynamicsram_end = .;       /* create a global symbol at dynamic sram end */
  } >DYNAMIC_SRAM
  
  /* RAM_SHARED_DATA Section 
  * 
  * Used for keeping info between reset
  */
  ._shared_data_area :
  {
    . = ALIGN(4);
    PRG_ReprogPatternAddr = .;       /* create a global symbol at dynamic sram start */
    
  } >RAM_SHARED_DATA
  
  /* Remove information from the standard libraries */
  /DISCARD/ :
  {
    libc.a ( * )
    libm.a ( * )
    libgcc.a ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
