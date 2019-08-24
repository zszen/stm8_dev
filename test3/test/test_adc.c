#include "iostm8s103f3.h"
#include "stm8s.h"

void ADC_Init(void) {
  
  PA_DDR_DDR2 = 0x1;
  PA_CR1_C12 = 0x1;
  PD_DDR_DDR3 = 0x0;
  PD_CR1_C13 = 0x0;
//  PA_DDR_DDR2 = 0x0;
    PB_DDR_DDR4 = 0x0;
  
  
//  ZLogUART("start test \r\n");
//  ADC1_DeInit();//ADC 相关寄存器恢复默认值
//  //初始化 ADC:单次转换/通道 1/时钟分频/关闭事件/数据右对齐/使能施密特触发器
//  ADC1_Init(ADC1_CONVERSIONMODE_SINGLE, (ADC1_CHANNEL_0|ADC1_CHANNEL_1|ADC1_CHANNEL_2|ADC1_CHANNEL_3|ADC1_CHANNEL_4|ADC1_CHANNEL_5|ADC1_CHANNEL_6|ADC1_CHANNEL_7), ADC1_PRESSEL_FCPU_D2, ADC1_EXTTRIG_TIM, DISABLE, ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_ALL, ENABLE); 
////  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,(ADC1_CHANNEL_4),ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM, DISABLE,ADC1_ALIGN_RIGHT, (ADC1_SCHMITTTRIG_CHANNEL4),DISABLE);
//   ADC1_ScanModeCmd(ENABLE);//启用扫描模式
//   ADC1_DataBufferCmd(ENABLE);//启用缓存寄存器存储数据
//   ADC1_ITConfig(ADC1_IT_EOCIE,DISABLE);//关闭中断功能
//  ADC1_Cmd(ENABLE);//使能 ADC
//  u16 u16_adc1_value;//采样值
//  u16 VoltageValue;//转换后电压值
//  u8 SendBuf[30];//要发送的字符串
//  while (1){
//    ADC1_StartConversion();//启动转换
//    while(ADC1_GetFlagStatus(ADC1_FLAG_EOC)==RESET);//等待转换结束
//    u16_adc1_value=ADC1_GetConversionValue();//获取采样值 
//    VoltageValue=u16_adc1_value*3300UL/1023UL;//转换为电压值 
//    //发送给计算机 
//    sprintf(SendBuf,"ADC converted:%d mv  %d adc\r\n",VoltageValue,u16_adc1_value); 
//    ZLogUART(SendBuf);
//    Delay(200);
//  }
  
  
//  ZLogUART("start test \r\n");
//  while(1){
//    if(PA_IDR_IDR2==0){
//      ZLogUART("light on \r\n");
//    }else{
//      ZLogUART("light off \r\n");
//    }
//    ZDelay(200);
//  }
  
  
//  ZLogUART("start test \r\n");
  u16 AdcValue,VoltageValue;//ADC 后的值及转换后的电压值
  unsigned char SendBuf[64];//需要发送的字符串 
  ADC_CR1=0x00;//fADC=fMASTER/2、单次转换
//  ADC_CR1|=0x02; //连续扫描
  ADC_CSR=0x04;//选择 AIN4
  ADC_CR2|=0x08;// | 0x02;//数据右对齐, 扫描
  ADC_CR1|=0x01;//将 ADC 从低功耗唤醒并触发一次 AD 转换
  while(1) {
    ADC_CR1|=0x01;//使能转换
    while((ADC_CSR&0x80)==0);//等待转换结束 
    ADC_CSR&=~0x80;//清除转换结束标志 
    //获取装换后的值
    AdcValue=(unsigned int)ADC_DRL; 
    AdcValue|=(unsigned int)ADC_DRH<<8;
    
    //转换为电压值 
    VoltageValue=AdcValue*3300UL/1023UL; 
    if(AdcValue>300){
      PA_ODR_ODR2 = 1;
    }else{
      PA_ODR_ODR2 = 0;
    }
    //通过 UART发送给计算机
//    sprintf(SendBuf,"ADC %d mv %d adc \r\n",VoltageValue, AdcValue); 
//    ZLogUART(SendBuf);
//    ZDelay(50);
  }

} 