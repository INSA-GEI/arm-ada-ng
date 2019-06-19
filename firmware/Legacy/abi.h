/******************************************************************************/
/* ABI.h: Header file for ABI Tables                                          */
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

#ifndef __ABI_H__
#define __ABI_H__

struct ABI_Table_ST
{
	char magic_str[4];
	unsigned int version;
	void *ptr;
};

typedef struct ABI_Table_ST ABI_Table_Type;

#endif /* __ABI_H__ */
