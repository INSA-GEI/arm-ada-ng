#include "stm32f7xx.h"
#include "wrapper.h"

int i=0;

int main (void)
{
  GLCD_DrawString(5,5,"Hello");

  while (1)
    {
      i=i+1;

      if (i>100)
        i=0;
    }

  return 0;
}
