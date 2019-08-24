//******************************************************************************
//*
//* This Information Proprietary  To Kong Studio Corporation
//*
//******************************************************************************
//*
//*           Copyright (c) 2015 Kong Studio Corporation
//*                  ALL RIGHTS RESERVED
//*
//******************************************************************************
    
//******************************************************************************
//* FILE NAME: Main.c
//*
//* DESCRIPTION: STM8S Lesson1 example
//*
//* ORIGINATOR: Konglittle
//*
//* DATE: 2015-03-15
//*
//******************************************************************************
#include <string.h>
#include "stm8s_adc1.h"
#include "EepromMap.h"
#include "SerialPort.h"
#include "stm8s_gpio.h"
#include "ADC_Brightness.h"



 
void DelayApi(uint16_t uwDelayCnt);
static void InitCpuClock(void);
static void InitTimer2(void);
static void InitUart1(void);
static void InitAdc1HW(void);


uint8_t ubStartTimerFlag = 0;
uint16_t uwTimerCount = 0;
uint8_t ubFrameDone = 0;
uint8_t ubUart1RxBuf[10] = {0};

/*******************************************************************************
* Function Name  : main.
* Description    : main function of this project
* Input          : None
* Output         : None.
* Return         : None.
*******************************************************************************/
int main( void )
{
    uint16_t uwDelayCnt = 0;
    //Reset GPIOB to default configure
    GPIO_DeInit(GPIOB);
    
    //Initialize GPIOB_Pin5 to output
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    
    InitCpuClock();
    InitTimer2();
    InitUart1();
    EepromInitial();
    InitAdc1HW();
    enableInterrupts();
    
    //Send welcome Information
    SendData_String("**************************************************\r\n");
    SendData_String("***************Welcome to My Studio***************\r\n");
    SendData_String("**************************************************\r\n");
    SendData_String("****************Lesson 6 - Eeprom*****************\r\n");
    SendData_String("**************************************************\r\n");
    SendData_String("Current Blinking Period is:   ");
    SendData_Number(uwEEP_BlinkPeriod);
    SendData_String("ms\r\n");
    
    uwDelayCnt = uwEEP_BlinkPeriod;
    
    
    while(1)
    {
        GPIO_WriteReverse(GPIOB, GPIO_PIN_5);
        if(ubFrameDone == 1)
        {
            ubFrameDone = 0;
            uwDelayCnt = ((uint16_t)ubUart1RxBuf[2] << 8) | (uint16_t)ubUart1RxBuf[3];
            EepromWriteSection(EE_BLINK_PERIOD, (uint8_t *)&uwDelayCnt);
            SendData_String("New Blinking Period is:   ");
            SendData_Number(uwDelayCnt);
            SendData_String("ms\r\n");
            memset(&ubUart1RxBuf, 0, sizeof(ubUart1RxBuf) / sizeof(uint8_t));
        }
        
        DelayApi(500);
        ADC_BrightnessTask();
    }
}

/*******************************************************************************
* Function Name  : DelayApi.
* Description    : Delay some time.
* Input          : Delay counter.
* Output         : None.
* Return         : None.
*******************************************************************************/
void DelayApi(uint16_t uwDelayCnt)
{    
    //Set the flag to make ISR start to count
    ubStartTimerFlag = 1;
    
    //Wait until expire 
    while(uwTimerCount <= uwDelayCnt);
    
    //Clear flag and timer cnt
    ubStartTimerFlag = 0;
    uwTimerCount = 0;
}

/*******************************************************************************
* Function Name  : InitCpuClock.
* Description    : Initial CPU clock, .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void InitCpuClock(void)
{
    CLK_DeInit();
    
    //Use HSI @2MHZ, div = 8
    CLK_HSECmd(DISABLE);
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV8);
    CLK_HSICmd(ENABLE);
}


/*******************************************************************************
* Function Name  : InitTimer2.
* Description    : Initial timer2 config, .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void InitTimer2(void)
{
    //1ms = 128/2000000 *15
    TIM2_TimeBaseInit(TIM2_PRESCALER_128, 15);
    /* Clear TIM4 update flag */
    TIM2_ClearFlag(TIM2_FLAG_UPDATE);
    
    /* Enable update interrupt */
    TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
    TIM2_Cmd(ENABLE);    
}


/*******************************************************************************
* Function Name  : InitUart1.
* Description    : Initial Uart1 config: 19200bps, 8bit, 1 StopBit, None Parity
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void InitUart1(void)
{
    UART1_DeInit();
    
    //19200bps, 8bit, 1 stopbit, both rx and tx
    UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, 
                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
                
    UART1_ClearFlag(UART1_FLAG_RXNE);
    
    //Enable Rx interrupt
    UART1_ITConfig(UART1_IT_RXNE_OR, ENABLE);
    
    UART1_Cmd(ENABLE);   
}

/*******************************************************************************
* Function Name  : InitAdc1.
* Description    : Initial ADC1 config, .
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void InitAdc1HW(void)
{
    //Set ADC1 to default setting
    ADC1_DeInit();
    ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,           //Single mode
              ADC1_CHANNEL_3,                       //Use channel 3- PD3
              ADC1_PRESSEL_FCPU_D2,                //Pre-12
              ADC1_EXTTRIG_TIM, DISABLE,            //Don't use external trigger
              ADC1_ALIGN_RIGHT,                     //Align to right
              ADC1_SCHMITTTRIG_CHANNEL3, ENABLE);  //not use schmitter
              
    //ADC1_ClearFlag(ADC1_FLAG_AWS3);
    ADC1_Cmd(ENABLE);
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
