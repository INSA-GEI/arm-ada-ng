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

void LEGACY_GUI_ProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t val, uint8_t maxval)
{
	uint16_t length;

	/* dessin du cadre */
	GLCD_SetTextColor(Black);
	GLCD_DrawLine(x,y,x+w,y);
	GLCD_DrawLine(x,y,x,y+h);
	GLCD_DrawLine(x+w,y,x+w,y+h);
	GLCD_DrawLine(x,y+h,x+w,y+h);

	if (val>maxval) val = maxval;

	/* Dessin du remplissage */
	length = (uint16_t)(val * (w-4)) /maxval;

	GLCD_SetTextColor(Blue);
	GLCD_DrawFillRectangle(x+2, y+2, (x+2)+length , (y+2)+h-4);

	GLCD_SetTextColor(White);
	GLCD_DrawFillRectangle(x+2+length+1, y+2, (x+2+length+1)+(w-4)-length, (y+2)+ h-4);
}

void LEGACY_GUI_CenterBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int val, uint32_t absolutemaxval)
{
	int length1;
	int length2;
	int length_tot;
	uint16_t length;

	/* dessin du cadre */
	GLCD_SetTextColor(Black);
	GLCD_DrawLine(x,y,x+w,y);
	GLCD_DrawLine(x,y,x,y+h);
	GLCD_DrawLine(x+w,y,x+w,y+h);
	GLCD_DrawLine(x,y+h,x+w,y+h);

	if ((val>0) && ((uint32_t)val >= absolutemaxval)) 
	{
		val = absolutemaxval-1;
	}

	if ((val<0) && ((uint32_t)(-val) >= absolutemaxval)) 
	{
		val = -(absolutemaxval-1);
	}
	//	if ((val<0) && (-val >absolutemaxval)) val = -absolutemaxval;

	/* Dessin du remplissage */
	length1 = (int)((w-4)/2);
	length2 = (int)(((int)val * (int)(w-4)) /((int)absolutemaxval));
	length2 = (int)(length2/2);
	length_tot = length1 + length2;
	length = (uint16_t)length_tot;

	GLCD_SetTextColor(Blue);
	GLCD_DrawFillRectangle(x+2, y+2, (x+2)+ length, (y+2) + h-4);

	GLCD_SetTextColor(White);
	GLCD_DrawFillRectangle(x+2+length+1, y+2, (x+2+length+1)+(w-4)-length, (y+2)+h-4);
}
