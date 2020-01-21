#ifndef _HX711_H_
#define _HX711_H_
#define HX711_SCK_GPIO    GPIOB
#define HX711_SCK_PIN     GPIO_Pin_3
#define HX711_DATA_GPIO    GPIOB
#define HX711_DATA_PIN     GPIO_Pin_2
#define SET_SCK1 GPIO_SetBits(HX711_SCK_GPIO, HX711_SCK_PIN);
#define RESET_SCK1 GPIO_ResetBits(HX711_SCK_GPIO, HX711_SCK_PIN);
#define SET_B1  GPIO_SetBits(HX711_DATA_GPIO, HX711_DATA_PIN);
void hx711_init(void);
unsigned long HX711_Read(void);
#endif