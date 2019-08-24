#include "iostm8s103f3.h"
#include "stm8s.h"
#include "ZDebug.h"
#include "ZConst.h"
#include "ZTime.h"

//static int IsDetected;
//static int IsOn;

void LighingOn_init(){
  
  PA_DDR=0xff;//设置 PC3 为输出模式 
  PA_CR1=0xff;//设置 PC3 为推挽输出 
  PA_CR2=0x00;//设置 PC3 为 10MHz 快速输出
  
  PD_DDR = 0x00;//PD1为输入
  PD_CR1|=0x08;//对应位设置为推挽输入
  PD_CR2=0x00;
  
//  while(1){
//    if(PD_IDR_IDR3 == 1){
//      if(IsOn==1){
//        IsOn = 0;
//        GPIO_WriteLow(GPIOA, GPIO_PIN_3);
//      }else{
//        IsOn = 1;
//        GPIO_WriteHigh(GPIOA, GPIO_PIN_3);
//      }
//      
//    }
//    GPIO_WriteReverse(GPIOA, GPIO_PIN_3); 
//  }
}

void LighingOn_fading(void){
  TIM2_Reset();
  
  LighingOn_init();
//  PD_DDR = 0x00;//PC1为输入
//  PD_CR1|=0x08;//对应位设置为推挽输出
//  PD_CR2|=0x08;
  
//  asm("rim");
//  asm("wfi");
  
  int i=0,j=0,isTurnedLight=0,isSRDetected=0;
  int IsOn = 0, detectValue = 0,isDetected=0;
  
  while(1){
    //
//     if(PD_IDR_IDR3==1){
//        i = 255;
//        TIM2_CCR3H=i;
//        TIM2_CCR3L=i;
//        ZDelayLoop(500);
//     }else{
//        i = 0;
//        TIM2_CCR3H=i;
//        TIM2_CCR3L=i;
//        ZDelayLoop(500);
//     }
//     continue;
    
//    isSRDetected = 0;
//    if(PD_IDR_IDR3==1){
//      isSRDetected = 1;
//      IsDetected = 1;
//      break;
////    }else{
////      IsDetected = 0;
//    }
//    isSRDetected = 0;
//    detectValue = 0;
//    for(j=0;j<200;j++){
//      if(PD_IDR_IDR3==1){
//        detectValue++;
//        isDetected = 1;
//      }else{
//        detectValue--;
//        isDetected = 0;
//      }
//    }
//    if(detectValue>0 && isDetected==1){
//      isSRDetected = 1;
//    }
    isSRDetected = 0;
    if(isDetected==0 && PD_IDR_IDR3==1){
      isSRDetected = 1;
      isDetected = 1;
    }else if(isDetected==1 && PD_IDR_IDR3==0){
      isDetected = 0;
    }
    
    if(isSRDetected){
      if(isTurnedLight==0){
        isTurnedLight = 1;
        for(;i<256;i+=5){
          TIM2_CCR3H=i;
          TIM2_CCR3L=i;
          ZDelayLoop(80);
        }
        i = 255;
        TIM2_CCR3H=i;
        TIM2_CCR3L=i;
        isSRDetected = 0;
      }else{
        isTurnedLight = 0;
        for(;i>=0;i-=10){
          TIM2_CCR3H=i;
          TIM2_CCR3L=i;
          ZDelayLoop(80);
        }
        i = 0;
        TIM2_CCR3H=i;
        TIM2_CCR3L=i;
      }
    }
  }
}