#ifndef	_SI7021_H
#define	_SI7021_H

#include "stm8l15x.h"
typedef	union union16_{
	u16 uint;
	u8 uchar[2];
}union16;
typedef union union32_{
	long _long;
	u16 uint[2];
	u8 uchar[4];
}union32;

#define	HSB	0
#define	LSB	1

#define	BIT_HIGH 	1
#define	BIT_LOW		0

typedef	struct _si7021_value_{
	union16 temp;
	union16 humi;
	unsigned char crc;
}si7021_value_ST, *p_si7021_value_ST;
//sbit	SI7021_SCLK	=	P3^4;
//sbit	SI7021_SDA	=	P3^3;
//sbit	SI7021_SCLK	=	P1^0;
//sbit	SI7021_SDA	=	P1^1;

#define	WRITE_CMD		0x80
#define	READ_CDM		0x81
#define	SALVE_ADDR		0x80

#define	HUMI_HOLD_MASTER	0xE5
#define	TEMP_HOLD_MASTER	0xE3
		
#define	HUMI_NOHOLD_MASTER	0xF5
#define	TEMP_NOHOLD_MASTER	0xF3

#define SI7021_SCLK_GPIO        GPIOC
#define SI7021_SCLK_GPIO_PIN    GPIO_Pin_0
#define SI7021_SDA_GPIO        GPIOC
#define SI7021_SDA_GPIO_PIN    GPIO_Pin_1
 

#define	SI7021_SCLK_HIGH()	SI7021_SCLK_GPIO->ODR |= SI7021_SCLK_GPIO_PIN
#define	SI7021_SCLK_LOW()	SI7021_SCLK_GPIO->ODR &= (uint8_t)(~SI7021_SCLK_GPIO_PIN)

#define	SI7021_SDA_HIGH()	SI7021_SDA_GPIO->ODR |= SI7021_SDA_GPIO_PIN
#define	SI7021_SDA_LOW()	SI7021_SDA_GPIO->ODR &= (uint8_t)(~SI7021_SDA_GPIO_PIN)

#define SI7021_SDA              (SI7021_SDA_GPIO->IDR & SI7021_SDA_GPIO_PIN)==SI7021_SDA_GPIO_PIN
void measure_si7021 ( unsigned char model, union16 *value );
void SI7021_GPIO_Config(void);
extern si7021_value_ST gv_si7021_value;
extern s16 si7021_temp;
extern u16 si7021_humi;
#endif//ifndef	_SI7021_H













