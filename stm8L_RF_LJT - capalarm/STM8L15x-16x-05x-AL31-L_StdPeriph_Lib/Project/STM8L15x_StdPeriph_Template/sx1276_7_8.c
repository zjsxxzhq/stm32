//#include "main.h"
#include "stm8l15x.h"
#include "sx1276_7_8.h"
#include "spi.h"
#include "math.h"
#include "stdlib.h"
#include "define.h"
/************************Description************************
************************************************	
									 ---------------
	   key2 ----    |PD4         PD3|	 ----key1
 GREEN_LED----    |PD5         PD2|	 ----NIRQ
   RED_LED----    |PD6         PD1|	 ----
	    	  ----    |NRST        PC7|   ----SDO
	        ----    |PA1         PC6|   ----SDI
 	        ----    |PA2         PC5|	 ----SCK
	    	  ----    |Vss         PC4|   ----
		      ----    |Vcap        PC3|   ----SDN
		      ----    |Vdd         PB4|	 ----
		  NSEL----    |PA3         PB5|	 ----
									---------------
										stm8s103f3p
************************************************/
/************************************************
//  RF module:           sx1276_7_8
//  FSK:
//  Carry Frequency:     434MHz
//  Bit Rate:            1.2Kbps/2.4Kbps/4.8Kbps/9.6Kbps
//  Tx Power Output:     20dbm/17dbm/14dbm/11dbm
//  Frequency Deviation: +/-35KHz
//  Receive Bandwidth:   83KHz
//  Coding:              NRZ
//  Packet Format:       0x5555555555+0xAA2DD4+"HR_WT Lora sx1276_7_8" (total: 29 bytes)
//  LoRa:
//  Carry Frequency:     434MHz
//  Spreading Factor:    6/7/8/9/10/11/12
//  Tx Power Output:     20dbm/17dbm/14dbm/11dbm
//  Receive Bandwidth:   7.8KHz/10.4KHz/15.6KHz/20.8KHz/31.2KHz/41.7KHz/62.5KHz/125KHz/250KHz/500KHz
//  Coding:              NRZ
//  Packet Format:       "HR_WT Lora sx1276_7_8" (total: 21 bytes)
//  Tx Current:          about 120mA  (RFOP=+20dBm,typ.)
//  Rx Current:          about 11.5mA  (typ.)       
**********************************************************/

/**********************************************************
**Parameter table define
**********************************************************/

const u8 sx1276_7_8FreqTbl[2][3] = 
{ 
  {0x6C, 0x80, 0x00}, //434MHz
  {0X6F,0x00,0x00},//444MHz
};

const u8 sx1276_7_8PowerTbl[4] =
{ 
  0xFF,                   //20dbm  
  0xFC,                   //17dbm
  0xF9,                   //14dbm
  0xF6,                   //11dbm 
};

const u8 sx1276_7_8SpreadFactorTbl[7] =//7`12
{
  6,7,8,9,10,11,12
};

const u8 sx1276_7_8LoRaBwTbl[10] =
{
//7.8KHz,10.4KHz,15.6KHz,20.8KHz,31.2KHz,41.7KHz,62.5KHz,125KHz,250KHz,500KHz
  0,1,2,3,4,5,6,7,8,9
};


//{"HR_WT Lora sx1276_7_8"};

u8 RxData[256];
u16 RxLen;
u8 TxData[256];
u16 TxLen;
u8 RF_IsrReg;
u8 Freq_Sel;//
u8 Power_Sel;//
u8 Lora_Rate_Sel;//
u8 BandWide_Sel;//
u8 Fsk_Rate_Sel;//
void sx1276_7_8_Standby(void);
/**********************************************************
**Variable define
**********************************************************/

void sx1276_7_8_Config(void);
void sx1276_7_8_Sleep(void);
void sx1276_7_8_Standby(void);
void sx1276_7_8_EntryLoRa(void);
void sx1276_7_8_LoRaClearIrq(void);
u8 sx1276_7_8LoRaEntryCAD(void);
u8 sx1276_7_8_ReadRSSI(void);
/**********************************************************
**Name:     sx1276_7_8_Standby
**Function: Entry standby mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_Standby(void)
{
  SPIWrite(LR_RegOpMode,0x09);                              		//Standby//Low Frequency Mode
	//SPIWrite(LR_RegOpMode,0x01);                              	 //Standby//High Frequency Mode
}

/**********************************************************
**Name:     sx1276_7_8_Sleep
**Function: Entry sleep mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_Sleep(void)
{
  SPIWrite(LR_RegOpMode,0x08);                              		//Sleep//Low Frequency Mode
	//SPIWrite(LR_RegOpMode,0x00);                            		 //Sleep//High Frequency Mode
}

/*********************************************************/
//LoRa mode
/*********************************************************/
/**********************************************************
**Name:     sx1276_7_8_EntryLoRa
**Function: Set RFM69 entry LoRa(LongRange) mode
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_EntryLoRa(void)
{
  SPIWrite(LR_RegOpMode,0x88);//Low Frequency Mode
	//SPIWrite(LR_RegOpMode,0x80);//High Frequency Mode
}

/**********************************************************
**Name:     sx1276_7_8_LoRaClearIrq
**Function: Clear all irq
**Input:    None
**Output:   None
**********************************************************/
void sx1276_7_8_LoRaClearIrq(void)
{
  SPIWrite(LR_RegIrqFlags,0xFF);
}



/*
发送数据前进行信道检测,
如果返回1,表示信道检测到前导码
如果返回0,表示信道没有检测到前导码
*/
u8 sx1276_7_8LoRaEntryCAD(void)
{
  u8 i;

  //进入待机
  sx1276_7_8_Standby();
//  HAL_Delay(10);
//  SPIWrite(REG_LR_DIOMAPPING1,0x81);//DIO0=10, DIO1=00, DIO2=00, DIO3=01
//  SPIWrite(REG_LR_DIOMAPPING2,0x20);
  //设置CADDONE中断和CADDETECTED中断
  SPIWrite(LR_RegIrqFlagsMask,0xFA);
  //清除中断
  sx1276_7_8_LoRaClearIrq();
  
  //进入CAD模式
  SPIWrite(LR_RegOpMode,0x0F);
//  HAL_Delay(10);
  //等待caddone信号
  
#if(0)  
  do
  {
    RF_IsrReg=SPIRead(LR_RegIrqFlags);
  }
  while((RF_IsrReg&0x04)!=0x04);
    
  if(RF_IsrReg==0x05)
  {
    sx1276_7_8_LoRaClearIrq();
    return 1;
  }
  else
  {
    sx1276_7_8_LoRaClearIrq();
    return 0;
  }
#endif
  
#if(1)
  while(1)
  {
    RF_IsrReg=SPIRead(LR_RegIrqFlags);
    i++;
    if((RF_IsrReg&0x04)==0x04)
    //if(Get_NIRQ0())
    {
      RF_IsrReg=SPIRead(LR_RegIrqFlags);
      SPIWrite(LR_RegIrqFlags,0x04);//清除caddone中断
      if((RF_IsrReg&0x01)==0x01)

      {
        SPIWrite(LR_RegIrqFlags,0x01);//清除caddetected中断
        return 1;
      }
      else
      {
        return 0;
      }
      
    }
  }
#endif

}
//等待信道空闲
void Wait_Rf_Idle(void)
{
  char jj;
  jj=0;
  while(1)
  {
    if(sx1276_7_8LoRaEntryCAD()==0)
    {
      jj++;
        
    }
    else
    {
      jj=0;
      SystickCount=(abs(rand())%600);
      while(SystickCount);
    }
    if(jj==2)
    {
      //HAL_Delay(abs(rand())%100);
      break;//累计20次没有检测到前导码,认为信道空闲
    }
  }  
}
/**********************************************************
**Name:     sx1276_7_8_LoRaEntryRx
**Function: Entry Rx mode
**Input:    None
**Output:   None
**********************************************************/
u8 sx1276_7_8_LoRaEntryRx(void)
{
  u8 addr; 
        
  sx1276_7_8_Config();                                         //setting base parameter
  
  SPIWrite(REG_LR_PADAC,0x84);                              //Normal and Rx
  SPIWrite(LR_RegHopPeriod,0xFF);                          //RegHopPeriod NO FHSS
  SPIWrite(REG_LR_DIOMAPPING1,0x01);                       //DIO0=00, DIO1=00, DIO2=00, DIO3=01
      
  SPIWrite(LR_RegIrqFlagsMask,0x1F);                       //Open RxDone interrupt & Timeout
  sx1276_7_8_LoRaClearIrq();   
  
  if(sx1276_7_8SpreadFactorTbl[Lora_Rate_Sel]==6)
  SPIWrite(LR_RegPayloadLength,21);                       //RegPayloadLength  21byte(this register must difine when the data long of one byte in SF is 6)
    
  addr = SPIRead(LR_RegFifoRxBaseAddr);           				//Read RxBaseAddr
  SPIWrite(LR_RegFifoAddrPtr,addr);                        //RxBaseAddr -> FiFoAddrPtr　 
  SPIWrite(LR_RegOpMode,0x8d);                        		//Continuous Rx Mode//Low Frequency Mode
  //SPIWrite(LR_RegOpMode,0x05);                        		//Continuous Rx Mode//High Frequency Mode
  u8 SysTime = 0;
  while(1)
  {
//                OSTimeDlyHMSM(0, 0, 0,2);
    SystickCount=2;
    while(SystickCount);
    
    if((SPIRead(LR_RegModemStat)&0x04)==0x04)   //Rx-on going RegModemStat
    return 1;
    if(SysTime>=3)	
    return 0;                                              //over time for error
  }
}

/**********************************************************
**Name:     sx1276_7_8_LoRaReadRSSI
**Function: Read the RSSI value
**Input:    none
**Output:   temp, RSSI value
**********************************************************/
u8 sx1276_7_8_LoRaReadRSSI(void)
{
  u16 temp=10;
  temp=SPIRead(LR_RegRssiValue);                  //Read RegRssiValue，Rssi value
  temp=temp+127-137;                                       //127:Max RSSI, 137:RSSI offset
  return (u8)temp;
}

/**********************************************************
**Name:     sx1276_7_8_LoRaRxPacket
**Function: Receive data in LoRa mode
**Input:    None
**Output:   1- Success
            0- Fail
**********************************************************/
u8 sx1276_7_8_LoRaRxPacket(void)
{
  u8 addr;
  RF_IsrReg=SPIRead(LR_RegIrqFlags);
  //if(Get_NIRQ0())
  if((RF_IsrReg&0x40)==0x40)
  {
    //for(i=0;i<255;i++) 
    //  RxData[i] = 0;     
    addr = SPIRead(LR_RegFifoRxCurrentaddr);      //last packet addr
    SPIWrite(LR_RegFifoAddrPtr,addr);                      //RxBaseAddr -> FiFoAddrPtr    
    if(sx1276_7_8SpreadFactorTbl[EE_Para.sf]==6)           //When SpreadFactor is six，will used Implicit Header mode(Excluding internal packet length)
      RxLen=21;//固定字节
    else
      RxLen = SPIRead(LR_RegRxNbBytes);     //Number for received bytes    
    SPIBurstRead(0x00, RxData, RxLen);   
    sx1276_7_8_LoRaClearIrq();
    if((RF_IsrReg&0x20)==0x20)
    {
      return (2);//crc错误
    }
    else
    {
      return 1;//有正确数据收到
    }
  }
  else
    return(0);//没有数据收到
}

/**********************************************************
**Name:     sx1276_7_8_LoRaEntryTx
**Function: Entry Tx mode
**Input:    None
**Output:   None
**********************************************************/
u8 sx1276_7_8_LoRaEntryTx(void)
{
  u8 TimeCount = 3;
  u8 addr;
  sx1276_7_8_Config();                                         //setting base parameter
    
  SPIWrite(REG_LR_PADAC,0x87);                                   //Tx for 20dBm
  SPIWrite(LR_RegHopPeriod,0x00);                               //RegHopPeriod NO FHSS
  SPIWrite(REG_LR_DIOMAPPING1,0x41);                       //DIO0=01, DIO1=00, DIO2=00, DIO3=01
  
  sx1276_7_8_LoRaClearIrq();
  SPIWrite(LR_RegIrqFlagsMask,0xF7);                       //Open TxDone interrupt
  SPIWrite(LR_RegPayloadLength,TxLen);                     //RegPayloadLength  21byte
  
  addr = SPIRead(LR_RegFifoTxBaseAddr);           //RegFiFoTxBaseAddr
  SPIWrite(LR_RegFifoAddrPtr,addr);                        //RegFifoAddrPtr

  while(TimeCount--)
  {
//                OSTimeDlyHMSM(0, 0, 0,2);
    SystickCount=10;
    while(SystickCount);
    if(SPIRead(LR_RegPayloadLength)==TxLen)
    {
      return 1; 
    }
  }
  return 0;
}
/**********************************************************
**Name:     sx1276_7_8_LoRaTxPacket
**Function: Send data in LoRa mode
**Input:    None
**Output:   1- Send over
**********************************************************/
u8 sx1276_7_8_LoRaTxPacket(void)
{ 
  u16    timecount=3000;
  BurstWrite(0x00, (u8 *)TxData, TxLen);
  SPIWrite(LR_RegOpMode,0x8b);                    //Tx Mode  
   
  while(timecount--)
  {
    SystickCount=1;
    while(SystickCount);
    RF_IsrReg=SPIRead(LR_RegIrqFlags);
    if((RF_IsrReg&0x08)==0x08)
    //if(Get_NIRQ0())                      //Packet send over
    {  		
      //RF_IsrReg=SPIRead(LR_RegIrqFlags);
      sx1276_7_8_LoRaClearIrq();                                //Clear irq				
      sx1276_7_8_Standby();                                     //Entry Standby mode
      return 1;
    }
  } 
  return 0;
}

/**********************************************************
**Name:     sx1276_7_8_ReadRSSI
**Function: Read the RSSI value
**Input:    none
**Output:   temp, RSSI value
**********************************************************/
u8 sx1276_7_8_ReadRSSI(void)
{
  u8 temp=0xff;
	
  temp=SPIRead(0x11);
  temp>>=1;
  temp=127-temp;                                           //127:Max RSSI
  return temp;
}
/**********************************************************
**Name:     sx1276_7_8_Config
**Function: sx1276_7_8 base config
**Input:    mode
**Output:   None
**********************************************************/
void sx1276_7_8_Config(void)
{
  u8 i; 
    
  sx1276_7_8_Sleep();                                      //Change modem mode Must in Sleep mode 
  for(i=250;i!=0;i--);                                      //Delay
    
//  delay_us(15000);
  delay(15);
	//延时15ms
  //lora mode
	sx1276_7_8_EntryLoRa();  
	//SPIWrite(0x5904);   //?? Change digital regulator form 1.6V to 1.47V: see errata note
        
        BurstWrite(LR_RegFrMsb,(u8*)EE_Para.rfmhz,3);  //setting frequency parameter
  
	

	//setting base parameter 
	SPIWrite(LR_RegPaConfig,sx1276_7_8PowerTbl[EE_Para.pw]);             //Setting output power parameter  
    
	//SPIWrite(LR_RegOcp,0x0B);                              //RegOcp,Close Ocp
        SPIWrite(LR_RegOcp,0x3B); 
	SPIWrite(LR_RegLna,0x23);                              //RegLNA,High & LNA Enable
    
//	if(sx1276_7_8SpreadFactorTbl[EE_Para.sf]==6)           //SFactor=6
        if(EE_Para.sf==6) 
	{
		u8 tmp;
		SPIWrite(LR_RegModemConfig1,((sx1276_7_8LoRaBwTbl[EE_Para.bw]<<4)+(EE_Para.cr<<1)+0x01));//Implicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		//SPIWrite(LR_RegModemConfig2,((sx1276_7_8SpreadFactorTbl[EE_Para.sf]<<4)+(_CRC<<2)+0x03));
                SPIWrite(LR_RegModemConfig2,((EE_Para.sf<<4)+(_CRC<<2)+0x03));
      
		tmp = SPIRead(0x31);
		tmp &= 0xF8;
		tmp |= 0x05;
		SPIWrite(0x31,tmp);
		SPIWrite(0x37,0x0C);
	} 
	else
	{
		SPIWrite(LR_RegModemConfig1,((sx1276_7_8LoRaBwTbl[EE_Para.bw]<<4)+(EE_Para.cr<<1)+0x00));//Explicit Enable CRC Enable(0x02) & Error Coding rate 4/5(0x01), 4/6(0x02), 4/7(0x03), 4/8(0x04)
		//SPIWrite(LR_RegModemConfig2,((sx1276_7_8SpreadFactorTbl[EE_Para.sf]<<4)+(_CRC<<2)+0x03));  //SFactor &  LNA gain set by the internal AGC loop 
                SPIWrite(LR_RegModemConfig2,(((u8)EE_Para.sf<<4)+(_CRC<<2)+0x03));
        }
	SPIWrite(LR_RegSymbTimeoutLsb,0xFF);                   //RegSymbTimeoutLsb Timeout = 0x3FF(Max) 
    
	SPIWrite(LR_RegPreambleMsb,EE_Para.pp>>8);                       //RegPreambleMsb 
	SPIWrite(LR_RegPreambleLsb,EE_Para.pp);                      //RegPreambleLsb 8+4=12byte Preamble，默认是12
    
	SPIWrite(REG_LR_DIOMAPPING2,0x01);                     //RegDioMapping2 DIO5=00, DIO4=01
	if(EE_Para.lowspeed==1)
        SPIWrite(0X26, 12);
        else
        SPIWrite(0X26, 4);
        
        SPIWrite(0X39,EE_Para.rfaddr);//写地址

        
        sx1276_7_8_Standby();                                         //Entry standby mode
}

void LoRaSetRFFrequency( uint32_t freq,u8 freset[] )
{

    freq = ( uint32_t )( ( double )freq / ( double )61.03515625 );
    freset[0] = ( uint8_t )( ( freq >> 16 ) & 0xFF );
    freset[1] = ( uint8_t )( ( freq >> 8 ) & 0xFF );
    freset[2] = ( uint8_t )( freq & 0xFF );
}









