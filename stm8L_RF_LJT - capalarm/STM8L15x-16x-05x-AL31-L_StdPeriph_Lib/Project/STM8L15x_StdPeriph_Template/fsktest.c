#include "stm8l15x.h"
#include "stdio.h"
#include "string.h"
#include "sx1276_7_8.h"
#include "spi.h"
#include "ds18b20.h"  
#include "define.h"
#include "SI7021.h"
/*!
 * SX1276 Internal registers Address
 */
#define REG_FIFO                                    0x00
// Common settings
#define REG_OPMODE                                  0x01
#define REG_BITRATEMSB                              0x02
#define REG_BITRATELSB                              0x03
#define REG_FDEVMSB                                 0x04 
#define REG_FDEVLSB                                 0x05
#define REG_FRFMSB                                  0x06
#define REG_FRFMID                                  0x07
#define REG_FRFLSB                                  0x08
// Tx settings
#define REG_PACONFIG                                0x09
#define REG_PARAMP                                  0x0A
#define REG_OCP                                     0x0B 
// Rx settings
#define REG_LNA                                     0x0C
#define REG_RXCONFIG                                0x0D
#define REG_RSSICONFIG                              0x0E
#define REG_RSSICOLLISION                           0x0F
#define REG_RSSITHRESH                              0x10
#define REG_RSSIVALUE                               0x11
#define REG_RXBW                                    0x12 
#define REG_AFCBW                                   0x13
#define REG_OOKPEAK                                 0x14
#define REG_OOKFIX                                  0x15
#define REG_OOKAVG                                  0x16
#define REG_RES17                                   0x17
#define REG_RES18                                   0x18
#define REG_RES19                                   0x19
#define REG_AFCFEI                                  0x1A
#define REG_AFCMSB                                  0x1B
#define REG_AFCLSB                                  0x1C
#define REG_FEIMSB                                  0x1D
#define REG_FEILSB                                  0x1E
#define REG_PREAMBLEDETECT                          0x1F
#define REG_RXTIMEOUT1                              0x20
#define REG_RXTIMEOUT2                              0x21
#define REG_RXTIMEOUT3                              0x22
#define REG_RXDELAY                                 0x23
// Oscillator settings
#define REG_OSC                                     0x24
// Packet handler settings
#define REG_PREAMBLEMSB                             0x25
#define REG_PREAMBLELSB                             0x26
#define REG_SYNCCONFIG                              0x27
#define REG_SYNCVALUE1                              0x28
#define REG_SYNCVALUE2                              0x29
#define REG_SYNCVALUE3                              0x2A
#define REG_SYNCVALUE4                              0x2B
#define REG_SYNCVALUE5                              0x2C
#define REG_SYNCVALUE6                              0x2D
#define REG_SYNCVALUE7                              0x2E
#define REG_SYNCVALUE8                              0x2F
#define REG_PACKETCONFIG1                           0x30
#define REG_PACKETCONFIG2                           0x31
#define REG_PAYLOADLENGTH                           0x32
#define REG_NODEADRS                                0x33
#define REG_BROADCASTADRS                           0x34
#define REG_FIFOTHRESH                              0x35
// SM settings
#define REG_SEQCONFIG1                              0x36
#define REG_SEQCONFIG2                              0x37
#define REG_TIMERRESOL                              0x38
#define REG_TIMER1COEF                              0x39
#define REG_TIMER2COEF                              0x3A
// Service settings
#define REG_IMAGECAL                                0x3B
#define REG_TEMP                                    0x3C
#define REG_LOWBAT                                  0x3D
// Status
#define REG_IRQFLAGS1                               0x3E
#define REG_IRQFLAGS2                               0x3F
// I/O settings
#define REG_DIOMAPPING1                             0x40
#define REG_DIOMAPPING2                             0x41
// Version
#define REG_VERSION                                 0x42
// Additional settings
#define REG_PLLHOP                                  0x44
#define REG_TCXO                                    0x4B
#define REG_PADAC                                   0x4D
#define REG_FORMERTEMP                              0x5B
#define REG_BITRATEFRAC                             0x5D
#define REG_AGCREF                                  0x61
#define REG_AGCTHRESH1                              0x62
#define REG_AGCTHRESH2                              0x63
#define REG_AGCTHRESH3                              0x64

#define RF_FDEVMSB_FDEV_MASK                        0xC0
#define XTAL_FREQ                                   32000000
#define FREQ_STEP                                   61.03515625


void SX1276FskSetBitrate( uint32_t bitrate );

void SX1276FskSetBitrate( uint32_t bitrate )
{
    
    u8 high_low[2];    
    bitrate = ( uint16_t )( ( double )XTAL_FREQ / ( double )bitrate );
    high_low[0]    = ( uint8_t )( bitrate >> 8 );
    high_low[1]    = ( uint8_t )( bitrate & 0xFF );
    BurstWrite( REG_BITRATEMSB, high_low, 2 );    
}
void SX1276FskSetFdev( uint32_t fdev );

void SX1276FskSetFdev( uint32_t fdev )
{

    u8 high_low[2];
    high_low[0]=SPIRead(REG_FDEVMSB);
    fdev = ( uint16_t )( ( double )fdev / ( double )FREQ_STEP );
    high_low[0]    = ( ( high_low[0] & RF_FDEVMSB_FDEV_MASK ) | ( ( ( uint8_t )( fdev >> 8 ) ) & ~RF_FDEVMSB_FDEV_MASK ) );
    high_low[1]    = ( uint8_t )( fdev & 0xFF );
    BurstWrite( REG_FDEVMSB, high_low, 2 );    
}

u8 fsk_fre[3]={0x6C,0x80,0x00};
void fsk_config(void);
void fsk_config(void)
{
  //基本参数配置
    delay_us(20000); 
    SPIWrite(REG_OPMODE,0x08);    //sx1276_7_8_Sleep();                   //Change modem mode Must in Sleep mode 
	SPIWrite(REG_OPMODE,0x08);   //sx1276_7_8_Sleep();                    //Change modem mode Must in Sleep mode 

    

	delay_us(20000); 

    BurstWrite(LR_RegFrMsb,&fsk_fre[0],3);// 32M  434MHz//BurstWrite(LR_RegFrMsb,sx1276_7_8FreqTbl[Freq_Sel],3);  //setting frequency parameter 
	SX1276FskSetBitrate( 1200 );//BR=1.2Kbps//SPIWrite(RegBitRateMsb,sx1276_7_8FSKRateTbl[Fsk_Rate_Sel][0]);
	                            //SPIWrite(RegBitRateLsb,sx1276_7_8FSKRateTbl[Fsk_Rate_Sel][1]);         //setting rf rate parameter 
	
	SPIWrite(REG_PACONFIG,0xff); //SPIWrite(LR_RegPaConfig,sx1276_7_8PowerTbl[Power_Sel]);             //Setting output power parameter
	

	SX1276FskSetFdev( 35000 );//SPIWrite(RegFdevMsb,0x02);
	//SPIWrite(RegFdevMsb,0x3d);//Fdev 35k
	

	SPIWrite(REG_OCP,0x0b);//Close Ocp
	//SPIWrite(RegLna,0x23);//High & LNA Enable
	SPIWrite(REG_LNA,0x20);//High & LNA disable
	
	SPIWrite(REG_RXBW,0x12);//83KHz
	
	SPIWrite(REG_PREAMBLEDETECT,0xa0);//Enable 2Byte
	//SPIWrite(RegPreambleDetect,0x20);//disable
	
	SPIWrite(REG_PREAMBLEMSB,0x00);
	SPIWrite(REG_PREAMBLELSB,0x00);//0Byte Preamble
	
	SPIWrite(REG_PACKETCONFIG1,0x00);//fix packet Disable CRC，NRZ
	//SPIWrite(RegPacketConfig2,0x40);//Packet Mode
	
    SPIWrite(REG_OPMODE,0x09); //sx1276_7_8_Standby();
    
  
}
void fsk_test_tx(void)
{
    
    //开始发送
        uint8_t  TxTestFiFoData[57] = {
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
						0xff, 0xff, 
						0xff, 0xff, 0xff, 0xff, 
						0xff, 
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
						0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
						0xff, 0xff, 
						0xff, 0xff, 0xff, 0xff, 0xff
                        };
	

	fsk_config();
	SPIWrite(REG_PACKETCONFIG2,0x40);//Packet Mode
	
	SPIWrite(REG_DIOMAPPING1,0x00);
	SPIWrite(REG_DIOMAPPING2,0x00);//DIO0 Mapping for IRQ / DIO2 for RxData
	SPIWrite(REG_PADAC,0x87);//20dBm Tx 
    SPIWrite(REG_OPMODE,0x2b);//OOK /low frequency/TX
    
    /*
	SysTime = 0;
	while(1)
	{
		if((SX1276FskGetIrqFlags1()&0xA0)==0xA0)//Status OK?
			break;
		if(SysTime>=3)	
			return 0;                                              //over time for error
	}
	*/
    delay_us(3000); 

	SPIWrite(REG_PAYLOADLENGTH, 57);
	BurstWrite(REG_FIFO, TxTestFiFoData, 57);
        static u8 ir2;
        static u16 iii=0;
        ir2=SPIRead(0X3F);
        iii=0;
        while(1){
        iii++;
        ir2=SPIRead(0X3F);
        delay_us(1000);
        if(iii==1000)
        {
          break;
        }
        if(ir2&(1<<6))
        {
          break;
        }
        }
        delay_us(30000); 

}

void fsk_test_rx(void)
{
  fsk_config();
	SPIWrite(REG_PACKETCONFIG2,0x00);//contuine Mode
	
    SPIWrite(REG_PACONFIG,0x0f);//RFIO Pin
	SPIWrite(REG_DIOMAPPING1,0x0c);
	SPIWrite(REG_DIOMAPPING2,0x00);//DIO0 Mapping for IRQ / DIO2 for RxData
	SPIWrite(REG_PADAC,0x84);//Normal and Rx
    SPIWrite(REG_OPMODE,0x0d);   
    delay_us(6000);
    for(;;);
}