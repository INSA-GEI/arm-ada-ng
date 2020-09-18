//******************** (C) COPYRIGHT 2011 STMicroelectronics ********************
//* File Name          : startup_stm32f4xx.s
//* Author             : MCD Application Team
//* Version            : V1.0.0
//* Date               : 30-September-2011
//* Description        : STM32F4xx devices vector table for MDK-ARM toolchain.
//*                      This module performs:
//*                      - Set the initial SP
//*                      - Set the initial PC == Reset_Handler
//*                      - Set the vector table entries with the exceptions ISR address
//*                      - Configure the system clock and the external SRAM mounted on
//*                        STM324xG-EVAL board to be used as data memory (optional,
//*                        to be enabled by user)
//*                      - Branches to __main in the C library (which eventually
//*                        calls main()).
//*                      After Reset the CortexM4 processor is in Thread mode,
//*                      priority is Privileged, and the Stack is set to Main.
//* <<< Use Configuration Wizard in Context Menu >>>
//*******************************************************************************
// THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
// WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
// AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
// INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
// CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
// INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
//*******************************************************************************


// Vector Table Mapped to Address 0 at Reset
        .section	.text.abi_table
        .global  ABI_Ptr_Table

/*		IMPORT  API_GetOSVersion
		IMPORT	MALLOC_Init
		IMPORT	MALLOC_GetMemory
		IMPORT	MALLOC_FreeMemory
		IMPORT	fputc
		IMPORT  fgetc
		IMPORT	Delay
		IMPORT	GLCD_Clear
        IMPORT  GLCD_SetTextColor		//
        IMPORT  GLCD_SetBackColor		//
        IMPORT  GLCD_PutPixel			//
        IMPORT  GLCD_DrawChar				//
		IMPORT  GLCD_DrawADAString		//
		IMPORT  GLCD_DrawLine	 	//
        IMPORT  GLCD_DrawRectangle		//
        IMPORT  GLCD_DrawFillRectangle		//
        IMPORT  GLCD_DrawCircle			//
		IMPORT	GLCD_DrawFillCircle
		IMPORT	GLCD_DrawImage
		IMPORT  KEYS_GetState			//
		IMPORT	POT_GetValue
		IMPORT  RNG_GetValue

		IMPORT	GUI_ProgressBar
		IMPORT	GUI_CenterBar
		IMPORT	AUDIO_Start
        IMPORT	AUDIO_Stop
        IMPORT	AUDIO_FillBuffer
        IMPORT	AUDIO_SetEventCallback
		IMPORT	LED_Set
		IMPORT	L3GD20_GetGyroscopicValues
		IMPORT	LSM303DLHC_GetMagneticValues
		IMPORT	LSM303DLHC_GetAccelerometerValues
		IMPORT 	SRAM_ReadByte
		IMPORT	SRAM_WriteByte
		IMPORT	SRAM_ReadBuffer
		IMPORT	SRAM_WriteBuffer
		IMPORT 	TIMER_Start
		IMPORT  TIMER_Stop
		IMPORT  TIMER_SetEventCallback

		IMPORT  GLCD_DrawImagefromSRAM
		IMPORT  GLCD_LayerScrollMode
		IMPORT  GLCD_SetScrollWindow
		IMPORT  GLCD_ScrollVertical
		IMPORT  GLCD_ScrollHorizontal
		IMPORT  GLCD_LayerDisplayMode
		IMPORT  GLCD_LayerTransparency
		IMPORT  GLCD_SetLayer
		IMPORT  GLCD_BTESetSource
		IMPORT  GLCD_BTESetDestination
		IMPORT  GLCD_BTESetSize
		IMPORT  GLCD_BTESetBackgroundColor
		IMPORT  GLCD_BTESetForegroundColor
		IMPORT  GLCD_BTESetPatternNumber
		IMPORT  GLCD_SetTransparentColor
		IMPORT  GLCD_BTEStart
		IMPORT  GLCD_BTEStartAndFillFromSRAM
*/
			
		.align  4

ABI_Ptr_Table:

// Basic OS services
		.word   API_GetOSVersion
		.word   _write
        .word   _read
        //.word   MALLOC_Init
		//.word   MALLOC_GetMemory
		//.word   MALLOC_FreeMemory
		.word   API_InvalidFunction
		.word   API_InvalidFunction
		.word   API_InvalidFunction
		.word	Delay

// Graphics services
		.word	GLCD_Clear
        .word 	GLCD_SetTextColor
        .word   GLCD_SetBackColor
        .word   GLCD_PutPixel
        .word   GLCD_DrawChar
		.word   GLCD_DrawADAString
		.word   GLCD_DrawLine
        .word   GLCD_DrawRectangle
        .word   GLCD_DrawFillRectangle
        .word   GLCD_DrawCircle
		.word	GLCD_DrawFillCircle
		.word	GLCD_DrawImage

// Graphics widgets
		.word	GUI_ProgressBar
		.word	GUI_CenterBar

// Keys and potar services
        .word 	KEYS_GetState
		.word	POT_GetValue

// Led services
		.word	LED_Set

// Random generator services
        .word   RNG_GetValue

// Sound services
        .word	AUDIO_Start
        .word	AUDIO_Stop
        .word	AUDIO_FillBuffer
        .word	AUDIO_SetEventCallback

// Sensors services
		.word	L3GD20_GetGyroscopicValues
		.word	LSM303DLHC_GetMagneticValues
		.word	LSM303DLHC_GetAccelerometerValues

// External RAM
		.word 	SRAM_ReadByte
		.word	SRAM_WriteByte
		.word	SRAM_ReadBuffer
		.word	SRAM_WriteBuffer

// Timer event managment
		.word 	TIMER_Start
		.word  	TIMER_Stop
		.word  	TIMER_SetEventCallback
			
// second set of function for GLCD
		.word  	GLCD_DrawImagefromSRAM
		.word  	GLCD_LayerScrollMode
		.word  	GLCD_SetScrollWindow
		.word 	GLCD_ScrollVertical
		.word  	GLCD_ScrollHorizontal
		.word  	GLCD_LayerDisplayMode
		.word  	GLCD_LayerTransparency
		.word  	GLCD_SetLayer
		.word  	GLCD_BTESetSource
		.word  	GLCD_BTESetDestination
		.word  	GLCD_BTESetSize
		.word  	GLCD_BTESetBackgroundColor
		.word  	GLCD_BTESetForegroundColor
		.word  	GLCD_BTESetPatternNumber
		.word  	GLCD_SetTransparentColor
		.word  	GLCD_BTEStart
		.word   GLCD_BTEStartAndFillFromSRAM

// Functions related to Synthetizer
		.word 	SYNTH_Start
		.word 	SYNTH_Stop

		.word 	SYNTH_SetMainVolume
		.word 	SYNTH_SetVolume
		.word 	SYNTH_SetInstrument
		.word 	SYNTH_NoteOn
		.word 	SYNTH_NoteOff

		.word 	MELODY_Start
		.word 	MELODY_Stop
		.word 	MELODY_GetPosition

ABI_Ptr_Table_End:

/******************************************************************************
*
* The minimal vector table for a Cortex-M.  Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
*
******************************************************************************/
 	.section	.legacy_isr_vector,"a",%progbits
	.type	g_pfnVectors, %object
	.size	g_pfnVectors, .-g_pfnVectors

g_pfnVectors:
	.word	Reset_Handler
	.word	ABI_Table

//******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE*****
