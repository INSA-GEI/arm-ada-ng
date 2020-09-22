/*
 * font.c
 *
 *  Created on: 5 avr. 2019
 *      Author: dimercur
 */

#include "fonts.h"
extern const uint8_t Font8_Table[];
extern const uint8_t Font12_Table[];
extern const uint8_t Font16_Table[];
extern const uint8_t Font20_Table[];
extern const uint8_t Font24_Table[];

sFONT FontLegacy= {
  Font12_Table,
  8, /* Width */
  12, /* Height */
};

sFONT Font8 = {
  Font8_Table,
  5, /* Width */
  8, /* Height */
};

sFONT Font12 = {
  Font12_Table,
  7, /* Width */
  12, /* Height */
};

sFONT Font16 = {
  Font16_Table,
  11, /* Width */
  16, /* Height */
};

sFONT Font20 = {
  Font20_Table,
  14, /* Width */
  20, /* Height */
};

sFONT Font24 = {
  Font24_Table,
  17, /* Width */
  24, /* Height */
};



