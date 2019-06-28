/******************************************************************************/
/* config.h: configuration file for system                                    */
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

#ifndef __CONFIG_H__
#define __CONFIG_H__

/*
 * Definition pour l'appel à l'application
 */
#define APPLICATION_FIRST_ADDR			0x8008000
#define BAD_APPLICATION_RETURN_CODE		0xDEAD

#define STACK_APP_ADDR (0x20000500-0x4)

/*
 * Definition pour la reprog
 */
#define BAUDRATE 500000
#define REPROG_PATTERN_ADDR	0x10001FFC
/*
 * Definition pour le vecteur d'interruption
 */
#define VECTOR_TABLE_ADDR 0x10000600

/*
 * Definition pour m_alloc
 */
#define MALLOC_INITIAL_BASE (0x20000000+(4*1024))
#define MALLOC_END_BASE 	0x2000A000

#endif /* __CONFIG_H__ */
