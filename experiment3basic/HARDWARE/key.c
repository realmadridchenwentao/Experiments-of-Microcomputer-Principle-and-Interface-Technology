#include "stm32f4xx.h"


/*******************************
功  能：按键端口初始化
参  数：无
返回值：无
*******************************/
void KEY_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //开启GPIOF的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           //输入模式
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           //上拉 
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
}
