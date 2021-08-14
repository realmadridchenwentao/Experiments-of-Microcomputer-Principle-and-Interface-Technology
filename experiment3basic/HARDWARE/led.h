#ifndef __LED_H
#define __LED_H
#include "sys.h"

//LED¶Ë¿Ú
#define LED_RCC_GPIO RCC_AHB1Periph_GPIOC
#define LED_GPIO     GPIOC
#define LED1(val)    GPIO_WriteBit(LED_GPIO, GPIO_Pin_0, (BitAction)val)
#define LED1_DATA()  GPIO_ReadOutputDataBit(LED_GPIO, GPIO_Pin_0)

void LED_Configure(void);

#endif
