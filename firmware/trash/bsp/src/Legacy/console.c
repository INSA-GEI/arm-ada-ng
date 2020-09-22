/******************************************************************************/
/* Console.c: Console tty maanagment                                          */
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

#include "system.h"

int CONSOLE_X=0;
int CONSOLE_Y=0;

void CONSOLE_GotoXY(int x, int y)
{
	if ((x>=0) && (x<40)) CONSOLE_X=x;
	if ((y>=0) && (y<15)) CONSOLE_Y=y;
}

int CONSOLE_PrintChar(int c)
{
	if ((c=='\n') || (c=='\r')) 
	{
		CONSOLE_X=0;
		CONSOLE_Y++;

		if (CONSOLE_Y>=15) CONSOLE_Y--;
	}
	else
	{
		GLCD_SetTextColor(White);
		GLCD_SetBackColor(Black);
		GLCD_DrawChar(CONSOLE_X,CONSOLE_Y, (uint8_t)c);
		CONSOLE_X++;

		if (CONSOLE_X>=40) 
		{
			CONSOLE_X=0;
			CONSOLE_Y++;

			if (CONSOLE_Y>=15) CONSOLE_Y--;
		}
	}

	return 1;
}
