#include "define.h"




/*
1.�ж����������Ǵӻ�

����->
�ж��Ƿ�������Ч
��Ч->������������ģ�鿪ʼ����
�ж��Ƿ��յ���������ģ��������
������->ִ��IO����
�ӻ�_>
�ж��Ƿ�������Ч
��Ч->������������ģ�鿪ʼ����
�ж��Ƿ��յ���������ģ��������
������->ִ��IO����
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

