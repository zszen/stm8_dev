#include "iostm8s103f3.h"
#include "stm8s.h"
#include "stm8s_adc1.h"
#include "ZDebug.h"
#include "ZConst.h"
#include <stdio.h>
#include "stm8s_gpio.h"
//#include "ZTime.h"

int main( void ){
  
  
//  Led_Flashing();
  
//  Led_Fading();
//  LedGroup_Turning2();
  
//  Ir501_Test();
//  Ir501_Fading();
  
//  Uart_Test();
  
//  ADC_Init();
  
//    AWU_Init();
//    asm("rim");
//    AWU_Enable();
  
//  LighingOn_init();
  
  LighingOn_fading();
  
  while(1);
  return 0;
}



