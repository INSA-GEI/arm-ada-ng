/******************************************************************************/
/* ABI_Table.c: Jump table to be used by application for accessing functions  */
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
#include "abi.h"
#include "version.h"
#include "panic.h"

void API_GetOSVersion(int* major, int* minor);
extern const void* ABI_Ptr_Table[];

const ABI_Table_Type ABI_Table = 
{
	"_ABI",
	ABI_VERSION,
	(void *)ABI_Ptr_Table
};

void API_GetOSVersion(int* major, int* minor)
{
	*major = BL_MAJOR_VERSION;
	*minor = BL_MINOR_VERSION;
}

void API_InvalidFunction(void)
{
	PANIC_SoftwarePanic("Invalid API Call", "Invalid function requested.");
}
