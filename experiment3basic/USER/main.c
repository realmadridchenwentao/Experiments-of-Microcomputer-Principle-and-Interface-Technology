/***********************************************************************
ʵ�����ƣ��ж�ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P10�ӿ�---------LED P2�ӿ� 	
		      ARM P12�ӿ�---------���� P1�ӿ�	 
          GPIOB  �� LED
					GPIOC  �� �����
		      GPIOF  �� ����
ʵ������
����ʱ�䣺2018-10-31
***********************************************************************/
#include "stm32f4xx.h"
#include "delay.h"
//74HC138
#define  HC138_A(val)   GPIO_WriteBit(GPIOC, GPIO_Pin_3, (BitAction)val)
#define  HC138_B(val)   GPIO_WriteBit(GPIOC, GPIO_Pin_4, (BitAction)val)
#define  HC138_C(val)   GPIO_WriteBit(GPIOC, GPIO_Pin_5, (BitAction)val)


//74HC595
#define  HC595_SI(val)  GPIO_WriteBit(GPIOC, GPIO_Pin_0, (BitAction)val)
#define  HC595_RCK(val) GPIO_WriteBit(GPIOC, GPIO_Pin_1, (BitAction)val)
#define  HC595_SCK(val) GPIO_WriteBit(GPIOC, GPIO_Pin_2, (BitAction)val)


/*******************************
��  �ܣ�LED�˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //����GPIOB��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************
��  �ܣ�����ܿڳ�ʼ��
��  ������
����ֵ����
*******************************/
void SMG_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //����GPIOC��ʱ��
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}



//Nested Vectored Interrupt Controller (NVIC)
/*******************************
��  �ܣ��ж϶˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void NVIC_Configure(void)
{
		GPIO_InitTypeDef   GPIO_TypeDefStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //����GPIOF��ʱ��

		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;     //ͨ������ģʽ
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //����
		GPIO_Init(GPIOF, &GPIO_TypeDefStructure);
}


void EXTI8_Configure(void)
{
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
	
	  //�ж��߹���
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line8;                // GIPO��8λ����
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //�½��ش���
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXTI8_IRQn�ж��������ȼ�����
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0; // ���ȼ�����ԽС���ȼ�Խ��
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}

void EXTI11_Configure(void)
{
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
	
		//�����ⲿ�ж�ʱ��
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	  //�ж��߹���
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line11;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXTI11_IRQn�ж��������ȼ�����
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}




void SMG_SelectPos(int p3To8)
{
	HC138_C(0);  HC138_B(0);  HC138_A(1);   //  ѡ��һλ�������ʾ
}


/*******************************
��  �ܣ�����ܿ���ʾ
��  ������
����ֵ����
*******************************/
void SMG_Display(void)
{
	int i = 0;
	int dj = 0;
	/*
	      a
	     ---
	  f| _g_ |b
	  e|     |c
	     --- 
        d  

	*/
	char NumLed[10][8] = {"11111100", "01100000", "11011010", "11110010", "01100110", 
												"10110110", "10111110", "11100000", "11111110","11110110"};
	//enum Digitron {a = 0, b, c, d, e, f, g, h};
	//enum Digitron dj;
	for(i = 0; i < 10; i++)   
	{
		for(dj = 7; dj >= 0; dj--)         // ���ݵ�·���� .hgfedcba �������
		{
			HC595_SI(NumLed[i][dj] - '0');   // ͨ���ַ��� ת��Ϊ0��1����
			HC595_SCK(0);
		  Delay_Us(1);
		  HC595_SCK(1);
		  Delay_Us(1);
		}
		HC595_RCK(0);
	  Delay_Us(3);
	  HC595_RCK(1);
		SMG_SelectPos(i);
		Delay_Ms(500);
	}
}

/*******************************
��  �ܣ��ⲿ�жϷ�����
��  ������
����ֵ����
*******************************/
void EXTI9_5_IRQHandler(void)  
{
	  if(EXTI_GetITStatus(EXTI_Line8))
    {
        if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_8) == 0)
        {
            SMG_Display();
					  EXTI_ClearITPendingBit(EXTI_Line8);
        }
    }
}

/*******************************
��  �ܣ��ⲿ�жϷ�����
��  ������
����ֵ����
*******************************/
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line11))
    {
        if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_11) == 0)
        {
					  SMG_Display();
            EXTI_ClearITPendingBit(EXTI_Line11);
        }
    }
}




int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  
	//�����ⲿ�ж�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);  
	EXTI8_Configure();
	EXTI11_Configure();

	Delay_Init(); 
	LED_Configure();
	SMG_Configure();
	NVIC_Configure();
	
	uint16_t LedSeq = 0x00;
	
	while(1)
  {
		
		GPIO_Write(GPIOB, LedSeq);
		
		//SMG_Display();
		LedSeq++;
		LedSeq = LedSeq & 0xFF;
		Delay_Ms(100);
		
  }
}

//end file

