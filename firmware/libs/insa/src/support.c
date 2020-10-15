#include "stdio.h"
#include "stm32f7xx_hal.h"

void API_GetOSVersion(uint32_t *major_ver, uint32_t *minor_ver)
{
  *major_ver=4;
  *minor_ver=0;
}

void C_Delay(uint32_t val)
{
  HAL_Delay(val);  
}
