#include "stm8l15x.h"
#include "SI7021.h"
#include "ds18b20.h"
s16 si7021_temp;
u16 si7021_humi;
void delay_x_us ( void );
void start_i2c ( void );
void stop_i2c ( void );
u8 send_1byte ( unsigned char send_data );
unsigned char read_1byte ( void );
void master_i2c_ack ( void );
void master_i2c_noack ( void );
void delay_x_us ( void )//(1+2)*60=180指令周期 180us
{
//	char x=60;
//	for ( ; x>0; x-- )
//		nop();
  delay_us_(179);
}       
                                                          
//函数名称： start_i2c
//函数功能： i2c 发送起始条件
//参数描述：
// 返 回 值：
void start_i2c ( void )
{
	SI7021_SDA_HIGH();  
	delay_x_us();
	SI7021_SCLK_HIGH();   
	delay_x_us();     
	SI7021_SDA_LOW();   
	delay_x_us(); 		
	SI7021_SCLK_LOW(); 
	delay_x_us();
}
//函数名称： stop_i2c
//函数功能： i2c 发送结束条件
//参数描述：
// 返 回 值：
void stop_i2c ( void )
{
	SI7021_SDA_LOW(); 
	delay_x_us();  
	SI7021_SCLK_HIGH(); 
	delay_x_us();
	SI7021_SDA_HIGH(); 
	delay_x_us();
}
//函数名称： send_1byte
//函数功能： 写一个字节到si7021芯片
//参数描述：
// 返 回 值：
u8 send_1byte ( unsigned char send_data )
{
	unsigned char bit_cnt;
	u8	b_ack=0;
	unsigned char i=200;
	
	for( bit_cnt=0; bit_cnt<8; bit_cnt++ ) 
	{ 
	     SI7021_SCLK_LOW(); 
	     if ( (send_data<<bit_cnt)&0x80 ) 
		 	SI7021_SDA_HIGH();  
	     else SI7021_SDA_LOW();  
		 delay_x_us();              
	     SI7021_SCLK_HIGH();       
	     delay_x_us();           
	}

	delay_x_us();
	SI7021_SCLK_LOW();
	SI7021_SDA_HIGH();        //
	delay_x_us();
	

	delay_x_us(); 
	SI7021_SCLK_HIGH();
	delay_x_us();
	 
	i = 200;
	while ( i-- )
	{
		delay_x_us();
		if(SI7021_SDA==0)
		{
			b_ack = 1;
			break;
		}  
	}

	if ( i == 0 ) b_ack = 0; 
	        
	SI7021_SCLK_LOW();
	delay_x_us ();

	return b_ack;
}

//函数名称： read_1byte
//函数功能： 从si7021读取一个字节
//参数描述：
// 返 回 值：
unsigned char read_1byte ( void )
{
	unsigned char read_value=0;
	unsigned char bit_cnt;

	for ( bit_cnt=0; bit_cnt<8; bit_cnt++ )
	{          
	     SI7021_SCLK_HIGH();       
	     delay_x_us();
		 read_value <<= 1;

	     if ( SI7021_SDA==1 ) 
		 	read_value +=1;

	     SI7021_SCLK_LOW();
	}
	return (read_value);
}
//函数名称：master_i2c_ack
//函数功能：MCU应答从器件
//参数描述：
// 返 回 值：
void master_i2c_ack ( void )
{
	SI7021_SDA_LOW();   
	delay_x_us();
	SI7021_SCLK_LOW();
	delay_x_us();      
	SI7021_SCLK_HIGH();
	delay_x_us();
	SI7021_SCLK_LOW();    
	delay_x_us(); 
	SI7021_SDA_HIGH();
	delay_x_us();
}
//函数名称：master_i2c_noack
//函数功能：MCU不发送应答信号到从器件
//参数描述：
// 返 回 值：
void master_i2c_noack ( void )
{
	SI7021_SDA_HIGH(); 
	delay_x_us();      
	SI7021_SCLK_HIGH();
	delay_x_us();
	SI7021_SCLK_LOW(); 
}
//函数名称：measure_si7021
//函数功能：HOLD MASTER模式下读取温湿度 
//参数描述：
// 返 回 值：
void measure_si7021 ( unsigned char model, union16 *value )
{
	int i;
	//发起始信号
	start_i2c();               
	if ( 0== send_1byte ( SALVE_ADDR ) )//写slave addr
	{
		value->uint = 0xAABB;
		return ;
	}

	if ( 0 == send_1byte( model ) )//measure cmd
	{
		value->uint = 0x1234;
		return ;
	}
	//默认湿度转换时间为10~12ms 温度 6~10ms  
#if(0)  
	i = 600;	//600*180=108ms	非准确延时
	while ( i-- )
		delay_x_us ();	//温湿度数据转换延时等待（延时参照手册，此处仅为测试）
#endif
        SystickCount=150;
        while(SystickCount);

	start_i2c ();			 	//重新发起始信号
	if ( 0==send_1byte(SALVE_ADDR+1) ) //读命令
	{
		value->uint = 0x3456;
		return ;
	}

	value->uchar[HSB] = read_1byte ();//读取温湿度的高位字节
	//mcu应答
	master_i2c_ack ();
	value->uchar[LSB] = read_1byte ();//读取温湿度的低位字节数据
	//mcu无应答
	master_i2c_noack ();
	
	//mcu应答->read_1byte()读取校验值->mcu无应答

	//发送停止位
//	value->uint = 0x7890;
	stop_i2c ();
        si7021_temp=(((u32)gv_si7021_value.temp.uint*17572)>>16)-4685;
        si7021_humi=(((u32)gv_si7021_value.humi.uint*125)>>16)-6;
}
si7021_value_ST gv_si7021_value;
void SI7021_GPIO_Config(void)
{ 
  GPIO_Init(SI7021_SCLK_GPIO, SI7021_SCLK_GPIO_PIN, GPIO_Mode_Out_OD_Low_Fast);
  GPIO_Init(SI7021_SDA_GPIO, SI7021_SDA_GPIO_PIN, GPIO_Mode_Out_OD_Low_Fast);
  SI7021_SCLK_HIGH();
  SI7021_SDA_HIGH();
}




















