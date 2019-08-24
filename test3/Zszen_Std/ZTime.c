#include "ZTime.h"
#include "iostm8s103f3.h"
//#include "stm8s_tim2.h"
#include "stm8s_tim4.h"
#include "stm8s_itc.h"

///HSI delay
static uint msDelay;
void ZDelayMS (uint _msDelay){
  msDelay = _msDelay;
//  enableInterrupts();
  asm("rim");
//  asm("sim");
  
//  CLK_DeInit();
//  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);//HSI16MHZ,1分频
   
//  ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF,ITC_PRIORITYLEVEL_0);
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_16,125);//hsi用1分频的话, 这里125需要改为1000, 默认8分频, 1000/8 = 125
  TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);
  TIM4_SetCounter(0x0000); 
  TIM4_Cmd(ENABLE);
  
//  _asm("halt"); 
// asm("wfi");
}

#pragma vector=TIM4_OVR_UIF_vector//TIM2_OVR_UIF_vector//13+2
__interrupt void TIM4_IRQ(){
  static unsigned int j;
  j++;
  if(j==msDelay){
    j=0;
    TIM4_Cmd(DISABLE);
//    (*pDelay)();
//    disableInterrupts();
//    asm("sim");
    return;
  }
  TIM4_ClearITPendingBit(TIM4_IT_UPDATE); //清中断标志位
}



///loop delay
void ZDelayusLoop(void){    
  asm("nop"); //一个asm("nop")函数经过示波器测试代表100ns   
//  asm("nop");   
//  asm("nop");   
//  asm("nop");    
}   

void ZDelayLoop(uint time_ms){
  uint i;   
  while(time_ms--){ 
    for(i=220;i>0;i--){
      asm("nop");
      asm("nop");
      asm("nop");
    }
  }
//    for(i=900;i>0;i--)
//      ZDelayusLoop();
}
