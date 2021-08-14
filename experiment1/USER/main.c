/*************************************************************
ʵ�����ƣ�LED��ˮ��ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P12�ӿ�---------LED P2�ӿ�
           PF0~PF7----------LED1~LED8
		     ע����ʹ��20P����ֱ��P12��P2�ӿڡ�
		   
ʵ������ͨ��������λ������LED1~LED8ʵ����ˮ��Ч����

����ʱ�䣺2018-09-21
**************************************************************/
#include "stm32f4xx.h"
#include "delay.h"

int main(void)
{
	uint8_t  cont = 0;
	uint16_t led_data = 0;
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //����GPIOF��ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     //����25MHz
	GPIO_Init(GPIOF, &GPIO_InitStructure);


	GPIO_Write(GPIOF, 0x00FF);

	Delay_Init();       //��ʱ��ʼ�� 
	
    while(1)
    {
		led_data = cont;         
		GPIO_Write(GPIOF, led_data); 
		Delay_Ms(500);
		cont++;
		cont &= 0x07;    //����7������
    }
}





