#include "iostm8s103f3.h"
#include "stm8s.h"

void CLK_Reset(void){
////  CLK_CKDIVR = 0x00;//CPU时钟0分频，系统时钟0分频
//  CLK_ICKR |= 0X01;           //使能内部高速时钟 HSI
////  CLK_CKDIVR = 0x08;// 16M内部RC经2分频后系统时钟为8M
//  CLK_CKDIVR=0X18;
////  while(!(CLK_ICKR&0x02));    //HSI准备就绪 
////  CLK_SWR=0xe1;               //HSI为主时钟源 
  CLK_SWR = 0xd2;
  CLK_CKDIVR= 0x00;
}

void TIM2_Reset(void) {
  CLK_Reset();
  TIM2_PSCR = 0x01; //定时器2预分频系数为1
  TIM2_CR1 = 0x01; //内部计数器使能；
  TIM2_ARRH = 0X9C;//0140，320分频，16M/320=50K，实测49.75K
  TIM2_ARRL = 0X40;//自动装载寄存器低位；实测013e正好为50.0K
  
  TIM2_CCER2=0x01; //开启OC3信号输出脚
  TIM2_CCMR3=0X60;   //设置定时器2三通道 PWM模式2 输出模式
  TIM2_CCR3H=0x00;  
  TIM2_CCR3L=0X00; 
}