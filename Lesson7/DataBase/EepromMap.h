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
//* FILE NAME: SerialPort.c
//*
//* DESCRIPTION: STM8S Lesson6 example
//*
//* ORIGINATOR: Konglittle
//*
//* DATE: 2015-03-15
//*
//******************************************************************************
#ifndef _SERIALPORT_H
#define _SERIALPORT_H
#include "stm8s.h"

enum EE_Map_Sections
{
    EE_MAP_VERSION = 0,          //0
    EE_MAJOR_VERSION,            //1
    EE_NINOR_VERSION,            //2
    EE_BUILD_VERSION,            //3
    EE_BLINK_PERIOD,             //4
    EE_ADC_BRI_OFFSET,           //5
    EE_ADC_BRI_SCALE,            //6
    EE_LAST_SECTION              //7
};

/*define the EE_ID */
typedef struct
{
    uint16_t  EepAddress;      //the Address in the EEPORM
    uint16_t  EepDefaultValue;  //the default value
    void*   pRam;           //corresponding ram  address
    uint8_t  EepLength;      //length of Eeprom
}stEE_ID;

typedef struct
{
    uint16_t uwOffset;
    uint16_t uwScaleFactor;    
}stEepAdcCal;

extern stEepAdcCal EEP_strAdcCal;
extern stEE_ID Eeprom[EE_LAST_SECTION];
extern uint16_t uwEEP_EepromVersion;
extern uint16_t uwEEP_MajorVersion;
extern uint16_t uwEEP_MinorVersion;
extern uint16_t uwEEP_BuildVersion;
extern uint16_t uwEEP_BlinkPeriod;

extern void EepromInitial(void);
extern void EepromWriteSection(uint8_t ubEepSection, uint8_t *pData);
extern void EepromReadSection(uint8_t ubEepSection, uint8_t *pData);
#endif