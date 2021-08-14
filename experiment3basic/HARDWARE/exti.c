#include "stm32f4xx.h"
#include "led.h"

/*******************************
��  �ܣ��ⲿ�ж�����
��  ������
����ֵ����
*******************************/
void EXTI_Configure(void)
{
		GPIO_InitTypeDef GPIO_TypeDefStructure;
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
		
		//�����ж�����˿�ʱ��
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
		
		//�����ⲿ�ж�ʱ��
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
		//KEY_UP for EXTI in Pin
		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_8;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;   	//ͨ������ģʽ
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //����
		GPIO_Init(GPIOF, &GPIO_TypeDefStructure);

		//�ж��߹���
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line8;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXTI2_IRQn�ж��������ȼ�����
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}


//endfile
