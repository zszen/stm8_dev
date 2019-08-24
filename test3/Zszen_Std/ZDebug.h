
#ifndef Zszen_Std_ZDebug
#define Zszen_Std_ZDebug

#include "stm8s.h"
#include "stm8s_uart1.h"
 
typedef enum{
  ZLOG_TYPE_UART,
}ZLOG_TYPE;
 
void ZLog(unsigned char *dat, ZLOG_TYPE type);
void ZLogUART(unsigned char *dat);

//void UART_Init(void);
//void UART_SendDat(u8 dat);
//void UART_SendStr(unsigned char *dat);

#endif