/******************************************************************************/
/* ProgressBar.c: Progress Bar widget                                         */
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
#include "gui.h"
#include "../wrapper.h"
#include "string.h"

const char* blackbkg="                                        ";

void LEGACY_GUI_CreateWindow(const char *title, COLOR background, COLOR titlebarText, COLOR titlebarBgnd)
{
	GLCD_Clear(background);
	GLCD_SetTextColor(titlebarText);
	GLCD_SetBackColor(titlebarBgnd);
	GLCD_DrawString(0,0,blackbkg);
	GLCD_DrawString((40-strlen(title))/2, 0, title);
}

