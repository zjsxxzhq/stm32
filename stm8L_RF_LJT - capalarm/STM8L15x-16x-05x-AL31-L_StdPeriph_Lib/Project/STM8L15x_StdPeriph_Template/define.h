#ifndef _DEFINE_H_
#define _DEFINE_H_
#include "stm8l15x.h"
#include "spi.h"
#include "sx1276_7_8.h"
#define USE_UART_IT_SEND        1
#define CLKHZ   2
#define WRITE_ID        0//0正常程序，1加密程序

//垃圾种类-------无线垃圾桶
/*
‘0’:感染性废物
‘1’:损伤性废物
‘2’:化学性废物
‘3’:药物性废物
‘4’:病理性废物
‘5’:利器盒
‘6’:输液袋
‘7’:输液瓶
‘8’:胎盘
‘9’:注射器
*/
enum lajitype
{
  ganran=0,
  shunshang,
  huaxue,
  yaowu,
  bingli,
  liqihe,
  shuyedai,
  shuyeping,
  taipan,
  zhusheqi,
  
};

typedef struct
{
  u8 sf;//扩频因子
  u8 bw;//带宽
  u8 cr;//编码率
  u8 lowspeed;//低速率优化
  u8 pw;//功率  
  u8 rfaddr;//模块地址
  u8 pp;//前导码
  u8 rfmhz[3];//无线频率
}Config_Typedef;
extern Config_Typedef  EE_Para;
#define MASTER  1
#define SLAVE   0
#define HIGH_LEVEL      1
#define LOW_LEVEL       0
#define DS18B20_TYPE    0
#define SI7021_TYPE     1
#define RX_GLED_GPIO    GPIOC
#define RX_GLED_PIN     GPIO_Pin_3
#define TX_RLED_GPIO    GPIOC
#define TX_RLED_PIN     GPIO_Pin_2
#define RX_GLED_TOGGLE  RX_GLED_GPIO->ODR ^= RX_GLED_PIN;//GPIO_ToggleBits(RX_GLED_GPIO, RX_GLED_PIN);
#define TX_RLED_TOGGLE  TX_RLED_GPIO->ODR ^= TX_RLED_PIN;//GPIO_ToggleBits(TX_RLED_GPIO, TX_RLED_PIN);

#define ON_TX_RLED  //TX_RLED_GPIO->ODR &= (uint8_t)(~TX_RLED_PIN);//GPIO_ResetBits(TX_RLED_GPIO, TX_RLED_PIN);
#define OFF_TX_RLED //TX_RLED_GPIO->ODR |= TX_RLED_PIN;//GPIO_SetBits(TX_RLED_GPIO, TX_RLED_PIN);

#define ON_RX_GLED //RX_GLED_GPIO->ODR &= (uint8_t)(~RX_GLED_PIN);//GPIO_ResetBits(RX_GLED_GPIO, RX_GLED_PIN);
#define OFF_RX_GLED //RX_GLED_GPIO->ODR |= RX_GLED_PIN;//GPIO_SetBits(RX_GLED_GPIO, RX_GLED_PIN);

#define LED_DATA_GPIO   GPIOD
#define LED_DATA_PIN  GPIO_Pin_1  

#define LED_CLEAR_GPIO   GPIOD
#define LED_CLEAR_PIN  GPIO_Pin_0  

#define ON_DATA_LED     GPIO_ResetBits(LED_DATA_GPIO, LED_DATA_PIN);//数据发送灯
#define OFF_DATA_LED    GPIO_SetBits(LED_DATA_GPIO, LED_DATA_PIN);

#define ON_CLEAR_LED    GPIO_ResetBits(LED_CLEAR_GPIO, LED_CLEAR_PIN);
#define OFF_CLEAR_LED   GPIO_SetBits(LED_CLEAR_GPIO, LED_CLEAR_PIN);

#define AD_POWER_GPIO GPIOA
#define AD_POWER_PIN GPIO_Pin_6

#define WEIGHT_POWER_GPIO GPIOA
#define WEIGHT_POWER_PIN GPIO_Pin_5

#define AD_POWER_ON GPIO_SetBits(AD_POWER_GPIO, AD_POWER_PIN);
#define AD_POWER_OFF GPIO_ResetBits(AD_POWER_GPIO, AD_POWER_PIN);

#define WEIGHT_POWER_ON //GPIO_SetBits(WEIGHT_POWER_GPIO, WEIGHT_POWER_PIN);
#define WEIGHT_POWER_OFF //GPIO_ResetBits(WEIGHT_POWER_GPIO, WEIGHT_POWER_PIN);





//满溢报警器

#define KEY_WAKEUP_PORT    GPIOC
#define KEY_WAKEUP_PIN     GPIO_Pin_5



#define ADC_BAT_PWR_ON  GPIO_SetBits(GPIOC, GPIO_Pin_6);//PC6
#define ADC_BAT_PWR_OFF GPIO_ResetBits(GPIOC, GPIO_Pin_6);

#define GY53_RX_ON  GPIO_SetBits(GPIOA, GPIO_Pin_3);
#define GY53_RX_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_3);

#define ADC_TEMP_PWR_ON  GPIO_SetBits(GPIOA, GPIO_Pin_4);//温度检测开关
#define ADC_TEMP_PWR_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_4);


#define CAP_PWR_ON  GPIO_SetBits(GPIOB, GPIO_Pin_1);//容量检测开关
#define CAP_PWR_OFF GPIO_ResetBits(GPIOB, GPIO_Pin_1);

#define NBIOT_PWR_ON  GPIO_SetBits(GPIOA, GPIO_Pin_2);//nbiot模块电源开关PA2
#define NBIOT_PWR_OFF GPIO_ResetBits(GPIOA, GPIO_Pin_2);

#define NBIOT_PWRKEY_ON  GPIO_SetBits(GPIOD, GPIO_Pin_6);//nbiot模块pwrkey脚
#define NBIOT_PWRKEY_OFF GPIO_ResetBits(GPIOD, GPIO_Pin_6);

#define YLED_OFF GPIO_SetBits(GPIOD, GPIO_Pin_0);
#define YLED_ON  GPIO_ResetBits(GPIOD, GPIO_Pin_0); 

#define GLED_OFF GPIO_SetBits(GPIOD, GPIO_Pin_1);
#define GLED_ON  GPIO_ResetBits(GPIOD, GPIO_Pin_1); 

#define ON_IF   GPIO_SetBits(GPIOB, GPIO_Pin_6);//红外感应电源开关
#define OFF_IF  GPIO_ResetBits(GPIOB, GPIO_Pin_6);

#define QINGDAO_ON GPIO_SetBits(GPIOB, GPIO_Pin_4);//倾倒开关打开
#define QINGDAO_OFF  GPIO_ResetBits(GPIOB, GPIO_Pin_4); 

#define SWITCH1_ON GPIO_SetBits(GPIOD, GPIO_Pin_7);//330R
#define SWITCH1_OFF  GPIO_ResetBits(GPIOD, GPIO_Pin_7); 

#define SWITCH2_ON GPIO_SetBits(GPIOD, GPIO_Pin_5);//680R
#define SWITCH2_OFF  GPIO_ResetBits(GPIOD, GPIO_Pin_5); 

#define SWITCH3_ON GPIO_SetBits(GPIOD, GPIO_Pin_4);//1000R
#define SWITCH3_OFF  GPIO_ResetBits(GPIOD, GPIO_Pin_4); 

#define SWITCH4_ON GPIO_SetBits(GPIOB, GPIO_Pin_7);//2000R
#define SWITCH4_OFF  GPIO_ResetBits(GPIOB, GPIO_Pin_7); 
typedef struct
{
  u8 server_ip[16];//="101.200.37.232";服务器地址
  u8 server_port[6];//="7777";  端口
  u16 upload_period;//3600上传周期
  u16 netwaittime;
//  u16 alarmdistance;//报警距离
//  u16 alarmresetdistance;//恢复距离  
}para_t;
void key_init(void);
void key_init_disenable(void);
void Open_Power(void);
void Close_Power(void);
void getuploaddata(void);
u8 read_macaddr(void);
u16 CRC16(u8* pchar, u8 charlen);
u8 read_macaddr(void);
void getuploaddatanew(void);
void read_cap(void);
void read_t(void);
int str2int(const char *str);
char *itoa(int value, char *string, int radix);
u8 Sum(u8 buf[],u8 len);
void lowpowerIO_init(void);
s8 At_Send(u8 atcmd[],u16 sendlen,u8 findvalue[],u16 overtimes);
s16 Find_Array(u8 array[],u16 array_len,u8 find_array[],u16 find_array_len);
void delay(u32 ms);
void USART_Config(u32 sudu);
void TIM4_Config(void);
void TIM2_Config(void);
void RTC_Config(void);
void UART_IT_Send(u8* buffer,u16 len);
void CLK_Config(void);
void bubleSort(u16  data[], u8 n);
void hextostr(char hex[],u16 hexlen,char str[]);
u32 GetATValueNumber(char *srcstr,char *str);
u8 Read_CSQ(u8* csq);

u8 str16tohex(u8 str16);
void rec_server_data_NBIOT(void);
void key_init_disenable(void);
void key_init(void);
void Open_Power(void);
void Close_Power(void);
void read_temp(void);
void gotosleep(u16 sleeptime);
void ADC_Config(ADC_Channel_TypeDef channel);
void read_batvolt(void);
void delay_us(u16 time);
bool IsIpv4(char*str);
bool IsPort(char*str);
void save_para(void);
void read_deviceinfo(void);
u8 connect_server(u8 ip[],u8 port[]);
u8 Net_Send(u8 data[],u16 datalen);
void server_rec(void);
void getackdata(u8 cmd);
void config_apn(void);
void read_ccid(void);
void test_module(void);
void sleepdelay0_42ms(u16 dlycount);
void RTC_Config_ms(void);
extern u8 UartRxBuf[255];
extern u8 UartRxLen;
extern u8 UartRxCount;
extern u8 UartRxCountLast;
extern u8 FlagUartReceive;
extern __IO u32 SystickCount;
extern __IO u32 SystickCount1;
extern __IO u32 SystickCount2;
extern __IO u32 SystickCount3;
extern __IO u32 ResetCount;
extern u8 flagclearljt;
extern u8 keycount;
extern u8 flagmaopi;
extern u32 uartrxdataallcount;
extern u32 uartrxdataerrorcount;
extern u8 flagtrig_rtc;
extern u8 flagtrig_key;
void shuzi2str(u16 value,u8 str[]);
#endif





