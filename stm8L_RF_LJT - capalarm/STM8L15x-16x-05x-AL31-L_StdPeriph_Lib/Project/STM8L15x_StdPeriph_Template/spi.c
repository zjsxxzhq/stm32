// ========================================================
/// @file       SPI.c
/// @brief      Software simulation SPI performance function
/// @version    V1.0
/// @date       2014/05/04
/// @company    HR_WT.
/// @website    http://www.HR_WT.com
/// @author     ISA
/// @mobile     
/// @tel        
// ========================================================
#include "stm8l15x.h"
#include "spi.h"


u8 rf_sel=0;//0主动发送模块,1被动接收模块

void SPIHwInit(void)
{
//  GPIO_Init(RF_RESET_GPIO_Port, RF_RESET_Pin, GPIO_Mode_Out_PP_High_Fast);  //RESET
  //主动发送模块初始化IO
  GPIO_Init(RF_NSEL_GPIO_Port, RF_NSEL_Pin, GPIO_Mode_Out_PP_High_Fast);  //NSS
  GPIO_Init(RF_SCLK_GPIO_Port, RF_SCLK_Pin, GPIO_Mode_Out_PP_High_Fast);  //MOSI
  GPIO_Init(RF_MOSI_GPIO_Port, RF_MOSI_Pin, GPIO_Mode_Out_PP_High_Fast);  //CLK 
  GPIO_Init(RF_MISO_GPIO_Port, RF_MISO_Pin, GPIO_Mode_In_PU_No_IT);  //MISO
//  GPIO_Init(RF_DIO0_GPIO_Port, RF_DIO0_Pin, GPIO_Mode_In_PU_No_IT);  //DIO0
  //被动接收模块初始化IO
#if(0)
  GPIO_Init(RF_NSEL_GPIO_Port_2, RF_NSEL_Pin_2, GPIO_Mode_Out_PP_High_Fast);  //NSS
  GPIO_Init(RF_SCLK_GPIO_Port_2, RF_SCLK_Pin_2, GPIO_Mode_Out_PP_High_Fast);  //MOSI
  GPIO_Init(RF_MOSI_GPIO_Port_2, RF_MOSI_Pin_2, GPIO_Mode_Out_PP_High_Fast);  //CLK 
  GPIO_Init(RF_MISO_GPIO_Port_2, RF_MISO_Pin_2, GPIO_Mode_In_PU_No_IT);  //MISO
#endif
/*  
  nRESET_L
  SystickCount=100;
  while(SystickCount);
  nRESET_H
*/
}
/**********************************************************
**Name:     SPICmd8bit
**Function: SPI Write one byte
**Input:    WrPara
**Output:   none
**note:     use for burst mode
**********************************************************/
void SPICmd8bit(u8 WrPara)
{
  u8 bitcnt;
  if(rf_sel==0){
  nSEL_L
  SCK_L
  
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    SCK_L
    if(WrPara&0x80)
      SDI_H
    else
      SDI_L
    SCK_H
    WrPara <<= 1;
  }
  SCK_L
  SDI_H
  }
  else if(rf_sel==1){
  nSEL_L_2
  SCK_L_2
  
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    SCK_L_2
    if(WrPara&0x80)
      SDI_H_2
    else
      SDI_L_2
    SCK_H_2
    WrPara <<= 1;
  }
  SCK_L_2
  SDI_H_2
  }
}

/**********************************************************
**Name:     SPIRead8bit
**Function: SPI Read one byte
**Input:    None
**Output:   result byte
**Note:     use for burst mode
**********************************************************/
u8 SPIRead8bit(void)
{
 u8 RdPara = 0;
 u8 bitcnt;
  if(rf_sel==0){ 
  nSEL_L
  SDI_H                                                 //Read one byte data from FIFO, MOSI hold to High
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    SCK_L
    RdPara <<= 1;
    SCK_H
    if(Get_SDO())
      RdPara |= 0x01;
    else
      RdPara |= 0x00;
  }
  SCK_L
  return(RdPara);
  }
  else if(rf_sel==1){ 
  nSEL_L_2
  SDI_H_2                                                 //Read one byte data from FIFO, MOSI hold to High
  for(bitcnt=8; bitcnt!=0; bitcnt--)
  {
    SCK_L_2
    RdPara <<= 1;
    SCK_H_2
    if(Get_SDO_2())
      RdPara |= 0x01;
    else
      RdPara |= 0x00;
  }
  SCK_L_2
  return(RdPara);
  } 
  return(RdPara);
}

/**********************************************************
**Name:     SPIRead
**Function: SPI Read CMD
**Input:    adr -> address for read
**Output:   None
**********************************************************/
u8 SPIRead(u8 adr)
{
    u8 tmp; 
    SPICmd8bit(adr);                                         //Send address first
    tmp = SPIRead8bit(); 
    if(rf_sel==0){
    nSEL_H
    }
    else if(rf_sel==1){
    nSEL_H_2
    }
    return(tmp);
}

/**********************************************************
**Name:     SPIWrite
**Function: SPI Write CMD
**Input:    u8 address & u8 data
**Output:   None
**********************************************************/
void SPIWrite(u8 adr, u8 WrPara)  
{
        if(rf_sel==0){	
	nSEL_L						 
	SPICmd8bit(adr|0x80);		 //写入地址 
	SPICmd8bit(WrPara);//写入数据	
	SCK_L
        SDI_H
        nSEL_H
        }
        else if(rf_sel==1){	
	nSEL_L_2						 
	SPICmd8bit(adr|0x80);		 //写入地址 
	SPICmd8bit(WrPara);//写入数据	
	SCK_L_2
        SDI_H_2
        nSEL_H_2
        }
}
/**********************************************************
**Name:     SPIBurstRead
**Function: SPI burst read mode
**Input:    adr-----address for read
**          ptr-----data buffer point for read
**          length--how many bytes for read
**Output:   None
**********************************************************/
void SPIBurstRead(u8 adr, u8 *ptr, u8 length)
{
    u8 i;
    if(length<=1)                                            //length must more than one
      return;
    else
    {
      if(rf_sel==0){
      SCK_L
      nSEL_L
      SPICmd8bit(adr); 
      for(i=0;i<length;i++)
      ptr[i] = SPIRead8bit();
      nSEL_H 
      }
      else if(rf_sel==1){
      SCK_L_2
      nSEL_L_2
      SPICmd8bit(adr); 
      for(i=0;i<length;i++)
      ptr[i] = SPIRead8bit();
      nSEL_H_2 
      }
    }
}

/**********************************************************
**Name:     SPIBurstWrite
**Function: SPI burst write mode
**Input:    adr-----address for write
**          ptr-----data buffer point for write
**          length--how many bytes for write
**Output:   none
**********************************************************/
void BurstWrite(u8 adr, u8 *ptr, u8 length)
{ 
  u8 i;

  if(length<=1)                                            //length must more than one
    return;
  else  
  { 
    if(rf_sel==0){
    SCK_L
    nSEL_L        
    SPICmd8bit(adr|0x80);
    for(i=0;i<length;i++)
    SPICmd8bit(ptr[i]);
    nSEL_H 
    }
    else if(rf_sel==1){
    SCK_L_2
    nSEL_L_2        
    SPICmd8bit(adr|0x80);
    for(i=0;i<length;i++)
    SPICmd8bit(ptr[i]);
    nSEL_H_2 
    }
  }
}





