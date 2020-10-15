/****************************************************************************
 *                                                                          *
 *                         GNAT COMPILER COMPONENTS                         *
 *                                                                          *
 *                                  A R M                                   *
 *                                                                          *
 *                            Linker Script File                            *
 *                                                                          *
 *      Copyright (C) 1999-2002 Universidad Politecnica de Madrid           *
 *             Copyright (C) 2003-2006 The European Space Agency            *
 *                   Copyright (C) 2003-2015 AdaCore                        *
 *                                                                          *
 * GNAT is free software;  you can  redistribute it  and/or modify it under *
 * terms of the  GNU General Public License as published  by the Free Soft- *
 * ware  Foundation;  either version 2,  or (at your option) any later ver- *
 * sion.  GNAT is distributed in the hope that it will be useful, but WITH- *
 * OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License *
 * for  more details.  You should have  received  a copy of the GNU General *
 * Public License  distributed with GNAT;  see file COPYING.  If not, write *
 * to  the  Free Software Foundation,  51  Franklin  Street,  Fifth  Floor, *
 * Boston, MA 02110-1301, USA.                                              *
 *                                                                          *
 * As a  special  exception,  if you  link  this file  with other  files to *
 * produce an executable,  this file does not by itself cause the resulting *
 * executable to be covered by the GNU General Public License. This except- *
 * ion does not  however invalidate  any other reasons  why the  executable *
 * file might be covered by the  GNU Public License.                        *
 *                                                                          *
 * GNARL was developed by the GNARL team at Florida State University.       *
 * Extensive contributions were provided by Ada Core Technologies, Inc.     *
 * The  executive  was developed  by the  Real-Time  Systems  Group  at the *
 * Technical University of Madrid.                                          *
 *                                                                          *
 ****************************************************************************/

/* This is a ARM specific version of this file */

/* This script replaces ld's default linker script, providing the
   appropriate memory map and output format. */

MEMORY
{
  itcm     (x) : ORIGIN = 0x00000000, LENGTH = 16K
  flash   (rx) : ORIGIN = 0x08000000, LENGTH = 256K
  dtcm   ( rx) : ORIGIN = 0x20000000, LENGTH = 64K
  sram12 (rwx) : ORIGIN = 0x20010000, LENGTH = 240K

  extram (rwx) : ORIGIN = 0xC0000000, LENGTH = 4M
  spiram (  r) : ORIGIN = 0x90000000, LENGTH = 8M
}

/* Do not place anything into the dtcm as it is used as Data cache by the CPU */
REGION_ALIAS("sram_tx", sram12)
REGION_ALIAS("sram_ro", sram12)
REGION_ALIAS("sram_bs", sram12)
REGION_ALIAS("sram_da", sram12)
REGION_ALIAS("ccm_da", dtcm)

REGION_ALIAS("extram_fb",extram)
REGION_ALIAS("extram_heap",extram)

_DEFAULT_STACK_SIZE = 8*1024;
_DEFAULT_SYS_STACK_SIZE = 1024;
_DEFAULT_FRAMEBUFFER_SIZE = 480*272*2;

ENTRY(_cpu_start);

SECTIONS
{
  .text :
  {
    KEEP (*(.isr_vector))
    KEEP (*(.interrupt_handlers))
    *(.text .text.* .gnu.linkonce.t*)
    *(.gnu.warning)
  } > flash

  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > flash
  /* .ARM.exidx is 4-bytes aligned, so __exidx_start needs to be
     aligned too. Note that assigning the location counter also makes
     ld attach the following symbols to the next section (instead of the
     previous section which is the default), so will properly
     consider the location counter of .ARM.exidx for __exidx_start and
      __exidx_end and not the previous section's one. */
  . = ALIGN(0x4);
  PROVIDE_HIDDEN (__exidx_start = .);
  .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > flash
  PROVIDE_HIDDEN (__exidx_end = .);

  .rodata :
  {
    *(.lit)
    *(.rodata .rodata.* .gnu.linkonce.r*)
    . = ALIGN(0x4);
    __rom_end = .;
  } > flash

  __ccmdata_load = __rom_end + (__data_words << 2);
  .ccmdata : AT (__ccmdata_load)
  {
    __ccmdata_start = .;
    *(.ccmdata .ccmdata.*)

    /* Ensure that the end of the data section is always word aligned.
       Initial values are stored in 4-bytes blocks so we must guarantee
       that these blocks do not fall out the section (otherwise they are
       truncated and the initial data for the last block are lost). */

    . = ALIGN(0x4);
    __ccmdata_end = .;
  } > ccm_da
  __ccmdata_words = (__ccmdata_end - __ccmdata_start) >> 2;

  .bss (NOLOAD): {
   . = ALIGN(0x8);
   __bss_start = .;

   __stack_start = .;
   . += DEFINED (__stack_size) ? __stack_size : _DEFAULT_STACK_SIZE;
   . = ALIGN(0x8);
   __stack_end = .;

   __interrupt_stack_start = .;
   . += DEFINED (__sys_stack_size) ? __sys_stack_size : _DEFAULT_SYS_STACK_SIZE;
   . = ALIGN(0x8);
   __interrupt_stack_end = .;

   *(.bss .bss.*)
   *(COMMON)

   . = ALIGN(0x8);    /* Align the stack to 64 bits */
   __bss_end = .;

   _end = .;
  } > sram_bs
  __bss_words = (__bss_end - __bss_start) >> 2;

  __data_load = __rom_end;
  .data : AT (__data_load)
  {
    __data_start = .;
    *(.data .data.* .gnu.linkonce.d*)

    /* Ensure that the end of the data section is always word aligned.
       Initial values are stored in 4-bytes blocks so we must guarantee
       that these blocks do not fall out the section (otherwise they are
       truncated and the initial data for the last block are lost). */

    . = ALIGN(0x4);
    __data_end = .;
  } > sram_da
  __data_words = (__data_end - __data_start) >> 2;

  .framebuffers :
  {
   _framebuffer_background_start = .;
   . += DEFINED (__framebuffer_size) ? __framebuffer_size : _DEFAULT_FRAMEBUFFER_SIZE;
   . = ALIGN(0x4);
   _framebuffer_background_end = .;

   _framebuffer_foreground_start = .;
   . += DEFINED (__framebuffer_size) ? __framebuffer_size : _DEFAULT_FRAMEBUFFER_SIZE;
   . = ALIGN(0x4);
   _framebuffer_foreground_end = .;
  } > extram_fb

  .heap :
  {
   __heap_start = .;
   __heap_end = ORIGIN(extram_heap) + LENGTH(extram_heap);
  } > extram_heap

  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
  .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
