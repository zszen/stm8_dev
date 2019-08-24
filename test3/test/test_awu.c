#include "iostm8s103f3.h"
#include "stm8s.h"

//AWU_Init();
//asm("rim");
//AWU_Enable();

void AWU_Init(void){
  AWU_CSR1 |= MASK_AWU_CSR1_AWUF;             /* AWU自动唤醒中断标志位被使能 */
  AWU_CSR1 &=~MASK_AWU_CSR1_AWUEN;            /* 自动唤醒功能被禁止 */
  AWU_CSR1 &=~MASK_AWU_CSR1_MSR;              /* 测量被禁止 */  
  AWU_APR = 0x3E;                             /* 时钟为LSI的64分频 */
  AWU_TBR = 0x0B;                             /* 时基选择,512ms唤醒一次 */
  CLK_PCKENR2 |= (0x04);                      /* AWU与主时钟连接 */   
  CLK_ICKR |= MASK_CLK_ICKR_LSIEN;            /* 打开内部低速时钟源 */  
  while(CLK_ICKR_LSIRDY == 0);                /* 等待时钟源信号稳定 */  
}

void AWU_Enable(void){
  AWU_CSR1 |= MASK_AWU_CSR1_AWUEN;            /* 自动唤醒功能被使能 */ 
}

void AWU_Disenable(void){
  AWU_CSR1 &=~MASK_AWU_CSR1_AWUEN;            /* 自动唤醒功能被禁止 */  
}

#pragma vector = AWU_vector 
__interrupt void AWU_ISR(void){
  AWU_CSR1 = AWU_CSR1;                        /* 清除更新中断标志位 */           
}