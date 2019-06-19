/******************************************************************************/
/* PackedBMP.h: Header for bitmap unpacking library                           */
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
#ifndef __PACKEDBMP_H__
#define __PACKEDBMP_H__

#include "stm32f30x.h"
#include "glcd.h"

struct PackedBMP_data_ST
{
	COLOR color;
	uint8_t count;
};

typedef struct PackedBMP_data_ST PackedBMP_data;

struct PackedBMP_Header_ST
{
	uint16_t width;
	uint16_t height;
	uint16_t size;
	PackedBMP_data *data;
};

typedef struct PackedBMP_Header_ST PackedBMP_Header;

#endif /* __PACKEDBMP_H__ */
