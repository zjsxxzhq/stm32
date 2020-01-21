#include "define.h"




/*
1.判断是主机还是从机

主机->
判断是否输入有效
有效->启动主动发送模块开始发送
判断是否收到被动接收模块有数据
有数据->执行IO动作
从机_>
判断是否输入有效
有效->启动主动发送模块开始发送
判断是否收到被动接收模块有数据
有数据->执行IO动作
*/

void LoRaSetRFFrequency( uint32_t freq,u8 freset[] )
{

    freq = ( uint32_t )( ( double )freq / ( double )61.03515625 );
    freset[0] = ( uint8_t )( ( freq >> 16 ) & 0xFF );
    freset[1] = ( uint8_t )( ( freq >> 8 ) & 0xFF );
    freset[2] = ( uint8_t )( freq & 0xFF );
}
void kaiguan_do(void);
void kaiguan_do(void)
{
  
}

