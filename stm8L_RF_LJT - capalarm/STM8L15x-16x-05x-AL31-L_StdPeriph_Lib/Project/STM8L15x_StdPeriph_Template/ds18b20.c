#include "stm8l15x.h"
#include "ds18b20.h"

s16 ds18b20_temp[1];
unsigned char ds18b20_error_flag[1];
unsigned char sign[1];
unsigned char interger[1];
unsigned int decimal[1];
u8 ds18b20_sel=0;//0第一路,1第二路，2第三路
__IO u8 ustime[2];
__IO u16 ustime1;

void delay_us(u16 time);
void delay_us(u16 time)
{

	//time=time*8;
        TIM2->CNTRH = 0;
        TIM2->CNTRL = 0;
        ustime1=0;
	while(ustime1<time)
        {
          ustime[0]=TIM2->CNTRH;
          ustime[1]=TIM2->CNTRL;
          ustime1=((u16)ustime[0]<<8)+ustime[1];
        }

}
/*
优化后的1us~200us
*/
void delay_us_(u16 time)
{
  TIM2->CNTRL = 0;
  while(TIM2->CNTRL<time);
}


void Tx_ResetPulse_0(void);
char Rx_PresencePulse_0(void);
char DS18B20_Init_0(void);
void GPIO_DQ_Out_Mode_0(void);
void GPIO_DQ_Input_Mode_0(void);
void Write_OneByte_ToDS18b20_0(unsigned char data);
unsigned char Read_OneByte_FromDS18b20_0(void);


void DS18B20_GPIO_Config(void)
{
  DQ1_GPIO_Port->ODR |= DQ1_Pin;
  DQ1_GPIO_Port->DDR |= DQ1_Pin;
  DQ1_GPIO_Port->CR1 &=~DQ1_Pin;
  DQ1_GPIO_Port->CR2 &=~DQ1_Pin;
}

char DS18B20_Init_0(void)
{
  Tx_ResetPulse_0();
  return (Rx_PresencePulse_0());
}
 
void GPIO_DQ_Out_Mode_0(void)
{
  DQ1_GPIO_Port->ODR |= DQ1_Pin;
  DQ1_GPIO_Port->DDR |= DQ1_Pin;
  //DQ1_GPIO_Port->CR1 &=~DQ1_Pin;
  //DQ1_GPIO_Port->CR2 |=DQ1_Pin;
  //GPIO_Init(DQ1_GPIO_Port, DQ1_Pin, GPIO_Mode_Out_OD_HiZ_Fast);
}



void GPIO_DQ_Input_Mode_0(void)
{
  DQ1_GPIO_Port->DDR &= (uint8_t)(~(DQ1_Pin));
  //DQ1_GPIO_Port->CR1 |=DQ1_Pin;
  //DQ1_GPIO_Port->CR2 &=~DQ1_Pin;
  //GPIO_Init(DQ1_GPIO_Port, DQ1_Pin, GPIO_Mode_In_PU_No_IT);
}



void Tx_ResetPulse_0(void)
{
  GPIO_DQ_Out_Mode_0();
  DQ0_Write_0();  
  delay_us(500);
  DQ0_Write_1();
  delay_us_(1); 
}

char Rx_PresencePulse_0(void)
{
  u16 i=0;
  GPIO_DQ_Input_Mode_0();

  while(DQ0_ReadBit())
  {
    i++;//等待DS18B20应答
    delay_us_(1);

    if(i==2000){
      GPIO_DQ_Out_Mode_0();
      return 0;
    }
  }
  i=0;
  while(!DQ0_ReadBit())
  {
    //DS18B20将总线拉低60~240us,然后总线由上拉电阻拉高    
    i++;//等待DS18B20应答
    delay_us_(1);

    if(i==2000){
      GPIO_DQ_Out_Mode_0();
      return 0;
    }
  } 

  delay_us(300);
  GPIO_DQ_Out_Mode_0();//接受完成,主机重新控制总线
  return 1;
}

void Write_OneByte_ToDS18b20_0(unsigned char data)
{
  unsigned char i;
  GPIO_DQ_Out_Mode_0();
  for(i=0;i<8;i++)
  {
    if(data&0x01)
    { //write 1
      DQ0_Write_0(); 
      delay_us_(8);                           
      DQ0_Write_1();  
      delay_us_(80);				
    }
    else
    {
      DQ0_Write_0(); 
      delay_us_(110);                           
      DQ0_Write_1();  
      delay_us_(5);      
    }
    data>>=1;				
  }	
}

unsigned char Read_OneByte_FromDS18b20_0(void)
{
  unsigned char i,data=0;
  for(i=0;i<8;i++)
  {
    GPIO_DQ_Out_Mode_0();
    data>>=1;
    DQ0_Write_0();
    //delay_us(2);
    GPIO_DQ_Input_Mode_0();
    //delay_us(1);
    if(DQ0_ReadBit())
    {
      data|=0x80;
    }
    delay_us(70);
  }
  GPIO_DQ_Out_Mode_0();
  return data;	
}

void Read_Temperature(void)
{
	unsigned char a=0;
	unsigned char b=0;
	unsigned int tmp;
        //HAL_GPIO_WritePin(VCC1_GPIO_Port, VCC1_Pin, GPIO_PIN_SET);//打开18B20供电
        SystickCount=1;
        while(SystickCount);
        ds18b20_error_flag[0]=0;
        
        
//        while(1)DS18B20_Init_0();
        disableInterrupts();
        //第1路
        ds18b20_sel=0;
        if(DS18B20_Init_0()==1)
        {
          Write_OneByte_ToDS18b20_0(ROM_Read_Cmd);
          if(DS18B20_Init_0()==1)
          {
            Write_OneByte_ToDS18b20_0(ROM_Skip_Cmd);
            Write_OneByte_ToDS18b20_0(Convert_T);
          }
          else
          {
            Tx_ResetPulse_0();
            ds18b20_error_flag[0]=1;
          }
        }
        else
        {
          Tx_ResetPulse_0();
          ds18b20_error_flag[0]=1;
        }
        enableInterrupts();
        if(ds18b20_error_flag[0]==0)
        {
          SystickCount=750;
          while(SystickCount);
          disableInterrupts();
          //读取第1路
          if(ds18b20_error_flag[0]==0)
          {
            ds18b20_sel=0;
            if(DS18B20_Init_0()==1)
            {
              Write_OneByte_ToDS18b20_0(ROM_Skip_Cmd);
              Write_OneByte_ToDS18b20_0(Read_Scratchpad);
              a=Read_OneByte_FromDS18b20_0();
              b=Read_OneByte_FromDS18b20_0();
              Tx_ResetPulse_0();
          
              tmp=(b<<8)|a;
              if(b&0xF0)
              {
                sign[0]=1;
                tmp=~tmp+1;
              }
              else
              {
                sign[0]=0;
              }
              interger[0]=(tmp>>4&0x00FF);
              decimal[0]=(tmp&0x000F)*625; 
              ds18b20_temp[0]=interger[0]+decimal[0]/1000;
              if(sign[0]==1)
              {
                ds18b20_temp[0]=-ds18b20_temp[0];
              }
            }
            else
            {
              Tx_ResetPulse_0();
              ds18b20_error_flag[0]=1;
            }
          }
        }
      enableInterrupts();
      //HAL_GPIO_WritePin(VCC1_GPIO_Port, VCC1_Pin, GPIO_PIN_RESET);//关闭18B20供电	
}




