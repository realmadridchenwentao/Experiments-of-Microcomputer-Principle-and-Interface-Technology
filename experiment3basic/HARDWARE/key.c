#include "stm32f4xx.h"


/*******************************
��  �ܣ������˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void KEY_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //����GPIOF��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
  
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;           //����ģʽ
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;           //���� 
	  GPIO_Init(GPIOF, &GPIO_InitStructure);
}
