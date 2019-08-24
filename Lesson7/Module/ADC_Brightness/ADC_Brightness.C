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
//* FILE NAME: ADC_Brightness.c
//*
//* DESCRIPTION: STM8S Practice example
//*
//* ORIGINATOR: Konglittle
//*
//* DATE: 2015-04-19
//*
//******************************************************************************
#include "stm8s.h"
#include "stm8s_adc1.h"
#include "EepromMap.h"

#define ADC_DIGITAL_MAX  1023    //2^10 - 1
#define ADC_VDD_X100     330     //3.3V * 100
#define ADC_MAX_BRI_VOLTS    320     //3.2V * 100
#define ADC_MIN_BRI_VOLTS      8     //0.08 * 100

uint16_t ADC_Brightness = 0;

void ADC_BrightnessTask(void)
{
    static uint16_t uwAdcSample = 0;
    
    //Start a conversion
    ADC1_StartConversion();
    //Wait until conversion finish
    while(!ADC1_GetFlagStatus(ADC1_FLAG_EOC));
    
    uwAdcSample = (ADC1_GetConversionValue() - EEP_strAdcCal.uwOffset + uwAdcSample) / 2;
    
    ADC1_ClearFlag(ADC1_FLAG_EOC);
    
    //Convert it to voltage * 100
    ADC_Brightness = (uint16_t)((uint32_t)uwAdcSample * (uint32_t)ADC_VDD_X100 / (uint32_t)ADC_DIGITAL_MAX);
    
    if(ADC_Brightness < ADC_MIN_BRI_VOLTS)
    {
        ADC_Brightness = ADC_MIN_BRI_VOLTS;
    }   
    
    if(ADC_Brightness > ADC_MAX_BRI_VOLTS)
    {
        ADC_Brightness = ADC_MAX_BRI_VOLTS;
    }
    
    //Convert it to brightness
    ADC_Brightness = (ADC_Brightness * 100 * EEP_strAdcCal.uwScaleFactor) / (ADC_MAX_BRI_VOLTS - ADC_MIN_BRI_VOLTS);
    
    if(ADC_Brightness > 100)
    {
        ADC_Brightness = 100;
    }
    
    ADC_Brightness = 100 - ADC_Brightness;
}