#ifndef __DK_SPI_h__
#define __DK_SPI_h__

#include "stm8l15x.h"

/*
	PC8			NSEL
	PC6			SCK
	PC5			SDI
	PD8			SDO
	PA12		DIO
	PC9			NIRQ
*/

//主动发送模块脚配置
//#define RF_RESET_GPIO_Port    GPIOD
//#define RF_RESET_Pin     GPIO_Pin_5

#define RF_NSEL_GPIO_Port    GPIOB
#define RF_NSEL_Pin     GPIO_Pin_4

#define RF_SCLK_GPIO_Port    GPIOB
#define RF_SCLK_Pin     GPIO_Pin_5

#define RF_MOSI_GPIO_Port    GPIOB
#define RF_MOSI_Pin     GPIO_Pin_6

#define RF_MISO_GPIO_Port    GPIOB
#define RF_MISO_Pin     GPIO_Pin_7

//#define RF_DIO0_GPIO_Port    GPIOC
//#define RF_DIO0_Pin     GPIO_Pin_4


#define nSEL_H  GPIO_WriteBit(RF_NSEL_GPIO_Port, RF_NSEL_Pin, SET);
#define nSEL_L  GPIO_WriteBit(RF_NSEL_GPIO_Port, RF_NSEL_Pin, RESET);

#define SCK_H   GPIO_WriteBit(RF_SCLK_GPIO_Port, RF_SCLK_Pin, SET);
#define SCK_L   GPIO_WriteBit(RF_SCLK_GPIO_Port, RF_SCLK_Pin, RESET);

#define SDI_H   GPIO_WriteBit(RF_MOSI_GPIO_Port, RF_MOSI_Pin, SET);
#define SDI_L   GPIO_WriteBit(RF_MOSI_GPIO_Port, RF_MOSI_Pin, RESET);

#define Get_SDO() (RF_MISO_GPIO_Port->IDR & RF_MISO_Pin)==RF_MISO_Pin

//被动接收模块脚配置
//#define RF_RESET_GPIO_Port_2    GPIOD
//#define RF_RESET_Pin_2     GPIO_Pin_5

#define RF_NSEL_GPIO_Port_2    GPIOD
#define RF_NSEL_Pin_2     GPIO_Pin_4

#define RF_SCLK_GPIO_Port_2    GPIOD
#define RF_SCLK_Pin_2     GPIO_Pin_5

#define RF_MOSI_GPIO_Port_2    GPIOD
#define RF_MOSI_Pin_2     GPIO_Pin_6

#define RF_MISO_GPIO_Port_2    GPIOD
#define RF_MISO_Pin_2     GPIO_Pin_7

//#define RF_DIO0_GPIO_Port_2    GPIOC
//#define RF_DIO0_Pin_2     GPIO_Pin_4


#define nSEL_H_2  GPIO_WriteBit(RF_NSEL_GPIO_Port_2, RF_NSEL_Pin_2, SET);
#define nSEL_L_2  GPIO_WriteBit(RF_NSEL_GPIO_Port_2, RF_NSEL_Pin_2, RESET);

#define SCK_H_2   GPIO_WriteBit(RF_SCLK_GPIO_Port_2, RF_SCLK_Pin_2, SET);
#define SCK_L_2   GPIO_WriteBit(RF_SCLK_GPIO_Port_2, RF_SCLK_Pin_2, RESET);

#define SDI_H_2   GPIO_WriteBit(RF_MOSI_GPIO_Port_2, RF_MOSI_Pin_2, SET);
#define SDI_L_2   GPIO_WriteBit(RF_MOSI_GPIO_Port_2, RF_MOSI_Pin_2, RESET);

#define Get_SDO_2() (RF_MISO_GPIO_Port_2->IDR & RF_MISO_Pin_2)==RF_MISO_Pin_2

//#define nRESET_H  GPIO_WriteBit(RF_RESET_GPIO_Port, RF_RESET_Pin, SET);
//#define nRESET_L  GPIO_WriteBit(RF_RESET_GPIO_Port, RF_RESET_Pin, RESET);

//#define Get_NIRQ0() (RF_DIO0_GPIO_Port->IDR & RF_DIO0_Pin)==RF_DIO0_Pin


void SPIHwInit(void);
void SPICmd8bit(u8 WrPara);
u8 SPIRead(u8 adr);
u8 SPIRead8bit(void);
void SPIWrite(u8 adr, u8 WrPara);
void SPIBurstRead(u8 adr, u8 *ptr, u8 length);
void BurstWrite(u8 adr, u8 *ptr, u8 length);
extern __IO u32 SystickCount;
#endif







