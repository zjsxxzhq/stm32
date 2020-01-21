#include "stm8l15x.h"
#include "stdio.h"
#include "string.h"
#include "sx1276_7_8.h"
#include "spi.h"
#include "ds18b20.h"  
#include "define.h"
#include "SI7021.h"
#include "HX711.h"


u8 ioio;
void hx711_init(void)
{
  GPIO_Init(HX711_SCK_GPIO, HX711_SCK_PIN, GPIO_Mode_Out_PP_Low_Slow);  
  GPIO_Init(HX711_DATA_GPIO, HX711_DATA_PIN, GPIO_Mode_In_PU_No_IT);
}
void weightdelay(void);
void weightdelay(void)
{
#if(0)
  u16 i=10;
  while(i--);
#endif
}
u8 weight_aderror;
//重量传感器
//****************************************************
//??HX711
//****************************************************
unsigned long HX711_Read(void)	//??128
{
  __IO unsigned long count; 
  unsigned char i; 
  u32 delaycount=0;
   

  SET_B1
  weightdelay();
  RESET_SCK1
  weightdelay();	
  count=0;
  while(GPIO_ReadInputDataBit(HX711_DATA_GPIO,HX711_DATA_PIN))
  {
    delaycount++;
    if(delaycount>10000)
    {
      weight_aderror++;
      return 0;
    }
  }
  disableInterrupts();
  for(i=0;i<24;i++)
  { 
	 //HX711_SCK=1; 
    SET_SCK1
    weightdelay();
		
    count=count<<1; 
    RESET_SCK1
    weightdelay();
    if(GPIO_ReadInputDataBit(HX711_DATA_GPIO,HX711_DATA_PIN))
    count++; 
  } 
  enableInterrupts();
  SET_SCK1	
	
  count=count^0x800000;//?25????????,????
  weightdelay();
  RESET_SCK1
  weightdelay();
  return(count);
}