/******************************************************************************/
/* panic.c: panic managment                                                   */
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

#include "stm32746g_discovery.h"
#include "wrapper.h"
#include "panic.h"

static volatile uint32_t R0,R1,R2,R3,R12,PC,LR,XPSR,SP;
static uint32_t IT_Source;
#define FLASH_USER_START_ADDR   ((uint32_t)0x0800C000)   /* Start @ of user Flash area */

extern const uint32_t* __app_stack_end__;
extern const uint32_t* __system_stack_end__;
extern void SetStack(uint32_t systemstack, uint32_t applistack);

void PANIC_EraseUserProgramEntry(void) {

}

void PANIC_ReadStack(uint32_t it_source, uint32_t *sp) {
	IT_Source = it_source;

	if ( (sp >= (uint32_t*)0x20000000) && (sp <= (uint32_t*)(0x20001400)))
	{
		R0 = sp[0];
		R1 = sp[1];
		R2 = sp[2];
		R3 = sp[3];
		R12 = sp[4];
		LR = sp[5];
		PC = sp[6];
		XPSR = sp[7];
	}
	else
	{
		IT_Source = 5;
		R0=R1=R2=R3=R12=LR=PC=XPSR=0x0;
		SP = (uint32_t)sp;
	}

	SetStack((uint32_t)&__system_stack_end__,(uint32_t)&__app_stack_end__);
	PANIC_Display();
}

void PANIC_Display(void) {
	char *title;
	char str[42];

	title ="";
	switch (IT_Source)
	{
	case 0:
		title ="NMI Error";
		break;
	case 1:
		title ="Hard Fault";
		break;
	case 2:
		title ="Memory Fault";
		break;
	case 3:
		title ="Bus Fault";
		break;
	case 4:
		title ="Usage Fault";
		break;
	case 5:
		title ="Stack Error";
		break;
	default:
		title ="Unknown Error";
	}

	GUI_CreateWindow(title, Red, White, Black);

	/* Affiche la backtrace */
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(Red);

	GLCD_DrawString(0, 3, "Press A to try again");

	GLCD_DrawString(0, 14, "System halted !");
	GLCD_DrawString(0, 10, "Backtrace :");
	sprintf (str, "R0[%08X] R1[%08X] R2[%08X]", (unsigned int)R0, (unsigned int)R1, (unsigned int)R2);
	GLCD_DrawString(0, 11, str);
	sprintf (str, "R3[%08X] R12[%08X] LR[%08X]", (unsigned int)R3, (unsigned int)R12, (unsigned int)LR);
	GLCD_DrawString(0, 12, str);
	sprintf (str, "PC[%08X] XPSR[%08X]", (unsigned int)PC, (unsigned int)XPSR);
	GLCD_DrawString(0, 13, str);

	while (KEYS_GetState(KEY_A) != KEY_PRESSED);

	/* Redemarrage de la carte */
	NVIC_SystemReset();
}

void PANIC_SoftwarePanic(char *Title, char *Message) {
	GUI_CreateWindow(Title, Yellow, White, Black);

	/* Affiche la backtrace */
	GLCD_SetTextColor(White);
	GLCD_SetBackColor(Red);

	GLCD_DrawString(0, 5, Message);
	GLCD_DrawString(0, 14, "Press A to try again");

	while (KEYS_GetState(KEY_B) != KEY_PRESSED);

		/* Redemarrage de la carte */
	NVIC_SystemReset();
}
