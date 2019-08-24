#include "iostm8s103f3.h"
#include "stm8s.h"
#include "ZTime.h"

void Ir501_Test(void){
  PA_DDR=0xff;//设置 PC3 为输出模式 
  PA_CR1=0xff;//设置 PC3 为推挽输出 
  PA_CR2=0x00;//设置 PC3 为 10MHz 快速输出
  
  PD_DDR = 0x00;//PD1为输入
  PD_CR1|=0x08;//对应位设置为推挽输入
  PD_CR2=0x00;
  
  while(1){
    if(PD_IDR_IDR3 == 0){
      PA_ODR=0x00;
//      ZDelayLoop(100);
    }else{
      PA_ODR=0xff;
      ZDelayLoop(100);
    }
  }
} 

//int isSRDetected = 1;

void Ir501_Fading(void){
  TIM2_Reset();
  
  PD_DDR = 0x00;//PC1为输入
  PD_CR1|=0x08;//对应位设置为推挽输出
  PD_CR2|=0x08;
  
//  asm("rim");
//  asm("wfi");
  
  int i=0,j=0,isTurnedLight=0,isSRDetected=0;

  while(1){
    //
    isSRDetected = PD_IDR_IDR3;
    for(j=0;j<20;j++){
      if(PD_IDR_IDR3==1){
        isSRDetected = 1;
        break;
      }else{
        ZDelayLoop(50);
      }
    }
    if(isSRDetected){
      if(isTurnedLight==0){
        isTurnedLight = 1;
        for(;i<256;i+=2){
          TIM2_CCR3H=i;
          TIM2_CCR3L=i;
          ZDelayLoop(50);
        }
        i = 255;
        TIM2_CCR3H=i;
        TIM2_CCR3L=i;
        isSRDetected = 0;
      }
      ZDelayLoop(1000);
    }else{
      if(isTurnedLight==1){
        isTurnedLight = 0;
        for(;i>=0;i-=5){
          TIM2_CCR3H=i;
          TIM2_CCR3L=i;
          ZDelayLoop(50);
        }
        i = 0;
        TIM2_CCR3H=i;
        TIM2_CCR3L=i;
      }
    }
  }
}

//#pragma vector=6+2
//__interrupt void PD_GET(){
//  static int i=0;
//  if(PD_IDR_IDR3==1){
//      for(;i<256;i+=5){
//          TIM2_CCR3H=i;
//          TIM2_CCR3L=i;
//          ZDelayLoop(50);
//        }
//      i = 255;
//      TIM2_CCR3H=i;
//      TIM2_CCR3L=i;
//      ZDelayLoop(1000);
//      for(;i>=0;i-=10){
//          TIM2_CCR3H=i;
//          TIM2_CCR3L=i;
//          ZDelayLoop(50);
//      }
//      i = 0;
//      TIM2_CCR3H=i;
//      TIM2_CCR3L=i;
//      asm("wfi");
//  }
//}



