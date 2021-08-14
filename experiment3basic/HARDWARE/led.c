#include "stm32f4xx.h"
#include "led.h"

/*******************************
功  能：LED端口初始化
参  数：无
返回值：无
*******************************/
/**
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(LED_RCC_GPIO, ENABLE);   //开启GPIOF的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(LED_GPIO, &GPIO_InitStructure);
}
*/
//end file
