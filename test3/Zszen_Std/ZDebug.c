
#include "ZDebug.h"

//pd6 rxd
//pd5 txd

static bool ZDebug_Init = FALSE;

void UART_Init(void);
void UART_SendDat(u8 dat);
void UART_SendStr(unsigned char *dat);

void ZLogUART(unsigned char *dat){
//  ZLog(dat, ZLOG_TYPE_UART);
  if(!ZDebug_Init){
    UART_Init();
    ZDebug_Init = TRUE;
  }
  UART_SendStr(dat);
  asm("rim");
}

void ZLog(unsigned char *dat, ZLOG_TYPE type){
  switch(type){
    case ZLOG_TYPE_UART:
    default:
      if(!ZDebug_Init)UART_Init();
      UART_SendStr(dat);
      asm("rim");
    break;
  }
}


void UART_Init(void){
  UART1_DeInit(); 
  UART1_Init((u32)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE); 
  UART1_ITConfig(UART1_IT_RXNE_OR,ENABLE); 
  UART1_Cmd(ENABLE); 
}

void UART_SendDat(u8 dat) { 
  while(( UART1_GetFlagStatus(UART1_FLAG_TXE)==RESET));
  UART1_SendData8(dat);
} 

void UART_SendStr(unsigned char *dat) {
  while(*dat!='\0') { 
    UART_SendDat(*dat);
    dat++;
  }
}