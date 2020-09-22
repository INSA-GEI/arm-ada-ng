/******************************************************************************/
/* potentiometers.h: Header for potentiometers managment                      */
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

void LEGACY_GUI_ProgressBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t val, uint8_t maxval);
void LEGACY_GUI_CenterBar(uint16_t x, uint16_t y, uint16_t w, uint16_t h, int val, uint32_t absolutemaxval);
