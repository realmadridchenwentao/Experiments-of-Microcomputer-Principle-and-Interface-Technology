#include "stm32f4xx.h"
#include "led.h"

/*******************************
��  �ܣ�LED�˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
/**
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(LED_RCC_GPIO, ENABLE);   //����GPIOF��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(LED_GPIO, &GPIO_InitStructure);
}
*/
//end file
