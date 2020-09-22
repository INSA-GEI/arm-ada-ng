/******************************************************************************/
/* UnpackBMP.c: Library for unpacking bmp stored as packedBMP format          */
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
#include "packedbmp.h"
#include "unpackbmp.h"

int UnpackBMP(PackedBMP_Header *packedbmp, COLOR *data)
{
	int size;

	PackedBMP_data *ptr_BMP;
	COLOR *ptr;
	int count;

	size = packedbmp->size;
	ptr_BMP = packedbmp->data;
	ptr =data;

	while (size != 0)
	{
		for (count=0; count<ptr_BMP->count; count ++)
		{
			*ptr = ptr_BMP->color;
			ptr++;
		}	
		ptr_BMP++;
		size--;
	}

	return 0;
}



