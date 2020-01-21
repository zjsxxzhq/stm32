#ifndef _DS18B20_H_
#define _DS18B20_H_
#include "stm8l15x.h"
typedef enum {FAILED=0,PASSED=!FAILED}TestStatus;

//Register commands
#define REGISTER_9_BITS  0X1F
#define REGISTER_10_BITS 0X3F
#define REGISTER_11_BITS 0X5F
#define REGISTER_12_BITS 0X7F

//ROM COMMANDS
#define ROM_Search_Cmd 0xF0
#define ROM_Read_Cmd   0x33
#define ROM_Match_Cmd  0x55
#define ROM_Skip_Cmd   0xCC
#define ROM_AlarmSearch_Cmd 0xEC

//DS18b20 FUNCTION COM
#define Convert_T        0X44
#define Write_Scratchpad 0x4E
#define Read_Scratchpad  0xBE
#define Copy_Scratchpad  0x48
#define Recall_EEPROM    0x88
#define Read_PowerSupply    0x84

#define DQ1_GPIO_Port    GPIOC
#define DQ1_Pin    GPIO_Pin_0

#define DQ0_Write_0()  DQ1_GPIO_Port->ODR &= (uint8_t)(~DQ1_Pin);

#define DQ0_Write_1()  DQ1_GPIO_Port->ODR |= DQ1_Pin;

#define DQ0_ReadBit()  (DQ1_GPIO_Port->IDR & DQ1_Pin)==DQ1_Pin

extern __IO u32 SystickCount;

void Read_Temperature(void);
void DS18B20_GPIO_Config(void);
void delay_us_(u16 time);
extern unsigned char ds18b20_error_flag[1];
extern unsigned char sign[1];
extern unsigned char interger[1];
extern unsigned int decimal[1];
extern s16 ds18b20_temp[1];
#endif






