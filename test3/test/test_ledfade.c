#include "iostm8s103f3.h"
#include "stm8s.h"
#include "ZTime.h"

void Led_Fading(void){
  TIM2_Reset();
  int i = 0;
  while(1){
    ZDelayLoop(500);
    for(i = 0;i<256;i+=10){
      TIM2_CCR3H=i;
      TIM2_CCR3L=i;
      ZDelayLoop(100);
    }
    ZDelayLoop(500);
    for(i=255;i>=0;i-=10){
      TIM2_CCR3H=i;
      TIM2_CCR3L=i;
      ZDelayLoop(200);
    }
    TIM2_CCR3H=0;
    TIM2_CCR3L=0;
  }
}

void LedGroup_Turning1(void){
  PD_DDR = 0xff;
  PD_CR1 = 0xff;
  PD_CR2 = 0x00;
  PD_ODR = 0x00;
  
  u8 x;
  int i;
  while(1){
    x = 0x02;
    for(i=0;i<5;i++){
      PD_ODR=x;
      ZDelayLoop(50);
      x = x<<1;
    }
    x = 0x40;
    for(i=0;i<5;i++){
      PD_ODR=x;
      ZDelayLoop(50);
      x = x>>1;
    }
  }
}

void LedGroup_Turning2(void){
  PA_DDR = 0xff;
  PA_CR1 = 0xff;
  PA_CR2 = 0x00;
  PA_ODR = 0x00;
  
  u8 x;
  int i;
  while(1){
    x = 0x02;
    for(i=0;i<5;i++){
      PA_ODR=x;
      ZDelayLoop(50);
      x = x<<1;
    }
    x = 0x40;
    for(i=0;i<5;i++){
      PA_ODR=x;
      ZDelayLoop(50);
      x = x>>1;
    }
  }
}