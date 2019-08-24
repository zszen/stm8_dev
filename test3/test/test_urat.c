#include "iostm8s103f3.h"
#include "stm8s.h"
#include "ZDebug.h"
#include "ZConst.h"

void Uart_Test(void){
  ZLogUART("init \r\n");
//  UART_Init();
//  UART_SendStr("STM8S UART 实验!\r\n");
  asm("rim");
  
  ZLogUART("STM8S UART 实验!\r\n");
}