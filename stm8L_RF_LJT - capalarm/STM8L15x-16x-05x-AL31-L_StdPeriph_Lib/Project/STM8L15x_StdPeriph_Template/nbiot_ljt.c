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
//#include "sx1276_7_8.h"
//#include "spi.h"
//#include "ds18b20.h"  
#include "define.h"
//#include "SI7021.h"
//#include "HX711.h" 



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
__IO u32 SystickCount3=0;
__IO u32 ResetCount=0;
u8*	uarttx_p=NULL;
__IO u16 uarttxlen=0;
Config_Typedef  EE_Para;
u8 keycount=0;
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
u16 id=0;
u8 ccid[21]="88888888888888888888";
u8 systatus=0;
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
s16 netresult;
u8 strbuf[256];
u8 send_ok_string[100];
u8 CSQ;
u8 netstep;
u8 ip_temp[16];
u8 ip_temp1[16];
u8 port_temp[6];
u16 period_temp;
u16 netwaittime_temp;
u8 netsenddatapacket[51];
u8 latitude[11]="0";
u8 logitude[12]="0";
u8 macaddr[6];
u16 distance;
u32 res_v;
s16 wendu;
u32 res10k;
u16 netsendlen;
u8 tcprec_data[200];
u16 tcprec_datalen;
u16 packetlen;
para_t info={
  .server_ip="101.37.247.112",
  .server_port="13000",
  .upload_period=300,
  .netwaittime=120
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
//  GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode_Out_OD_HiZ_Slow);//AD口
  
  //未用到的
  GPIO_Init(GPIOC, GPIO_Pin_1, GPIO_Mode);
  GPIO_Init(GPIOC, GPIO_Pin_4, GPIO_Mode);
  //用到的IO口  
  GPIO_Mode=GPIO_Mode_Out_PP_Low_Slow;
  GPIO_Init(GPIOA, GPIO_Pin_2, GPIO_Mode);//PWR_NBIOT
  GPIO_Init(GPIOA, GPIO_Pin_3, GPIO_Mode);//cap_uartrx_enable
  GPIO_Init(GPIOA, GPIO_Pin_4, GPIO_Mode);//PWR_TEMP_ADC 
  GPIO_Init(GPIOD, GPIO_Pin_0, GPIO_Mode); //黄灯LED
  GPIO_Init(GPIOD, GPIO_Pin_1, GPIO_Mode); //绿灯LED
  GPIO_Init(GPIOD, GPIO_Pin_2, GPIO_Mode);//RX-LORA-NSS
  GPIO_Init(GPIOD, GPIO_Pin_3, GPIO_Mode);//RX-LORA-SCK
  GPIO_Init(GPIOB, GPIO_Pin_1, GPIO_Mode);//PWR_CAP
  GPIO_Init(GPIOB, GPIO_Pin_2, GPIO_Mode);//RX-LORA-MOSI
  GPIO_Init(GPIOB, GPIO_Pin_3, GPIO_Mode_In_PU_No_IT);//RX-LORA-MISO
  GPIO_Init(GPIOB, GPIO_Pin_4, GPIO_Mode);//PB4_VCC--倾斜检测电源开关
  GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_In_FL_No_IT);//PB5_IN--红外接收头必须设置成输入浮空
  GPIO_Init(GPIOB, GPIO_Pin_6, GPIO_Mode);//PB6_VCC--红外接收头电源开关
  GPIO_Init(GPIOB, GPIO_Pin_7, GPIO_Mode);//PB4_VCC
  GPIO_Init(GPIOD, GPIO_Pin_4, GPIO_Mode);//PD4-out3
  GPIO_Init(GPIOD, GPIO_Pin_5, GPIO_Mode);//PD5-out2
  GPIO_Init(GPIOD, GPIO_Pin_6, GPIO_Mode);//PWR_KEY
  GPIO_Init(GPIOD, GPIO_Pin_7, GPIO_Mode);//PD7-out1
  GPIO_Init(GPIOC, GPIO_Pin_0, GPIO_Mode_In_FL_No_IT);//倾斜开关输入检测脚
  GPIO_Init(GPIOC, GPIO_Pin_6, GPIO_Mode);//PWR_BAT_ADC
  YLED_OFF
  GLED_OFF
  ADC_BAT_PWR_OFF//电池检测电源关闭
  GY53_RX_OFF//测距传感器接收关闭
  ADC_TEMP_PWR_OFF//温度传感器电源关闭
  CAP_PWR_OFF//测距传感器电源关闭
  NBIOT_PWR_OFF//nbiot模组电源关闭
  NBIOT_PWRKEY_OFF//nbiot启动键关闭
}


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
//返回0表示成功,其他表示失败
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
void USART_Config(u32 sudu)
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
  USART_Init(USART1, sudu, USART_WordLength_8b, USART_StopBits_1,USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Tx | USART_Mode_Rx));
  USART_Cmd(USART1, ENABLE);
  ITC_SetSoftwarePriority(USART1_RX_IRQn, ITC_PriorityLevel_3);//最高
  
}

void TIM4_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM4, ENABLE);
#if(CLKHZ==16)
  TIM4_TimeBaseInit(TIM4_Prescaler_64, 249);
#elif(CLKHZ==8)
  TIM4_TimeBaseInit(TIM4_Prescaler_32, 249);
#elif(CLKHZ==4)
  TIM4_TimeBaseInit(TIM4_Prescaler_16, 249);
#elif(CLKHZ==2)
  TIM4_TimeBaseInit(TIM4_Prescaler_8, 249);
#endif
  
  TIM4_ClearFlag(TIM4_FLAG_Update);

  TIM4_ITConfig(TIM4_IT_Update, ENABLE);

//  enableInterrupts();


  TIM4_Cmd(ENABLE);
}
/*
void TIM2_Config(void)
{
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  if(CLKHZ==4)
  TIM2_TimeBaseInit(TIM2_Prescaler_4, TIM2_CounterMode_Up,65535);
  else if(CLKHZ==8)
  TIM2_TimeBaseInit(TIM2_Prescaler_8, TIM2_CounterMode_Up,65535); 
  TIM2_Cmd(ENABLE);
}
*/
/*
1秒RTC
*/
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
/*
0.42毫秒RTC
*/
void RTC_Config_ms(void)
{

  CLK_RTCClockConfig(CLK_RTCCLKSource_LSI, CLK_RTCCLKDiv_1);//lsi=38000hz

  while (CLK_GetFlagStatus(CLK_FLAG_LSIRDY) == RESET);
  

  
  CLK_PeripheralClockConfig(CLK_Peripheral_RTC, ENABLE);


  RTC_WakeUpClockConfig(RTC_WakeUpClock_RTCCLK_Div16);//计数器2375HZ，0.42MS


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













#if(0)
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
#endif

void read_deviceinfo(void)
{
#if(0)
  FLASH_Unlock(FLASH_MemType_Data);
  FLASH_ProgramByte(0x1100, 'N');
  FLASH_ProgramByte(0x1101, 'O');
  FLASH_Lock(FLASH_MemType_Data);  
#endif
  if(*(u8*)0x1100=='O'&&*(u8*)0x1101=='K')
  {
    info=*(para_t*)0x1102;//从配置文件里读取
  }
  else
  {
#if(1)
    strcpy(info.server_ip,"101.37.247.112");
    strcpy(info.server_port,"13000");
    info.upload_period=1800;
    info.netwaittime=120;    
#endif
  }
}


void save_para(void)
{
  u8 i;
  u16 ii=255;
  u8 *p=(u8*)&info;
  FLASH_Unlock(FLASH_MemType_Data);
  FLASH_ProgramByte(0x1100, 'O');
  FLASH_ProgramByte(0x1101, 'K');
  for(i=0;i<sizeof(info);i++)
  {
    FLASH_ProgramByte(0x1102+i, *p++);
    ii=1000;while(ii--);
  }
  FLASH_Lock(FLASH_MemType_Data);   
}
void write_id(void);
void write_id(void)
{
  u8 i;
  u16 ii;
  FLASH_Unlock(FLASH_MemType_Data);
  for(i=0;i<sizeof(macaddr);i++)
  {
    FLASH_ProgramByte(0x1000+i, macaddr[i]);
    ii=1000;while(ii--);
  }
  FLASH_Lock(FLASH_MemType_Data);    
}



/*--------------------冒泡排序---------------------*/
void bubleSort(u16  data[], u8 n) {
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
#if(0)
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
#endif

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
//加入手机卡号读取,方便流量跟踪,欠费查询

void read_ccid(void)
{
  u8 res,i;
  res=At_Send("AT+CCID\r\n",0,"OK\r\n",600);
  if(res==0)
  {
    for(i=0;i<20;i++)
    {
      ccid[i]=UartRxBuf[2+i];
    }
    ccid[20]=0;
  }
}
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




u8 sendok=0;
enum connect_status
{
  AT_ERROR=0,
  AT_CARD_ERROR,
  AT_NET_ERROR,
  AT_CREATTCP_ERROR,
  AT_CONERROR,
  AT_SENDERROR,
  OKOK,
};
#define YUNYINGSHANG    0//0电信,1移动，2联通
void config_apn(void)
{
  At_Send("AT+CFUN=0\r\n",0,"OK\r\n",100);
#if(YUNYINGSHANG==0)
  At_Send("AT*MCGDEFCONT=\"IP\",\"ctnb\"\r\n",0,"OK\r\n",100);
#elif(YUNYINGSHANG==1)
  At_Send("AT*MCGDEFCONT=\"IP\",\"CMNBIOT\"\r\n",0,"OK\r\n",100);
#elif(YUNYINGSHANG==2)
  At_Send("AT*MCGDEFCONT=\"IP\",\"snbiot\"\r\n",0,"OK\r\n",100);
#endif  
  At_Send("AT+CFUN=1\r\n",0,"OK\r\n",100);
}
enum connect_status con_status;

void test_module(void)
{
  At_Send("ATE0\r\n",0,"OK\r\n",100);
  delay(300);
  At_Send("AT+CPIN?\r\n",0,"READY",100);
  delay(300);
  At_Send("AT+CGATT?\r\n",0,"+CGATT: 1",100);
  delay(300);
  Read_CSQ(&CSQ);
  delay(300);
  At_Send("AT+COPS?\r\n",0,"READY",100);
  delay(300);
  At_Send("AT+CSMINS?\r\n",0,"READY",100);
  delay(300);
  
}
u8 waitnetokcount=0;
u8 connect_server(u8 ip[],u8 port[])
{
  u16 count;
  
  con_status=OKOK;
  count=0;
  while(1)
  {
    count++;
    netresult=At_Send("ATE0\r\n",0,"OK\r\n",100);
    if(netresult==0)
    {
      
      break;
    }
    if(count>100)
    {
      con_status=AT_ERROR;
      return 1;//回显指令错误
    }
  }
#if(1)
  //读取卡状态
  count=0;
  while(1)
  {
    count++;
    netresult=At_Send("AT+CPIN?\r\n",0,"READY",100);
    if(netresult==0)
    {
      break;
    }
    sleepdelay0_42ms(1000/0.42);
    if(count>10)
    {
      con_status=AT_CARD_ERROR;
      return 2;//读卡错误
    }
  }
#endif
  read_ccid();

//  config_apn();
 // delay(10);
  waitnetokcount=0;
  while(1)
  {
    waitnetokcount++;
    Read_CSQ(&CSQ);
//    netresult=At_Send("AT+CGATT?\r\n",0,"+CGATT: 1",100);
    netresult=At_Send("AT+CGREG?\r\n",0,"+CGREG: 0,1",100);
    sleepdelay0_42ms(1000/0.42);
    if(netresult==0)
    {
      break;
    }
    
    if(waitnetokcount>info.netwaittime)
    {
      con_status=AT_NET_ERROR;
      return 3;//网络搜索不到
    }
  }
//  sleepdelay0_42ms(100/0.42);
  //主动踢掉原来链路
//  netresult=At_Send("AT+CSOCL=0\r\n",0,"\r\nOK\r\n",100);//

  //创建1路TCP 1-ipv4/2-ipv6,1-tcp,2-udp,1-IP
  netresult=At_Send("AT+CSOC=1,1,1\r\n",0,"OK",15000);
  if(netresult!=0)
  {
    con_status=AT_CREATTCP_ERROR;
    return 4;
  }
//  sleepdelay0_42ms(10/0.42);
  //使能TCP回执
  netresult=At_Send("AT+CSOSENDFLAG=1\r\n",0,"\r\nOK\r\n",500);
//  sleepdelay0_42ms(10/0.42);
	
  strcpy(strbuf, "AT+CSOCON=0,");

  strcat(strbuf,port);
  strcat(strbuf,",\"");
//  strcat(strbuf,"101.200.37.232");
//  strcat(strbuf,"101.37.247.112");server_ip
  strcat(strbuf,ip);
  strcat(strbuf,"\"\r\n");
  netresult=At_Send(strbuf,0,"OK",30000);
  if(netresult!=0)
  {
    con_status=AT_CONERROR;
    return 5;
  }
  return 0;
}
u8 Net_Send(u8 data[],u16 datalen)
{
  u16 len;
  u8 strtemp[10];
#if(0)  
  //发送数据
  if(datalen<10)
  {
    sprintf(send_ok_string, "SEND: 0,%1d", datalen);//sprintf太占内存了
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
#endif
  sendok=0;
  strcpy(send_ok_string,"SEND: 0,");
  shuzi2str(datalen,strtemp);
  strcat(send_ok_string,strtemp);
  
  strcpy(strbuf,"AT+CSOSEND=0,");
  shuzi2str(datalen*2,strtemp);
  strcat(strbuf,strtemp);  
  strcat(strbuf,","); 
  
  strcat(strbuf,"\"");
  len=strlen(strbuf);
//	hextostr(data,datalen,datahexstrbuf);
//	datahexstrbuf[datalen*2]=0;
//	strcat(strbuf,datahexstrbuf);
  hextostr(data,datalen,&strbuf[len]);
  strbuf[len+datalen*2]=0;	
  strcat(strbuf,"\"");
  strcat(strbuf,"\r\n");
  netresult=At_Send(strbuf,0,send_ok_string,30000);//返回字节长度就表示正常
  if(netresult!=0)
  {
    netstep=AT_SENDERROR;
    return 1;//发送失败
  }
  sendok=1;
  
  return 0;//发送成功

}

void server_rec(void)
{
  //等待一点时间,如果有下发数据就处理,时间等待5秒
  
  s16 pos;
  u8 findvalue[2]={0xAA,0x55};
  SystickCount=5000;
  while(SystickCount)
  {
    if(FlagUartReceive==1)
    {
      rec_server_data_NBIOT();
      UartRxCount=0;
      FlagUartReceive=0;
    }
  }
}

//0123456789ABCDEF

u8 str16tohex(u8 str16)
{
	if((str16>='A')&&(str16<='Z'))
	{
		return (str16-'A'+10);
	}
	else if((str16>='a')&&(str16<='z'))
	{
		return (str16-'a'+10);
	}
	else if(str16>='0')
	{
		return (str16-'0');
	}
}
void getackdata(u8 cmd)
{
  u8 i;
  u8 sum=0;
  netsendlen=0;
  netsenddatapacket[netsendlen++]=0xAA;
  netsenddatapacket[netsendlen++]=0x55;
  netsenddatapacket[netsendlen++]=cmd;//帧类型
  netsenddatapacket[netsendlen++]=0x01;//设备类型
  netsenddatapacket[netsendlen++]=macaddr[0];
  netsenddatapacket[netsendlen++]=macaddr[1];
  netsenddatapacket[netsendlen++]=macaddr[2];
  netsenddatapacket[netsendlen++]=macaddr[3];
  netsenddatapacket[netsendlen++]=macaddr[4];
  netsenddatapacket[netsendlen++]=macaddr[5];
  netsenddatapacket[netsendlen++]=1;
  for(i=0;i<netsendlen;i++)
  {
    sum+=netsenddatapacket[i];
  }
  netsenddatapacket[netsendlen++]=sum;
  netsenddatapacket[netsendlen++]=0xBB;
  netsenddatapacket[netsendlen++]=0x66;
}
void rec_server_data_NBIOT(void)//+CSONMI: 0,28,AA55FF0407E20906093A2462BB66
{
  s16 pos;
  s16 datapos;//实际数据索引位置
  u16 i;
  u8 rec_temp;
  u8 * p=NULL;
  u8 * p1=NULL;
  //检查下是否是wifiserverrx数据,如果不是就送给AT队列
  while(1)
  {
    pos=Find_Array(UartRxBuf,UartRxCount,"+CSONMI: 0,",strlen("+CSONMI: 0,"));//改成数组方式搜索
    if(pos==-1)
    {
      break;//未找到+CSONMI: 0,退出
    }
    //找到的+CSONMI: 0,头删除,防止下一次搜索重复
    UartRxBuf[pos]='-';	
    packetlen=GetATValueNumber(&UartRxBuf[pos],",");//获取长度			
    if(packetlen<10)
    {
      datapos=pos+strlen("+CSONMI: 0,")+2;
    }
    else if(packetlen<100)
    {
      datapos=pos+strlen("+CSONMI: 0,")+3;
    }
    else if(packetlen<1000)
    {
      datapos=pos+strlen("+CSONMI: 0,")+4;
    }
#if defined(ALIYUN)		
    for(i=0;i<(packetlen/2);i++)
    {
      rec_temp=str16tohex(UartRxBuf[datapos+i*2])*16+str16tohex(UartRxBuf[datapos+i*2+1]);
    }			
#else
    for(i=0;i<(packetlen/2);i++)
    {
      tcprec_data[i]=str16tohex(UartRxBuf[datapos+i*2])*16+str16tohex(UartRxBuf[datapos+i*2+1]);
    }	
    tcprec_datalen=packetlen/2;
    //这里解析
    if((tcprec_data[0]==0xAA)&&(tcprec_data[1]==0x55)&&(tcprec_data[2]==0xFE)&&(tcprec_datalen==26))
    {
      //下发ip和port--AA55 FE31 3031 2E32 3030 2E33 372E 3233 3200 3737 3737 00DD BB66 
      //101.200.37.232 7777
      for(i=0;i<15;i++)//ip
      {
        ip_temp[i]=tcprec_data[3+i];
        ip_temp1[i]=ip_temp[i];
      }
      ip_temp[i]=0;
      for(i=0;i<5;i++)//port
      {
        port_temp[i]=tcprec_data[18+i];
      }
      port_temp[i]=0;
      //需要验证是不是正确的IP和port
      if(IsIpv4(ip_temp1)==TRUE)
      {
        if(IsPort(port_temp)==TRUE)
        {
          //合法的ip和port就保存
          strcpy(info.server_ip,ip_temp);
          strcpy(info.server_port,port_temp);
          save_para();
          //返回应答
          getackdata(0xFE);
          Net_Send(netsenddatapacket,netsendlen);
          SystickCount=3000;
        }
      }
    }
    else if((tcprec_data[0]==0xAA)&&(tcprec_data[1]==0x55)&&(tcprec_data[2]==0xFD)&&(tcprec_datalen==8))
    {
      //设置上传周期--AA55 FD01 2CDD BB66 
      //300秒
      period_temp=((u16)tcprec_data[3]<<8)+tcprec_data[4];
      if(period_temp>30)
      {
        //合理的上传周期就保存
        info.upload_period=period_temp;
        save_para();
        //返回应答
        getackdata(0xFD);
        Net_Send(netsenddatapacket,netsendlen);
        SystickCount=3000;
      }
             
    }
    else if((tcprec_data[0]==0xAA)&&(tcprec_data[1]==0x55)&&(tcprec_data[2]==0xFC)&&(tcprec_datalen==8))
    {
      //设置网络超时等待--AA55 FC01 2CDD BB66 
      //300秒
      netwaittime_temp=((u16)tcprec_data[3]<<8)+tcprec_data[4];
      if((netwaittime_temp>10)&&(netwaittime_temp<600))
      {
        //合理的超时等待时间就保存
        info.netwaittime=netwaittime_temp;
        save_para();
        //返回应答
        getackdata(0xFC);
        Net_Send(netsenddatapacket,netsendlen);
        SystickCount=3000;
      }
             
    }
#endif
  }
}
/*
    1、只有三个点 , 四部分，每个数都在 0 ~ 255 
    2、数字不能是 0开头 如：012.1.1.1 

*/

bool IsPort(char*str)
{
  u8 i;
  if(str[0] == '0' && ((str[1]>='0')&&(str[1]<='9'))) return FALSE;
  for(i=0;i<5;i++)
  {
    if((str[i]>='0')&&(str[i]<='9'))
    {
      //正常
    }
    else if((str[i]==0)&&(i!=0))
    {
      return TRUE;
    }
    else
    {
      return FALSE;
    }
  }
  return TRUE;
}
bool IsIpv4(char*str)
{
    char* ptr;
    int count = 0;
    const char *p = str;

    //1、判断是不是三个 ‘.’
    //2、判断是不是先导0
    //3、判断是不是四部分数
    //4、第一个数不能为0

    while(*p !='\0')
    {
        if(*p == '.')
        count++;
        p++;
    }

    if(count != 3)  return FALSE;
    count = 0;
    ptr = strtok(str,".");
    while(ptr != NULL)
    {   
        count++;
        if(ptr[0] == '0' && ((ptr[1]>='0')&&(ptr[1]<='9'))) return FALSE;
        int a = atoi(ptr);
        if(count == 1 && a == 0) return FALSE;
        if(a<0 || a>255) return FALSE;
        ptr = strtok(NULL,".");

    }
    if(count == 4)  return TRUE;
    else  return FALSE;
}


void key_init_disenable(void)
{
  //唤醒脚
  GPIO_Init(KEY_WAKEUP_PORT,KEY_WAKEUP_PIN,GPIO_Mode_In_PU_No_IT);  
}

void key_init(void)
{
  
  //唤醒脚
  GPIO_Init(KEY_WAKEUP_PORT,KEY_WAKEUP_PIN,GPIO_Mode_In_PU_IT);  
  EXTI_SetPinSensitivity(EXTI_Pin_5, EXTI_Trigger_Falling);
  ITC_SetSoftwarePriority(EXTI1_IRQn, ITC_PriorityLevel_1);
  
}

void Open_Power(void)
{
  NBIOT_PWR_ON//打开电源
  sleepdelay0_42ms(100/0.42);
  NBIOT_PWRKEY_ON
//开机过程中可以进入休眠
  sleepdelay0_42ms(2000/0.42);//开机pwrkey脚拉低至少0.8秒
//  delay(9000);
//  NBIOT_PWRKEY_OFF
}

void Close_Power(void)
{

  NBIOT_PWRKEY_OFF  
  NBIOT_PWR_OFF//关闭电源
}

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
  MCUID[0]=MCUID[0]+MCUID[1];
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
u8 flagtrig_rtc=0;
u8 flagtrig_key=0;
//AA 55 D2 01 06 90 61 55 00 80 17 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 28 00 17 01 03 00 F8 BB 66 
void getuploaddatanew(void)
{
  u8 i;
  u8 sum=0;
  netsendlen=0;
  netsenddatapacket[netsendlen++]=0xAA;
  netsenddatapacket[netsendlen++]=0x55;
  netsenddatapacket[netsendlen++]=0xd2;//帧类型
  netsenddatapacket[netsendlen++]=0x01;//设备类型
  netsenddatapacket[netsendlen++]=macaddr[0];
  netsenddatapacket[netsendlen++]=macaddr[1];
  netsenddatapacket[netsendlen++]=macaddr[2];
  netsenddatapacket[netsendlen++]=macaddr[3];
  netsenddatapacket[netsendlen++]=macaddr[4];
  netsenddatapacket[netsendlen++]=macaddr[5];
  netsenddatapacket[netsendlen++]=CSQ;  
  for(i=0;i<11;i++)
  {
    netsenddatapacket[netsendlen++]=latitude[i];
  }
  for(i=0;i<12;i++)
  {
    netsenddatapacket[netsendlen++]=logitude[i];
  }
  for(i=0;i<20;i++)
  {
    netsenddatapacket[netsendlen++]=ccid[i];
  }
  netsenddatapacket[netsendlen++]=batvolt;//锂电池电压
  netsenddatapacket[netsendlen++]=distance>>8;//容量距离高8位
  netsenddatapacket[netsendlen++]=distance;//容量距离低8位
  netsenddatapacket[netsendlen++]=wendu>>8;//温度高8位
  netsenddatapacket[netsendlen++]=wendu;//温度低8位
  netsenddatapacket[netsendlen++]=info.upload_period>>8;//上传周期高8位
  netsenddatapacket[netsendlen++]=info.upload_period;//上传周期低8位
  if(flagtrig_key==1)
  {
    netsenddatapacket[netsendlen++]=1;
  }
  else
  {
    netsenddatapacket[netsendlen++]=0;
  }
  netsenddatapacket[netsendlen++]=waitnetokcount;
  netsenddatapacket[netsendlen++]=id>>8;
  netsenddatapacket[netsendlen++]=id;
  netsenddatapacket[netsendlen++]=systatus;//状态
  for(i=0;i<netsendlen;i++)
  {
    sum+=netsenddatapacket[i];
  }
  netsenddatapacket[netsendlen++]=sum;
  netsenddatapacket[netsendlen++]=0xBB;
  netsenddatapacket[netsendlen++]=0x66;
}

#if(CLKHZ==16)
u16 startdelay=60000;
#elif(CLKHZ==8)
u16 startdelay=30000;
#elif(CLKHZ==4)
u16 startdelay=15000;
#elif(CLKHZ==2)
u16 startdelay=7500;
#endif

u8 flagfull=0;
u8 flagfullcount=0;
#define MAX(a, b)     (((a) > (b) ) ? (a) : (b))
#define MIN(a, b)     (((a) < (b) ) ? (a) : (b))
#define READCAPCOUNT    6
u16 distance_buf[READCAPCOUNT];
u8 id_check(void);
//id验证,0x1000开始6字节
u8 id_check(void)
{
  u8 i;
  for(i=0;i<6;i++)
  {
    if(macaddr[i]!=*(u8*)(0x1000+i))
    {
       break;
    } 
  }
  if(i==6)
  {
    return 0;
  }
  return 1;
}
/**
  * @brief  Configure TIM1 peripheral 
  * @param  None
  * @retval None
  */
  
#if(CLKHZ==16)
  u16 period=400;
#elif(CLKHZ==8)
  u16 period=200;
#elif(CLKHZ==4)
  u16 period=100;
#elif(CLKHZ==2)
  u16 period=50;
#endif
static void TIM2_Config(void)
{

  CLK_PeripheralClockConfig(CLK_Peripheral_TIM2, ENABLE);
  GPIO_Init(GPIOB, GPIO_Pin_0 , GPIO_Mode_Out_PP_Low_Fast);

 
  TIM2_TimeBaseInit(0, TIM2_CounterMode_Up, period);//2M/50=40KHZ,0.025ms*240=6ms，,29


  TIM2_OC1Init(TIM2_OCMode_PWM1, TIM2_OutputState_Enable,period/3, TIM2_OCPolarity_Low,  TIM2_OCIdleState_Set);//24占空比
  TIM2_OC1PreloadConfig(DISABLE);


  TIM2_ARRPreloadConfig(ENABLE);
  TIM2_SetCounter(0);

//  TIM2_ITConfig(TIM2_IT_Update, ENABLE);
  

  /* Enable TIM1 outputs */
  TIM2_CtrlPWMOutputs(ENABLE);
  
  /* TIM1 enable counter */
//  TIM2_Cmd(ENABLE);//启动红外发波
}
static void TIM3_Config(u16 pwm_num)
{
  u16 time;
  CLK_PeripheralClockConfig(CLK_Peripheral_TIM3, ENABLE);
  time=pwm_num*25;
#if(CLKHZ==16)
  TIM3_TimeBaseInit(TIM3_Prescaler_16, TIM3_CounterMode_Up, time);//1200us
#elif(CLKHZ==8)
  TIM3_TimeBaseInit(TIM3_Prescaler_8, TIM3_CounterMode_Up, time);//1200us
#elif(CLKHZ==4)
  TIM3_TimeBaseInit(TIM3_Prescaler_4, TIM3_CounterMode_Up, time);//1200us
#elif(CLKHZ==2)
  TIM3_TimeBaseInit(TIM3_Prescaler_2, TIM3_CounterMode_Up, time);//1200us
#endif  
  
  
//  TIM3_TimeBaseInit(0, TIM3_CounterMode_Up, time);//1200us




  TIM3_ARRPreloadConfig(ENABLE);
  TIM3_SetCounter(0);

  TIM3_ITConfig(TIM3_IT_Update, ENABLE);
  

  /* Enable TIM1 outputs */
//  TIM1_CtrlPWMOutputs(ENABLE);
  
  /* TIM1 enable counter */
//  TIM1_Cmd(ENABLE);//启动红外发波
}
uint8_t ifreccount=0;
uint8_t flaginfraredwork=0; //红外工作标记
uint8_t flagobjectdetection=0;//有物体感应到
void start_infrared_emission(void);
void start_infrared_emission(void)
{
//  ON_IF
//  delay(100);
  TIM2_SetCounter(0);
  TIM3_SetCounter(0);
  TIM3_Cmd(ENABLE);//启动红外发波
  TIM2_Cmd(ENABLE);//启动红外发波
  flaginfraredwork=1;//红外检测标记  
}
void stop_infrared_emission(void);
void stop_infrared_emission(void)
{
  
  TIM2_SetCounter(0);
  TIM3_SetCounter(0);
  TIM3_Cmd(DISABLE);
//  TIM1_SetCompare1(0);
  TIM2_Cmd(DISABLE);//关闭红外发波
  flaginfraredwork=0;//红外检测标记  
}
/*
返回1:无效
返回0:有效
*/
uint8_t read_infrared_reception(void);
uint8_t read_infrared_reception(void)
{
  if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)==0)//红外检测口
  {
    return 0;
  }
  else
  {
    return 1;
  }
}
u8 IF_power=3;//0-3,0最小
u8 read_cap_IF(u8 powerlevel);
u8 read_cap_IF(u8 powerlevel)
{
    //红外感应检测开始
    ON_IF//打开接收头的电源
    QINGDAO_ON
    SWITCH1_OFF
    SWITCH2_OFF
    SWITCH3_OFF  
    SWITCH4_OFF 
    sleepdelay0_42ms(10/0.42);//等待外设稳定时间
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)==0)
    {
      systatus|=0x01;
    }
    else
    {
      systatus&=(~0x01);
    }
    QINGDAO_OFF
    if(powerlevel==0)//2000
    {
      SWITCH4_ON
    }
    else if(powerlevel==1)//1000
    {     
      SWITCH3_ON       
    }
    else if(powerlevel==2)//680
    {
      SWITCH2_ON
    }
    else if(powerlevel==3)//507
    {
      SWITCH2_ON
      SWITCH4_ON 
    }
    else if(powerlevel==4)//404
    {
      SWITCH2_ON
      SWITCH3_ON 
    }
    else if(powerlevel==5)//330
    {
      SWITCH1_ON
    }
    else if(powerlevel==6)//283
    {
      SWITCH1_ON
      SWITCH4_ON
    }
    else if(powerlevel==7)//220
    {
      SWITCH1_ON
      SWITCH3_ON
      SWITCH4_ON
    }
    else if(powerlevel==8)//200
    {
      SWITCH1_ON
      SWITCH2_ON
      SWITCH4_ON
    }
    else if(powerlevel==9)//180
    {
      SWITCH1_ON
      SWITCH2_ON
      SWITCH3_ON
    }
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_In_FL_No_IT);//输入脚
    TIM2_Config();
    TIM3_Config(300);//发送的波形数量决定了距离
    start_infrared_emission();//启动红外发射
    ifreccount=0;
    flagobjectdetection=0;
    while(flaginfraredwork==1)
    {
      
      if(read_infrared_reception()==0)
      {
        //探测到有物体       
        ifreccount++;       
      }
      else
      {
        
      }
      if(ifreccount>60)
      {
        flagobjectdetection=1;
        break;
      }
    }

    SWITCH1_OFF
    SWITCH2_OFF
    SWITCH3_OFF
    SWITCH4_OFF 
    GPIO_Init(GPIOB, GPIO_Pin_5, GPIO_Mode_Out_PP_Low_Slow);//输入脚改成输出0
    OFF_IF
    TIM2_DeInit();
    GPIO_Init(GPIOB, GPIO_Pin_0 , GPIO_Mode_Out_PP_Low_Fast);
    if(flagobjectdetection==0)
    {
      //没有感应到物体进入休眠
      YLED_OFF
      //distance|=(1<<powerlevel);
    }
    else if(flagobjectdetection==1)
    {
      YLED_ON
      //distance&=(~(1<<powerlevel));
    } 
    return flagobjectdetection;
    //红外检测结束  
}
u16 keypresscount=0;


#if(WRITE_ID==1)
u8 flagwriteid=0;
#endif
void main()
{
  u8 i;
#if(CLKHZ==16)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
#elif(CLKHZ==8)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
#elif(CLKHZ==4)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
#elif(CLKHZ==2)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
#endif

  
  while(startdelay--);
  read_macaddr();

  
  lowpowerIO_init();
  TIM4_Config();
  enableInterrupts();
#if(WRITE_ID==1)
  while(1)
  {
    if(flagwriteid==0)
    {
      YLED_ON
      GLED_ON
      write_id();
      if(id_check()==0)
      {
        flagwriteid=1;
      }
    }
    else
    {
      YLED_ON
      GLED_ON
      delay(40);
      YLED_OFF
      GLED_OFF
      delay(40);
    }
  }
#endif

  read_deviceinfo();
  disableInterrupts();
  key_init();
  lowpowerIO_init();

  
  RTC_Config();
  //串口等待配置
  USART_Config(9600);
  TIM4_Config();//判断一帧收到
  enableInterrupts();
  NBIOT_PWR_OFF//关闭电源
  /*启动时2个指示灯闪烁*/
  while(1)
  {
    startdelay=10;
    while(startdelay--)
    {
      YLED_ON
      GLED_ON
      sleepdelay0_42ms(50/0.42);
      YLED_OFF
      GLED_OFF
      sleepdelay0_42ms(50/0.42);
    }
    if(id_check()==0)//校验通过执行正常
    break;
  }
//  gotosleep(10);
#if(1)//设备序列号固定写入
  macaddr[0]=0x81;
  macaddr[1]=0x30;
  macaddr[2]=0x62;
  macaddr[3]=0x98;
  macaddr[4]=0x57;
  macaddr[5]=0x81;
#endif
//  Open_Power();//打开nbiot电源
  while(1)
  {
    id++;//报警器工作1次加1
    SystickCount3=0;
    read_batvolt();//读取锂电池电压
    read_temp();//读取温度
 //   read_cap();//读取容量-GY-53
#if(0)
    while(1){
    GLED_ON
    read_cap_IF();
    GLED_OFF
//    sleepdelay0_42ms(5000/0.42);

   gotosleep(5);
    }
#endif
    distance=11;//0~11,0表示感应到的距离越短
    for(i=0;i<10;i++)
    {
      if(read_cap_IF(i))
      {
        distance=i;
        break;
      }
    }

    Open_Power();//打开nbiot电源

    //数据发送    
    if(connect_server(info.server_ip,info.server_port)==0)
    {
      getuploaddatanew();//准备好数据包
      if(Net_Send(netsenddatapacket,netsendlen)==0)
      {
        server_rec();//等待服务器接收
        At_Send("AT+CSOCL=0\r\n",0,"\r\nOK\r\n",100);//断开链路
      }
    }
    Close_Power();//关闭nbiot电源--确保信号已经发出
    if(1==sendok)
    {
      i=4;
      while(i--){
      YLED_ON
      sleepdelay0_42ms(250/0.42);//黄灯快闪2秒,网络发送数据成功
      YLED_OFF  
      sleepdelay0_42ms(250/0.42);
      }
    }
    gotosleep(info.upload_period);//进入休眠
    

    GLED_ON
    sleepdelay0_42ms(2000/0.42);//待机->运行，绿灯常亮2秒
    GLED_OFF
    keypresscount=0;  

    //长按按钮,判断是否需要重新初始化参数
    while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)==0)//
    {
      //如果被拉低

      keypresscount++;
      sleepdelay0_42ms(100/0.42);
      if(keypresscount>36)//长按计时
      {
#if(1)
        strcpy(info.server_ip,"101.37.247.112");
        strcpy(info.server_port,"13000");
        info.upload_period=1800;//默认半个小时1次
        info.netwaittime=120;//网络等待超时2分钟    
#endif
        save_para();
        //绿灯慢闪3秒表示恢复出厂设置成功
        GLED_ON
        sleepdelay0_42ms(500/0.42);
        GLED_OFF
        sleepdelay0_42ms(500/0.42);
        GLED_ON
        sleepdelay0_42ms(500/0.42);
        GLED_OFF
        sleepdelay0_42ms(500/0.42);
        GLED_ON
        sleepdelay0_42ms(500/0.42);
        GLED_OFF
        sleepdelay0_42ms(500/0.42);
        break;
      }
    }
  

  }
}
u16 comparevalue;
u16 comparecountmax;
u8  comparecountmax_pos;
u16 comparecount[READCAPCOUNT];

void read_cap(void)
{ 
  u8 i=0;
  u8 j=0;
  while(1)
  {
  CAP_PWR_ON
  sleepdelay0_42ms(400/0.42);
  GY53_RX_ON
  FlagUartReceive=0;
  while(1){
  i=0;
  SystickCount=2000;
  while(SystickCount)
  {
    if(FlagUartReceive==1)
    {
      if((UartRxCount==8)&&(UartRxBuf[0]==0x5A)&&(UartRxBuf[1]==0x5A))
      {
        distance_buf[i++]=((u16)UartRxBuf[4]<<8)+UartRxBuf[5];//找到一组正常的就取走
        UartRxCount=0;
        FlagUartReceive=0;
        break;
      }
      UartRxCount=0;
      FlagUartReceive=0;
    }
  }
  }
  CAP_PWR_OFF
    
  GY53_RX_OFF
  if(i==READCAPCOUNT)
  break;
  sleepdelay0_42ms(1000/0.42);
  }
#if(1)  
  /*计算数字出现最多的那组,并且那一组的数据最平均*/
  //智能模式
  for(i=0;i<READCAPCOUNT;i++)
  {
    comparevalue=distance_buf[i];
    comparecount[i]=2500*READCAPCOUNT;
    for(j=0;j<READCAPCOUNT;j++)
    {
      if(abs(comparevalue-distance_buf[j])<20)//接近误差值2cm
      {
        comparecount[i]-=abs(comparevalue-distance_buf[j]);    
      }
      else
      {
        comparecount[i]-=2500;
      }
    }
  }
  comparecountmax=comparecount[0];
  comparecountmax_pos=0;
  for(i=1;i<READCAPCOUNT;i++)
  {
    if(comparecount[i]>comparecountmax)
    {
      comparecountmax_pos=i;
      comparecountmax=comparecount[i];
    }
  }
  distance = distance_buf[comparecountmax_pos];
#else
  //普通模式
  bubleSort(distance_buf, READCAPCOUNT);
  distance =distance_buf[READCAPCOUNT>>1];
#endif
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
  ADC_DeInit(ADC1);
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
        
void sleepdelay0_42ms(u16 dlycount)
{
  /* RTC will wake-up from halt every 5second */
  key_init_disenable();//打开电源的时候,屏蔽掉外部唤醒功能  
  RTC_Config_ms();
  RTC_SetWakeUpCounter(dlycount);//0.42MS
  RTC_WakeUpCmd(ENABLE);
  TIM4_Cmd(DISABLE);
  TIM2_Cmd(DISABLE);
  TIM3_Cmd(DISABLE);
  enableInterrupts();
  /* Enter Wait for interrupt mode*/
  //wfi();
  halt();
#if(CLKHZ==16)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
#elif(CLKHZ==8)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
#elif(CLKHZ==4)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
#elif(CLKHZ==2)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
#endif
  RTC_Config();
  TIM4_Config();
  RTC_WakeUpCmd(DISABLE);
  disableInterrupts();
  key_init();
  enableInterrupts();  
}
void gotosleep(u16 sleeptime)
{
  /* RTC will wake-up from halt every 5second */
  disableInterrupts();
  RTC_Config();
  RTC_SetWakeUpCounter(sleeptime);
  RTC_WakeUpCmd(ENABLE);
  TIM4_Cmd(DISABLE);
  TIM2_Cmd(DISABLE);
  TIM3_Cmd(DISABLE);
  RTC_ClearITPendingBit(RTC_IT_WUT);
  flagtrig_key=0;
  flagtrig_rtc=0;
  GLED_OFF//进入休眠前,把指示灯关掉
  YLED_OFF
  enableInterrupts();
  /* Enter Wait for interrupt mode*/
  //wfi();
  halt();
#if(CLKHZ==16)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
#elif(CLKHZ==8)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_2);
#elif(CLKHZ==4)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_4);
#elif(CLKHZ==2)
  CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_8);
#endif
  RTC_Config();
  TIM4_Config();
  RTC_WakeUpCmd(DISABLE);
  enableInterrupts();
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
