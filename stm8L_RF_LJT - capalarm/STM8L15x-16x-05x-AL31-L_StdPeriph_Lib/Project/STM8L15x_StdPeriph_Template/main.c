/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/main.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "sx1276_7_8.h"
#include "spi.h"
#include "ds18b20.h"  
#include "define.h"
#include "SI7021.h"
#include "HX711.h" 



/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

u16 ADCdata;
u8 UartRxBuf[255];
u8 UartRxLen=0;
u8 UartRxCount=0;
u8 UartRxCountLast=0;
u8 UartTxBuf[255];
u8 UartTxCount=0;
u8 UartTxLen;
u8 FlagUartReceive=0;
u8 FlagUartSending=0;
__IO u32 SystickCount=0;
__IO u32 SystickCount1=0;
__IO u32 SystickCount2=0;
__IO u32 ResetCount=0;
u8*	uarttx_p=NULL;
__IO u16 uarttxlen=0;
Config_Typedef  EE_Para;
u8 keycount=0;
Device_Typedef  device_info;
s32 weight;
s32 weighterror;
s32 weighttemp;
s32 weight_ad;
s32 weighttempbuf[3];
u8 batvolt;
s32 maopi;
//u16 weightxishu=8440;
u32 uartrxdataallcount;
u32 uartrxdataerrorcount;
u32 uartrxactivecount=0;
u8 flagmaopi=0;
u8 flagclearljt=0;
u8 sumcheck=0;
u32 rfrxcountall=0;
u32 rfrxcountok=0;
u32 errlen;
u8 showstr[100];
u16 keylongpresscount=0;
u8 keylongpressvalue;
const u32 config_RF_table[][3]={//425-500M
 //频率
  //扩频因子,7`10
  //带宽//0:7.8KHz,1:10.4KHz,2:15.6KHz,3:20.8KHz,4:31.2KHz,5:41.7KHz,6:62.5KHz,7:125KHz,8:250KHz,9:500KHz
//{408000000,7,9},//0-15
//{412000000,7,9},
//{416000000,7,9},
//{420000000,7,9},
//{424000000,7,9},


 //16
{425000000,8,9},
{429000000,8,9},
{433000000,8,9},
{437000000,8,9},
{441000000,8,9},
{445000000,8,9},
{449000000,8,9},
{453000000,8,9},
{457000000,8,9},
{461000000,8,9},
{465000000,8,9},
{469000000,8,9},
{473000000,8,9},
{477000000,8,9},
{481000000,8,9},
{485000000,8,9},
{489000000,8,9},


 //32-47
{425000000,9,9},
{429000000,9,9},
{433000000,9,9},
{437000000,9,9},
{441000000,9,9},
{445000000,9,9},
{449000000,9,9},
{453000000,9,9},
{457000000,9,9},
{461000000,9,9},
{465000000,9,9},
{469000000,9,9},
{473000000,9,9},
{477000000,9,9},
{481000000,9,9},
{485000000,9,9},
{489000000,9,9},
//48-63
{425000000,10,9},
{429000000,10,9},
{433000000,10,9},
{437000000,10,9},
{441000000,10,9},
{445000000,10,9},
{449000000,10,9},
{453000000,10,9},
{457000000,10,9},
{461000000,10,9},
{465000000,10,9},
{469000000,10,9},
{473000000,10,9},
{477000000,10,9},
{481000000,10,9},
{485000000,10,9},
{489000000,10,9},

{425000000,7,9},
{429000000,7,9},
{433000000,7,9},
{437000000,7,9},
{441000000,7,9},
{445000000,7,9},
{449000000,7,9},
{453000000,7,9},
{457000000,7,9},
{461000000,7,9},
{465000000,7,9},
{469000000,7,9},
{473000000,7,9},
{477000000,7,9},
{481000000,7,9},
{485000000,7,9},
{489000000,7,9},
//64-79

//80-95
{425000000,8,8},
{429000000,8,8},
{433000000,8,8},
{437000000,8,8},
{441000000,8,8},
{445000000,8,8},
{449000000,8,8},
{453000000,8,8},
{457000000,8,8},
{461000000,8,8},
{465000000,8,8},
{469000000,8,8},
{473000000,8,8},
{477000000,8,8},
{481000000,8,8},
{485000000,8,8},
{489000000,8,8},
//96-111
{425000000,9,8},
{429000000,9,8},
{433000000,9,8},
{437000000,9,8},
{441000000,9,8},
{445000000,9,8},
{449000000,9,8},
{453000000,9,8},
{457000000,9,8},
{461000000,9,8},
{465000000,9,8},
{469000000,9,8},
{473000000,9,8},
{477000000,9,8},
{481000000,9,8},
{485000000,9,8},
{489000000,9,8},
//112-127
{425000000,10,8},
{429000000,10,8},
{433000000,10,8},
{437000000,10,8},
{441000000,10,8},
{445000000,10,8},
{449000000,10,8},
{453000000,10,8},
{457000000,10,8},
{461000000,10,8},
{465000000,10,8},
{469000000,10,8},
{473000000,10,8},
{477000000,10,8},
{481000000,10,8},
{485000000,10,8},
{489000000,10,8},

{425000000,7,8},
{429000000,7,8},
{433000000,7,8},
{437000000,7,8},
{441000000,7,8},
{445000000,7,8},
{449000000,7,8},
{453000000,7,8},
{457000000,7,8},
{461000000,7,8},
{465000000,7,8},
{469000000,7,8},
{473000000,7,8},
{477000000,7,8},
{481000000,7,8},
{485000000,7,8},
{489000000,7,8},
};

int str2int(const char *str)
{
        int temp = 0;
        const char *ptr = str;  //ptr保存str字符串开头
  
        if (*str == '-' || *str == '+')  //如果第一个字符是正负号，
       {                      //则移到下一个字符
           str++;
       }
       while(*str != 0)
       {
           if ((*str < '0') || (*str > '9'))  //如果当前字符不是数字
           {                       //则退出循环
               break;
           }
           temp = temp * 10 + (*str - '0'); //如果当前字符是数字则计算数值
           str++;      //移到下一个字符
       }  
       if (*ptr == '-')     //如果字符串是以“-”开头，则转换成其相反数
       {
           temp = -temp;
       }
 
       return temp;
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART_printf()调用
 */
//static 
char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */
u8 Sum(u8 buf[],u8 len)
{
  u8 ccs=0;
  while(len--)ccs+=buf[len];
  return ccs;
}
__IO u8 ustime[2];
__IO u16 ustime1;
void delay_us(u16 time)
{
  u8 x,y;
  //time=time*8;
  TIM2->CNTRH = 0;
  TIM2->CNTRL = 0;
  ustime1=0;
  while(ustime1<time)
  {
    ustime[0]=TIM2->CNTRH;
    ustime[1]=TIM2->CNTRL;
    x=ustime[0];
    y=ustime[1];
    ustime1=((u16)x<<8)+y;
  }
}




void lowpowerIO_init(void)
{ 
  //不用的口需要配置输出
  GPIO_Mode_TypeDef GPIO_Mode=GPIO_Mode_Out_PP_High_Slow;
  GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_OD_HiZ_Slow);//AD口
  GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_OD_HiZ_Slow);//AD口
  GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_OD_HiZ_Slow);//AD口
  
  GPIO_Init(GPIOB, GPIO_Pin_0, GPIO_Mode);
  GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode);
  GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode);
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode);
  GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode);
  GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode);
  
  GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode);
  GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode);
  
  GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode);
  //用到的IO口  
  GPIO_Mode=GPIO_Mode_Out_PP_Low_Slow;
  GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode);
  GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode);
  GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode); 
  GPIO_Init(GPIOC, GPIO_Pin_5, GPIO_Mode);
  GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode);
  GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode); //LED
  
  ADC_BAT_PWR_OFF//电池检测电源关闭
  GY53_RX_OFF//测距传感器接收关闭
  ADC_TEMP_PWR_OFF//温度传感器电源关闭
  CAP_PWR_OFF//测距传感器电源关闭
  NBIOT_PWR_OFF//nbiot模组电源关闭
  NBIOT_PWRKEY_OFF//nbiot启动键关闭
}
void lowpowerIO_init(void);

s8 At_Send(u8 atcmd[],u16 sendlen,u8 findvalue[],u16 overtimes);
s16 Find_Array(u8 array[],u16 array_len,u8 find_array[],u16 find_array_len);

s16 Find_Array(u8 array[],u16 array_len,u8 find_array[],u16 find_array_len)
{
  s16 i,j;
	if(array_len<find_array_len)
	{
		return -1;
	}
  for(i=0;i<(array_len-find_array_len+1);i++)
  {
    if(array[i]==find_array[0])
    {
      for(j=1;j<find_array_len;j++)
      {
        if(array[i+j]==find_array[j])
        {
          continue;
        }
        else
        {
          break;
        }
      }
      if(j==find_array_len)
      {
        return i;
      }
    }
  }
  return -1;
}
s8 At_Send(u8 atcmd[],u16 sendlen,u8 findvalue[],u16 overtimes)
{
  u8 findlen;
  s16 pos;
  findlen=strlen(findvalue);
  if(sendlen!=0)
  {
    UART_IT_Send(atcmd,sendlen);
  }
  else
  {
    UART_IT_Send(atcmd,strlen(atcmd));
  }
  SystickCount=overtimes;
  while(SystickCount)
  {
    if(FlagUartReceive==1)
    {
      if((UartRxCount>findlen))
      {
        pos=Find_Array(UartRxBuf,UartRxCount,findvalue,findlen);
        if(pos!=-1)
        {
          UartRxCount=0;
          FlagUartReceive=0;
          return 0;
        }
        else
        {
          UartRxCount=0;
          FlagUartReceive=0;
          return -1;
        }
        UartRxCount=0;
        FlagUartReceive=0;
      }
      UartRxCount=0;
      FlagUartReceive=0;
    }
  }
  return -1;
}








void delay(u32 ms)
{
  SystickCount=ms;
  while(SystickCount);   
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void USART_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
   
  //SYSCFG_REMAPDeInit();
  //SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_3, ENABLE);
  GPIO_ExternalPullUpConfig(GPIOC, GPIO_Pin_2, ENABLE);
  GPIO_Init(GPIOC, GPIO_Pin_3, GPIO_Mode_Out_PP_High_Fast);//TX  
  GPIO_Init(GPIOC, GPIO_Pin_2, GPIO_Mode_In_PU_No_IT); //RX
  USART_DeInit(USART1);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
  USART_ClearFlag(USART1, USART_FLAG_RXNE);
#if(USE_UART_IT_SEND ==1) 
//  USART_ITConfig(USART1, USART_IT_TC, ENABLE);
//  USART_ClearFlag(USART1, USART_FLAG_TC);
  USART_ClearFlag(USART1, USART_FLAG_TXE);
#endif
  USART_Init(USART1, 115200, USART_WordLength_8b, USART_StopBits_1,USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
  USART_Cmd(USART1, ENABLE);
  ITC_SetSoftwarePriority(USART1_RX_IRQn, ITC_PriorityLevel_3);//最高
  
}

void TIM4_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
  TIM4_TimeBaseInit(TIM4_Prescaler_64, 249);
  TIM4_ClearFlag(TIM4_FLAG_Update);

  TIM4_ITConfig(TIM4_IT_Update, ENABLE);

//  enableInterrupts();


  TIM4_Cmd(ENABLE);
}
void TIM2_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  if(CLKHZ==4)
  TIM2_TimeBaseInit(TIM2_Prescaler_4, TIM2_CounterMode_Up,65535);
  else if(CLKHZ==8)
  TIM2_TimeBaseInit(TIM2_Prescaler_8, TIM2_CounterMode_Up,65535); 
  TIM2_Cmd(ENABLE);
}

void RTC_Config(void)
{

  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);

  while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);
  
//  SystickCount=100;
//  while(SystickCount);
  
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);


  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);


  RTC_ITConfig(RTC_IT_WUT, ENABLE);

  
}



void UART_IT_Send(u8* buffer,u16 len)
{

#if(USE_UART_IT_SEND ==1) 
//  uarttx_p=buffer;
//  uarttxlen=len;
//  uarttxlen--;
//  USART1->DR = *uarttx_p++;
//  while(uarttxlen)
//  {
//  }
  while(uarttxlen)
  {
  }
  uarttx_p=buffer;
  uarttxlen=len;
  USART_ClearFlag(USART1, USART_FLAG_TXE);
  USART_ITConfig(USART1, USART_IT_TXE, ENABLE);

#else
  while(len--){
  USART1->DR =* buffer++;
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {
  }
  }
#endif

}

void CLK_Config(void)
{
  /* Select HSE as system clock source */
  CLK_SYSCLKSourceSwitchCmd(ENABLE);
  CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSE);
  /* system clock prescaler: 1*/
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  while (CLK_GetSYSCLKSource() != CLK_SYSCLKSource_HSE)
  {}
}











void key_init(void)
{
  disableInterrupts();
  //脚踩按钮
  GPIO_Init(KEY_DATA_PORT,KEY_DATA_PIN,GPIO_Mode_In_PU_IT);  
  EXTI_SetPinSensitivity(EXTI_Pin_1, EXTI_Trigger_Falling);
  ITC_SetSoftwarePriority(EXTI1_IRQn, ITC_PriorityLevel_1);
  //去皮按钮
  GPIO_Init(KEY_CLEAR_PORT,KEY_CLEAR_PIN,GPIO_Mode_In_PU_IT);  
  EXTI_SetPinSensitivity(EXTI_Pin_0, EXTI_Trigger_Falling_Low);
  ITC_SetSoftwarePriority(EXTI0_IRQn, ITC_PriorityLevel_1);
  enableInterrupts();
}


void read_deviceinfo(void)
{
#if(1)
  if(*(u8*)0x1100=='O'&&*(u8*)0x1101=='K')
  {
    device_info=*(Device_Typedef*)0x1102;//从配置文件里读取
  }
  else
  {
    device_info.device_type=ljt;//1表示控制器,0表示垃圾桶
    device_info.config_channel=16;//(0-15 16-31 32-47 48-63 64-71 72-79)
    device_info.ljt_addr=1;//垃圾桶地址
    device_info.laji_type=ganran;//垃圾类型
    device_info.controller_addr=1;//控制器地址
    device_info.ljt_update_period=10;//上传周期
    device_info.weightzerovalue=0;
    device_info.weightxishu=8500;//校准系数
  }
  
#else
    device_info.device_type=0;//1表示控制器,0表示垃圾桶
    device_info.config_channel=16;//(0-15 16-31 32-47 48-63 64-71 72-79)
    device_info.ljt_addr=1;//垃圾桶地址
    device_info.laji_type=0;//垃圾类型
    device_info.controller_addr=1;//控制器地址
    device_info.ljt_update_period=10;//上传周期
    device_info.weightzerovalue=0;
    device_info.weightxishu=8500;//校准系数 
    save_para();
#endif
}
const u8 rfaddr[4]={33,99,50,80};
void get_rf_para(void)
{
  u8 addr;
  LoRaSetRFFrequency( config_RF_table[device_info.config_channel][0],EE_Para.rfmhz);
  EE_Para.sf=config_RF_table[device_info.config_channel][1];//扩频因子--扩频因子设置到9
  EE_Para.bw=config_RF_table[device_info.config_channel][2];//125KHZ
   
  EE_Para.cr=1;//CR4_5
  EE_Para.lowspeed=1;//低速率优化开启
  EE_Para.pw=3;//发送功率
  EE_Para.pp=12;//前导码12
  addr=device_info.config_channel/127;
  addr=addr%4;
  EE_Para.rfaddr=rfaddr[addr];//模块地址33,99,50,80
}



void save_para(void)
{
  u8 i;
  u16 ii=255;
  u8 *p=(u8*)&device_info;
  FLASH_Unlock(FLASH_MemType_Data);
  FLASH_ProgramByte(0x1100, 'O');
  FLASH_ProgramByte(0x1101, 'K');
  for(i=0;i<sizeof(Device_Typedef);i++)
  {
    FLASH_ProgramByte(0x1102+i, *p++);
    ii=1000;while(ii--);
  }
  FLASH_Lock(FLASH_MemType_Data);   
}




/*--------------------冒泡排序---------------------*/
void bubleSort(long  data[], u8 n) {
    u8 i,j;
    long temp;
    //两个for循环，每次取出一个元素跟数组的其他元素比较
    //将最大的元素排到最后。
    for(j=0;j<n-1;j++) {
        //外循环一次，就排好一个数，并放在后面，
        //所以比较前面n-j-1个元素即可
        for(i=0;i<n-j-1;i++) {
            if(data[i]>data[i+1]) {
                temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
            }
        }
    }  
}

u8 weight_adcount=0;

s32 weight_max=88888888;
s32 weight_min=88888888;
void read_weight(enum device_LP mode)
{
#if(0)
  u8 i;
  for(i=0;i<3;i++)
  {
    //disableInterrupts();
    do{
    weighttempbuf[i]=HX711_Read();
    }while(weighttempbuf[i]==0);
    //enableInterrupts();
    SystickCount=50;
    while(SystickCount); 
  }
  bubleSort(weighttempbuf, 3);
  weight_ad=weighttempbuf[1];  
#endif
  u8 count=5;
  do
  {
    weight_adcount=0;
    do{count--;weight_ad=HX711_Read();weight_adcount++;}while((weight_ad==0)&&count);
    weighttemp=((weight_ad-device_info.weightzerovalue)*100)/device_info.weightxishu;
    if((weighttemp<80000)&&(weighttemp>-80000))
    {
      weight=weighttemp;
      if(weight_max==88888888)
      {
        weight_max=weight;
      }
      if(weight_min==88888888)
      {
        weight_min=weight;
      }
      if(weight>weight_max)
      {
        weight_max=weight;
      }
      if(weight<weight_min)
      {
        weight_min=weight;
      }      
      break;
    }
    else
    {
      weighterror=weighttemp;
      break;
    }
  }while(1);
  

  if(mode==lp_mode)
  {
   SET_SCK1
  }
}

void clear_weight(enum device_LP mode)
{

  do
  {
    weight_ad=HX711_Read();
  }while(weight_ad==0);
  device_info.weightzerovalue=weight_ad;
  if(mode==lp_mode)
  {
   SET_SCK1
  }
}


void hextostr(char hex[],u16 hexlen,char str[]);
void hextostr(char hex[],u16 hexlen,char str[])
{
  u16 i;
  u8 temp;
  for(i=0;i<hexlen;i++)
  {
    temp=hex[i]>>4;
    if(temp<10)
    {
      str[i*2]=temp+'0';
    }
    else
    {
      str[i*2]=temp+'A'-10;
    }
    temp=hex[i]&0x0f;
    if(temp<10)
    {
      str[i*2+1]=temp+'0';
    }
    else
    {
      str[i*2+1]=temp+'A'-10;
    }
  }
}
u32 GetATValueNumber(char *srcstr,char *str);
u32 GetATValueNumber(char *srcstr,char *str)	
{	
	while(*srcstr!=*str)//偏移到参数开始的地方
	{
		srcstr++;	
		if(*srcstr=='\0'||*srcstr=='\r'||*srcstr=='\n'||*srcstr==0)
			return 0;//遇到结束符了
	}
	srcstr++;
	//return atoi(srcstr);	
	return strtol(srcstr,NULL,10);
}
u8 Read_CSQ(u8* csq);
u8 Read_CSQ(u8* csq)
{
  u8 res;
  u8 *p;
  //+CSQ: 19,99
  res=At_Send("AT+CSQ\r\n",0,"OK\r\n",200);
  if(res!=0)
  {
    *csq=99;
    return res;
  }
  p=strstr(UartRxBuf,"+CSQ: ");
  *csq=GetATValueNumber(p,":");
  return res;
}
void Net_Send(u8 data[],u16 datalen);
s16 netresult;
u8 strbuf[256];
u8 send_ok_string[100];
u8 CSQ;
u8 netstep;
void Net_Send(u8 data[],u16 datalen)
{
  u16 len;
  u16 count;
  netresult=At_Send("ATE0\r\n",0,"OK\r\n",200);
  netresult=At_Send("ATE0\r\n",0,"OK\r\n",200);
  netresult=At_Send("ATE0\r\n",0,"OK\r\n",200);
  if(netresult!=0)
  {
    netstep=0;
    return;
  }
  netresult=At_Send("AT+CPIN?\r\n",0,"READY",200);
  if(netresult!=0)
  {
    netstep=1;
    return;
  }
  netresult=At_Send("AT+CSQ\r\n",0,"OK\r\n",200);
  if(netresult!=0)
  {
    netstep=2;
    return;
  }
  Read_CSQ(&CSQ);
  count=0;
  while(1)
  {
    count++;
    netresult=At_Send("AT+CGATT?\r\n",0,"+CGATT: 1",200);
    if(netresult==0)
    {
      break;
    }
    if(count>100)
    {
      netstep=3;
      return;//网络搜索不到
    }
  }
  //创建1路TCP 1-ipv4/2-ipv6,1-tcp,2-udp,1-IP
  netresult=At_Send("AT+CSOC=1,1,1\r\n",0,"\r\nOK\r\n",500);
  if(netresult!=0)
  {
    netstep=4;
    return;
  }
  //使能TCP回执
//  netresult=At_Send("AT+CSOSENDFLAG=1\r\n",0,"\r\nOK\r\n",500);

	
  strcpy(strbuf, "AT+CSOCON=0,");
  strcat(strbuf,"7777");
  strcat(strbuf,",\"");
  strcat(strbuf,"101.200.37.232");
  strcat(strbuf,"\"\r\n");
  netresult=At_Send(strbuf,0,"OK",60000);
  if(netresult!=0)
  {
    netstep=6;
    return;
  }
  //发送数据
  if(datalen<10)
  {
    sprintf(send_ok_string, "SEND: 0,%1d", datalen);
  }
  else if(datalen<100)
  {
    sprintf(send_ok_string, "SEND: 0,%2d", datalen);
  }
  else if(datalen<1000)
  {
    sprintf(send_ok_string, "SEND: 0,%3d", datalen);
  }
  
  if((datalen*2)<10)
  {
    sprintf(strbuf, "AT+CSOSEND=0,%1d,", (datalen*2));		
  }
  else if((datalen*2)<100)
  {
    sprintf(strbuf, "AT+CSOSEND=0,%2d,", (datalen*2));
  }
  else if((datalen*2)<1000)
  {
    sprintf(strbuf, "AT+CSOSEND=0,%3d,", (datalen*2));	
  }
  strcat(strbuf,"\"");
  len=strlen(strbuf);
//	hextostr(data,datalen,datahexstrbuf);
//	datahexstrbuf[datalen*2]=0;
//	strcat(strbuf,datahexstrbuf);
  hextostr(data,datalen,&strbuf[len]);
  strbuf[len+datalen*2]=0;	
  strcat(strbuf,"\"");
  strcat(strbuf,"\r\n");
  netresult=At_Send(strbuf,0,send_ok_string,60000);//返回字节长度就表示正常
  if(netresult!=0)
  {
    netstep=7;
    return;
  }		  
}

void Open_Power(void);
void Open_Power(void)
{
  NBIOT_PWR_ON//打开电源
  delay(100);
  NBIOT_PWRKEY_ON
  //开机过程中可以进入休眠
  
//  delay(9000);
//  NBIOT_PWRKEY_OFF
}
void Close_Power(void);
void Close_Power(void)
{

  NBIOT_PWRKEY_OFF  
  NBIOT_PWR_OFF//关闭电源
}
u8 netsenddatapacket[51];
u8 latitude[11];
u8 logitude[12];
u8 macaddr[6];
void getuploaddata(void);
u8 read_macaddr(void);
u16 CRC16(u8* pchar, u8 charlen);
#define CRC_16_POLYNOMIALS  0xA001
//CRC16??
u16 CRC16(u8* pchar, u8 charlen)
{
  u16 crc16=0xffff;
  u8 i;
  while(charlen--)
  {
    
    crc16=crc16^((u16)*pchar);
    for(i=0;i<8;i++)
    {
      if(crc16&0x0001)
      {
        crc16=crc16>>1;
        crc16=crc16^CRC_16_POLYNOMIALS;
      }
      else
      {
        crc16=crc16>>1;
      }      
    }
    pchar++;
  }
  crc16=(crc16>>8)+(crc16<<8);
  return crc16;
}
u8 read_macaddr(void)
{  


  u8 ge,shi,bai,qian,wan;
  u16 crc1,crc2;
  u32 MCUID[3];
  macaddr[0]=0;
  macaddr[1]=0;
  macaddr[2]=0;
  macaddr[3]=0;
  macaddr[4]=0;
  macaddr[5]=0;
  MCUID[0]=*(__IO u32*)(0x4926);
  MCUID[1]=*(__IO u32*)(0x492A);
  MCUID[2]=*(__IO u32*)(0x492E);
  MCUID[0]=MCUID[1]+MCUID[2];
  MCUID[1]=MCUID[0]+MCUID[2];
  crc1=CRC16((u8*) &MCUID[0], 4);
  crc2=CRC16((u8*) &MCUID[1], 4);
  ge=crc1%10;
  shi=(crc1/10)%10;
  bai=(crc1/100)%10;
  qian=(crc1/1000)%10;
  wan=(crc1/10000)%10;
  macaddr[0]=ge;
  macaddr[0]=macaddr[0]|(shi<<4);
  macaddr[1]=bai;
  macaddr[1]=macaddr[1]|(qian<<4);
  macaddr[2]=wan+0x60;
  ge=crc2%10;
  shi=(crc2/10)%10;
  bai=(crc2/100)%10;
  qian=(crc2/1000)%10;
  wan=(crc2/10000)%10;
  macaddr[3]=ge;
  macaddr[3]=macaddr[3]|(shi<<4);
  macaddr[4]=bai;
  macaddr[4]=macaddr[4]|(qian<<4);
  macaddr[5]=wan+0x80; 
	return 0;
}
void getuploaddata(void)
{

	u8 i,ccs=0;
	u16 code=0;
//	memset(netsenddatapacket,0,sizeof(netsenddatapacket));
	netsenddatapacket[0]=0xAA;
	netsenddatapacket[1]=0x55;
	netsenddatapacket[2]=0xB2;//老一代rs款是B1,新一代是B2,低成本一代是B3
	netsenddatapacket[3]=0x03;
	netsenddatapacket[4]=macaddr[0];
	netsenddatapacket[5]=macaddr[1];
	netsenddatapacket[6]=macaddr[2];
	netsenddatapacket[7]=macaddr[3];
	netsenddatapacket[8]=macaddr[4];
	netsenddatapacket[9]=macaddr[5];
	netsenddatapacket[10]=CSQ;


	netsenddatapacket[11]=latitude[0];
	netsenddatapacket[12]=latitude[1];
	netsenddatapacket[13]=latitude[2];
	netsenddatapacket[14]=latitude[3];
	netsenddatapacket[15]=latitude[4];
	netsenddatapacket[16]=latitude[5];
	netsenddatapacket[17]=latitude[6];
	netsenddatapacket[18]=latitude[7];
	netsenddatapacket[19]=latitude[8];
	netsenddatapacket[20]=latitude[9];
	netsenddatapacket[21]=latitude[10];	
	
	netsenddatapacket[22]=logitude[0];
	netsenddatapacket[23]=logitude[1];
	netsenddatapacket[24]=logitude[2];
	netsenddatapacket[25]=logitude[3];
	netsenddatapacket[26]=logitude[4];
	netsenddatapacket[27]=logitude[5];
	netsenddatapacket[28]=logitude[6];
	netsenddatapacket[29]=logitude[7];
	netsenddatapacket[30]=logitude[8];
	netsenddatapacket[31]=logitude[9];
	netsenddatapacket[32]=logitude[10];
	netsenddatapacket[33]=logitude[11];	
	
	

	netsenddatapacket[34]=0;//卫星数量
	netsenddatapacket[35]=batvolt;//电池电压
	netsenddatapacket[36]=1;//充电状态
	netsenddatapacket[37]=0;//1表示开,0表示闭合
	netsenddatapacket[38]=0;//开门次数高
	netsenddatapacket[39]=0;//开门次数低
	netsenddatapacket[40]=0;
	

	netsenddatapacket[41]=66;//垃圾实时容量
	
	netsenddatapacket[42]=0;//垃圾清理次数
	netsenddatapacket[43]=0;

	netsenddatapacket[44]=code>>8;
	netsenddatapacket[45]=code;
	netsenddatapacket[46]=0;//压缩次数
	netsenddatapacket[47]=0;	

	for(i=2;i<48;i++)
	{
		ccs+=netsenddatapacket[i];
	}
	netsenddatapacket[48]=ccs;
	netsenddatapacket[49]=0xBB;
	netsenddatapacket[50]=0x66;

}
void main()
{
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  read_macaddr();
  lowpowerIO_init();
  u16 startdelay=60000;
  while(startdelay--); 
  RTC_Config();
  //串口等待配置
  USART_Config();
  TIM4_Config();
  enableInterrupts();
  delay(100);
  LED_ON
  delay(100);
  LED_OFF  
  delay(100);
  LED_ON
  delay(100);
  LED_OFF
  while(1)
  {
    read_batvolt();
    read_temp();
    Open_Power();
    gotosleep(15);
    getuploaddata();
    Net_Send(netsenddatapacket,51);
    Close_Power();
    gotosleep(600);
    delay(30);
    LED_OFF
    delay(30);
    LED_ON
  }
}

void ADC_Config(ADC_Channel_TypeDef channel)
{
  ADC_Cmd(ADC1, DISABLE);
  /* Enable ADC1 clock */
  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1, ENABLE);
  /* Initialise and configure ADC1 */
  ADC_Init(ADC1, ADC_ConversionMode_Single, ADC_Resolution_12Bit, ADC_Prescaler_2);
  ADC_SamplingTimeConfig(ADC1, ADC_Group_SlowChannels, ADC_SamplingTime_384Cycles);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* Enable ADC1 Channel 3 */
  ADC_ChannelCmd(ADC1, channel, ENABLE);
//  ADC_ChannelCmd(ADC1, ADC_Channel_1, ENABLE);
//  ADC_ChannelCmd(ADC1, ADC_Channel_4, ENABLE);
  /* Enable End of conversion ADC1 Interrupt */
  //ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);

  /* Start ADC1 Conversion using Software trigger*/
  //ADC_SoftwareStartConv(ADC1);
}

//读取锂电池电压值
void read_batvolt(void)
{
  GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_In_FL_No_IT);
  ADC_BAT_PWR_ON
  ADC_Config(ADC_Channel_0);
  SystickCount=2;
  while(SystickCount); 
  ADC_SoftwareStartConv(ADC1);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
  ADCdata = ADC_GetConversionValue(ADC1);

  ADC_BAT_PWR_OFF

  batvolt=((u32)ADCdata*66)>>12; 
  GPIO_Init(GPIOA, GPIO_Pin_6, GPIO_Mode_Out_OD_HiZ_Slow);
  ADC_Cmd(ADC1, DISABLE);
  
}
//读取热敏电阻温度
void read_temp(void)
{
  GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_In_FL_No_IT);
  ADC_TEMP_PWR_ON
  ADC_Config(ADC_Channel_1);
  SystickCount=2;
  while(SystickCount); 
  ADC_SoftwareStartConv(ADC1);
  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)==RESET);
  ADCdata = ADC_GetConversionValue(ADC1);

  ADC_TEMP_PWR_OFF
  read_t();
  GPIO_Init(GPIOA, GPIO_Pin_5, GPIO_Mode_Out_OD_HiZ_Slow);
  ADC_Cmd(ADC1, DISABLE);
  
}
void gotosleep(u16 sleeptime)
{
  /* RTC will wake-up from halt every 5second */
  RTC_SetWakeUpCounter(sleeptime);
  RTC_WakeUpCmd(ENABLE);
  TIM4_Cmd(DISABLE);
  /* Enter Wait for interrupt mode*/
  //wfi();
  halt();
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
  RTC_Config();
  TIM4_Config();
  USART_Config();
  RTC_WakeUpCmd(DISABLE);
}
const s32 t_table[151][2]={
{	-50	,	6930736	},
{	-49	,	6445208	},
{	-48	,	5997100	},
{	-47	,	5583278	},
{	-46	,	5200890	},
{	-45	,	4847341	},
{	-44	,	4520267	},
{	-43	,	4217511	},
{	-42	,	3937107	},
{	-41	,	3677258	},
{	-40	,	3436326	},
{	-39	,	3212809	},
{	-38	,	3005339	},
{	-37	,	2812660	},
{	-36	,	2633624	},
{	-35	,	2467177	},
{	-34	,	2312355	},
{	-33	,	2168273	},
{	-32	,	2034118	},
{	-31	,	1909144	},
{	-30	,	1792666	},
{	-29	,	1684053	},
{	-28	,	1582726	},
{	-27	,	1488151	},
{	-26	,	1399837	},
{	-25	,	1317332	},
{	-24	,	1240216	},
{	-23	,	1168107	},
{	-22	,	1100648	},
{	-21	,	1037512	},
{	-20	,	978396	},
{	-19	,	923020	},
{	-18	,	871124	},
{	-17	,	822471	},
{	-16	,	776837	},
{	-15	,	734018	},
{	-14	,	693823	},
{	-13	,	656077	},
{	-12	,	620616	},
{	-11	,	587288	},
{	-10	,	555953	},
{	-9	,	526480	},
{	-8	,	498747	},
{	-7	,	472643	},
{	-6	,	448062	},
{	-5	,	424906	},
{	-4	,	403086	},
{	-3	,	382516	},
{	-2	,	363117	},
{	-1	,	344817	},
{	0	,	327547	},
{	1	,	311243	},
{	2	,	295847	},
{	3	,	281301	},
{	4	,	267556	},
{	5	,	254562	},
{	6	,	242274	},
{	7	,	230650	},
{	8	,	219650	},
{	9	,	209239	},
{	10	,	199380	},
{	11	,	190041	},
{	12	,	181193	},
{	13	,	172807	},
{	14	,	164857	},
{	15	,	157317	},
{	16	,	150164	},
{	17	,	143376	},
{	18	,	136933	},
{	19	,	130816	},
{	20	,	125005	},
{	21	,	119485	},
{	22	,	114239	},
{	23	,	109252	},
{	24	,	104510	},
{	25	,	100000	},
{	26	,	95709	},
{	27	,	91626	},
{	28	,	87738	},
{	29	,	84037	},
{	30	,	80512	},
{	31	,	77154	},
{	32	,	73953	},
{	33	,	70903	},
{	34	,	67995	},
{	35	,	65221	},
{	36	,	62576	},
{	37	,	60051	},
{	38	,	57642	},
{	39	,	55342	},
{	40	,	53146	},
{	41	,	51049	},
{	42	,	49045	},
{	43	,	47130	},
{	44	,	45300	},
{	45	,	43551	},
{	46	,	41878	},
{	47	,	40278	},
{	48	,	38748	},
{	49	,	37283	},
{	50	,	35882	},
{	51	,	34540	},
{	52	,	33255	},
{	53	,	32025	},
{	54	,	30846	},
{	55	,	29717	},
{	56	,	28635	},
{	57	,	27597	},
{	58	,	26603	},
{	59	,	25649	},
{	60	,	24734	},
{	61	,	23856	},
{	62	,	23014	},
{	63	,	22206	},
{	64	,	21431	},
{	65	,	20686	},
{	66	,	19970	},
{	67	,	19283	},
{	68	,	18623	},
{	69	,	17989	},
{	70	,	17380	},
{	71	,	16794	},
{	72	,	16231	},
{	73	,	15689	},
{	74	,	15168	},
{	75	,	14667	},
{	76	,	14185	},
{	77	,	13722	},
{	78	,	13275	},
{	79	,	12845	},
{	80	,	12431	},
{	81	,	12033	},
{	82	,	11649	},
{	83	,	11279	},
{	84	,	10923	},
{	85	,	10580	},
{	86	,	10249	},
{	87	,	9930	},
{	88	,	9623	},
{	89	,	9326	},
{	90	,	9040	},
{	91	,	8764	},
{	92	,	8498	},
{	93	,	8241	},
{	94	,	7994	},
{	95	,	7754	},
{	96	,	7523	},
{	97	,	7300	},
{	98	,	7085	},
{	99	,	6877	},
{	100	,	6676	},

};
u32 res_v;
s16 wendu;
u32 res10k;
void read_t(void)
{
	u16 i;
        u16 xiaoshu;
	res_v=((u32)ADCdata*3300)>>12;
	if(res_v){
	res10k=((u32)(33000-10*res_v)*10000)/res_v;
	//查表
	for(i=0;i<150;i++){
		if((res10k>=t_table[i+1][1])&&(res10k<=t_table[i][1]))
		{
                  xiaoshu=((res10k-t_table[i+1][1])*10)/(t_table[i][1]-t_table[i+1][1]);
                  wendu=t_table[i][0]*10+xiaoshu;		
                  break;
		}
	}
	}
	else
	{
		wendu=1000;
	}
}
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
