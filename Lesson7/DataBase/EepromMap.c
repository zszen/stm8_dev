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
//* FILE NAME: EepromMap.c
//*
//* DESCRIPTION: STM8S Lesson1 example
//*
//* ORIGINATOR: Konglittle
//*
//* DATE: 2015-03-15
//*
//******************************************************************************
#include "EepromMap.h"
#include "stm8s_flash.h"

uint16_t uwEEP_EepromVersion = 0;
uint16_t uwEEP_MajorVersion = 0;
uint16_t uwEEP_MinorVersion = 0;
uint16_t uwEEP_BuildVersion = 0;
uint16_t uwEEP_BlinkPeriod = 0;
stEepAdcCal EEP_strAdcCal = {0, 0};

#define EEPROM_CURR_VERSION                    4
#define INIT_VERSION                           1
#define DEFAULT_PERIOD                         500
#define DEFAULT_OFFSET                         0
#define DEFAULT_SCALE                          1

#define EEPROM_BASE_ADDRESS                    0x4000
#define EepromUnlock()                         FLASH_Unlock(FLASH_MEMTYPE_DATA)
#define EepromLock()                           FLASH_Lock(FLASH_MEMTYPE_DATA)

#define EepromWriteByte(Address, Data)     FLASH_ProgramByte(Address + EEPROM_BASE_ADDRESS, Data)
#define EepromReadByte(Address)                FLASH_ReadByte(Address + EEPROM_BASE_ADDRESS)

void EepromInitial(void);
void EepromWriteSection(uint8_t ubEepSection, uint8_t *pData);
void EepromReadSection(uint8_t ubEepSection, uint8_t *pData);

stEE_ID Eeprom[EE_LAST_SECTION] =
{
    /*--------------------------------------------------------------------------
    |start address      |defaultValue       |pRam                 |size in byte      
    |                   |                   |                     |         
    --------------------------------------------------------------------------*/
    {0,     EEPROM_CURR_VERSION,         &uwEEP_EepromVersion,         2},
    
    {2,     INIT_VERSION,                &uwEEP_MajorVersion,     2},
    
    {4,     INIT_VERSION,                &uwEEP_MinorVersion,     2},
    
    {6,     INIT_VERSION,                &uwEEP_BuildVersion,     2},
    
    {8,     DEFAULT_PERIOD,              &uwEEP_BlinkPeriod,           2},
    
    {10,    DEFAULT_OFFSET,              &EEP_strAdcCal.uwOffset,      2},
    
    {12,    DEFAULT_SCALE,               &EEP_strAdcCal.uwScaleFactor, 2}
};


/*******************************************************************************
* Function Name  : EepromInitial.
* Description    : Initialize EEPROM Map
* Input          : None
* Output         : None.
* Return         : None.
*******************************************************************************/
void EepromInitial(void)
{
    uint8_t ubSectionIndex = 0;
    uint16_t uwEepVersion = 0;
    
    EepromReadSection(EE_MAP_VERSION, (uint8_t *)&uwEepVersion);
    
    if(uwEepVersion != EEPROM_CURR_VERSION)
    {
        //Power on for first time, write default value to EEPROM
        for(ubSectionIndex = EE_MAP_VERSION; ubSectionIndex < EE_LAST_SECTION; ubSectionIndex++)
        {
            EepromWriteSection(ubSectionIndex, (uint8_t *)&Eeprom[ubSectionIndex].EepDefaultValue);
        }
        
    }
    
    //Copy Eeprom data into ram_copy
    for(ubSectionIndex = EE_MAP_VERSION; ubSectionIndex < EE_LAST_SECTION; ubSectionIndex++)
    {
        EepromReadSection(ubSectionIndex, (uint8_t *)Eeprom[ubSectionIndex].pRam);
    }
}

void EepromWriteSection(uint8_t ubEepSection, uint8_t *pData)
{
    uint8_t ubIndex = 0;
    uint8_t ubTempData = 0;
    uint8_t *pEepRam = (uint8_t*)Eeprom[ubEepSection].pRam;
    
    EepromUnlock();
    for(ubIndex = 0; ubIndex < Eeprom[ubEepSection].EepLength; ubIndex++)
    {
        ubTempData = *(pData + ubIndex);
        //Write into EEPROM
        EepromWriteByte(Eeprom[ubEepSection].EepAddress + ubIndex, ubTempData);
        //Also save a copy into RAM
        *(pEepRam + ubIndex) = ubTempData;
    }
    EepromLock();
}



void EepromReadSection(uint8_t ubEepSection, uint8_t *pData)
{
    uint8_t ubIndex = 0;
    
    EepromUnlock();
    for(ubIndex = 0; ubIndex < Eeprom[ubEepSection].EepLength; ubIndex++)
    {
        *(pData + ubIndex) = EepromReadByte(Eeprom[ubEepSection].EepAddress + ubIndex);
    }
    EepromLock();
}
    