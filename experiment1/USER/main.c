/*************************************************************
实验名称：LED流水灯实验

硬件模块：计算机原理应用实验箱

硬件接线：ARM P12接口---------LED P2接口
           PF0~PF7----------LED1~LED8
		     注：可使用20P排线直连P12、P2接口。
		   
实验现象：通过数据移位操作，LED1~LED8实现流水灯效果。

更新时间：2018-09-21
**************************************************************/
#include "stm32f4xx.h"
#include "delay.h"

int main(void)
{
	uint8_t  cont = 0;
	uint16_t led_data = 0;
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //开启GPIOF的时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     //速率25MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);


	GPIO_Write(GPIOF, 0x00FF);

	Delay_Init();       //延时初始化 
	
    while(1)
    {
		led_data = cont;         
		GPIO_Write(GPIOF, led_data); 
		Delay_Ms(500);
		cont++;
		cont &= 0x07;    //大于7后清零
    }
}





