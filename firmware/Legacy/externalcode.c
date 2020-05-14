/*
 * externalcode.c
 *
 *  Created on: 4 mai 2020
 *      Author: dimercur
 */

#include "externalcode.h"
#include "system.h"
#include "stdio.h"

volatile unsigned int i;
volatile unsigned int counter;
char str[15];

int EssaiCodeSRAM(void)
{
	GLCD_SetTextColor(Black);
	GLCD_DrawString(7,8,"Valeur du compteur: ");
	counter =0;
	i=0;

	while (1) {
		i=i+1;

		if (i>=10000000)
		{
			i=0;
			counter++;
			//GLCD_DrawString(7,9,"                   ");
			sprintf(str,"%i", counter);
			GLCD_DrawString(7,9,str);
		}
	}
}


