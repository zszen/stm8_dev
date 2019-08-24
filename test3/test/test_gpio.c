#include "iostm8s103f3.h"
#include "stm8s.h"
#include "ZTime.h"

void GPIO_Reset(void){
//  GPIO_DeInit(GPIOA);
//  GPIO_Init(GPIOA, GPIO_PIN_2, GPIO_MODE_OUT_PP_HIGH_FAST);
  
//  PA_DDR = 0x00; //清空
  PA_DDR=0xff;//设置 PC3 为输出模式 
  PA_CR1=0xff;//设置 PC3 为推挽输出 
  PA_CR2=0x00;//设置 PC3 为 10MHz 快速输出
  
//  PD_DDR=0xff;
//  PD_CR1=0xff;
//  PD_CR2=0X00;
//  PD_ODR=0xff;
//  PA_DDR&=0xfe;//输入模式
//  PA_CR2|=0x00;//设置 PC3 为 10MHz 快速输出
//  PA_ODR|= 0xff;
  
  
//  PA_DDR=0Xff; //PD0输出，其余保持原功能
//  PA_CR1=0Xff; //对应位设置为推挽输出
//  PA_CR2=0xff; //输出最大频率为2Mhz
//  PA_ODR=0x00;
//	PA_DDR = 0XFF;
//	PA_CR1 = 0XFF;
//	PA_CR2 = 0x0;
////  PA_ODR = 0x0;
}

//void onDelay(){
//  GPIO_WriteReverse(GPIOA, GPIO_PIN_3);//1s取一次反
//}

void Led_Flashing(void){
  GPIO_Reset();
  
  while(1){
    ZDelayLoop(1000);
    GPIO_WriteReverse(GPIOA, GPIO_PIN_3);
  }
  
//  while(1){
//    PA_ODR=0x00; //PD0为输出0，LED灭 PA_ODR&=0xfa;
////    GPIO_WriteReverse(GPIOA, GPIO_PIN_3);
//    ZDelay(1000);
//    PA_ODR=0xff; //PD0为输出1，LED亮 PA_ODR=0x04;
////    GPIO_WriteReverse(GPIOA, GPIO_PIN_3);
//    ZDelay(1000);
//  }
}



