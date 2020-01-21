#include "stm8l15x.h"
#include "define.h"



void shuzi2str(u16 value,u8 str[])
{
  if(value<10)
  {
    str[0]=value+'0';
    str[1]=0;
  }
  else if(value<100)
  {
    str[0]=(value/10)+'0';
    str[1]=(value%10)+'0';
    str[2]=0;    
  }
  else if(value<1000)
  {
    str[0]=(value/100)+'0';
    str[1]=((value/10)%10)+'0';
    str[2]=(value%10)+'0';
    str[3]=0;    
  }
}