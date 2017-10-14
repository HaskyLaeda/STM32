#include "interrupts.h"

extern Int8U Flag1;

void SysTick_Handler(void)
{
  static unsigned int volatile i;
//  static unsigned int volatile j;  
  i++;
//  j++;
  if (i == 1000)
  {
    if (Flag1)
      Flag1 = 0;
    else  
      Flag1 = 1;
    i = 0;
  }  
  return;
}



