/******************************************************************************/
/* panic.h: Header file for panic managment                                   */
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

#include "stm32f30x.h"

#define NMI_IT					0
#define HARD_FAULT_IT		1
#define USAGE_FAULT_IT	4
#define BUS_FAULT_IT		3
#define MEMORY_FAULT_IT	2

void PANIC_EraseUserProgramEntry(void);
void PANIC_ReadStack(uint32_t it_source, uint32_t *sp);
void PANIC_Display(void);
void PANIC_SoftwarePanic(char *Title, char *Message);
