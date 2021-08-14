/*************************************************************
ʵ�����ƣ�����ܶ�̬ɨ��ʵ��

Ӳ��ģ�飺�����ԭ��Ӧ��ʵ����

Ӳ�����ߣ�ARM P12�ӿ�---------����� P4�ӿ� 
				PF0--------SI
				PF1--------RCK
				PF2--------SCK
				PF3--------A
				PF4--------B
				PF5--------C
         ע������20P����ֱ��P12��P4�ӿ�
					
ʵ���������������ʾ����0~7��

����ʱ�䣺2018-10-31
**************************************************************/
#include "stm32f4xx.h"
#include "delay.h"

#define  SMG_RCC_GPIO RCC_AHB1Periph_GPIOF
#define  SMG_GPIO     GPIOF

//74HC138
#define  HC138_A(val)   GPIO_WriteBit(SMG_GPIO, GPIO_Pin_3, (BitAction)val)
#define  HC138_B(val)   GPIO_WriteBit(SMG_GPIO, GPIO_Pin_4, (BitAction)val)
#define  HC138_C(val)   GPIO_WriteBit(SMG_GPIO, GPIO_Pin_5, (BitAction)val)

//74HC595
#define  HC595_SI(val)  GPIO_WriteBit(SMG_GPIO, GPIO_Pin_0, (BitAction)val)
#define  HC595_RCK(val) GPIO_WriteBit(SMG_GPIO, GPIO_Pin_1, (BitAction)val)
#define  HC595_SCK(val) GPIO_WriteBit(SMG_GPIO, GPIO_Pin_2, (BitAction)val)

/*******************************
��  �ܣ�����ܶ˿ڳ�ʼ��
��  ������
����ֵ����
*******************************/
void SMG_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(SMG_RCC_GPIO, ENABLE);       //����GPIOC��ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 
														| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       //���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�50MHz
	GPIO_Init(SMG_GPIO, &GPIO_InitStructure);
}

/*******************************
��  �ܣ�HC595��������
��  ����dat    ����
����ֵ����
*******************************/
void HC595_Send(uint8_t dat)
{
	uint8_t dat_buf = 0, i;
	for(i=0; i<8; i++)
	{
		dat_buf = dat & 0x80;
		if (dat_buf)      //���1bit����
		{
			HC595_SI(1);    //��74HC595��������������������Ϊ�ߵ�ƽ
		}
		else
		{
			HC595_SI(0);    //��74HC595��������������������Ϊ�͵�ƽ
		}
		HC595_SCK(0);
		Delay_Us(1);
		HC595_SCK(1);
		Delay_Us(1);
		dat <<= 1;
	}
	HC595_RCK(0);
	Delay_Us(3);
	HC595_RCK(1);
}



//��ʾ���������飬����Ϊ0,1,..,7
uint8_t digivalue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07}; 

/*******************************
��  �ܣ������λ�ο���
��  ����index   ��Ӧ�������
����ֵ����
*******************************/
void SMG_Sele(uint8_t index)
{
   HC595_Send(digivalue[index]); 	 
   switch(index)
   {
	  case 0: 
		  HC138_C(0);  HC138_B(0);  HC138_A(0);
		  break;
	   case 1: 
		  HC138_C(0);  HC138_B(0);  HC138_A(1);
		  break;
	   case 2: 
		  HC138_C(0);  HC138_B(1);  HC138_A(0);
		  break;
       case 3:
          HC138_C(0);  HC138_B(1);  HC138_A(1);	   
		  break;
	   case 4: 
		  HC138_C(1);  HC138_B(0);  HC138_A(0);
		  break;
	   case 5: 
		  HC138_C(1);  HC138_B(0);  HC138_A(1);
		  break;
	   case 6: 
		  HC138_C(1);  HC138_B(1);  HC138_A(0);
		  break;
	   case 7: 
		   HC138_C(1);  HC138_B(1);  HC138_A(1);
		   break;
	   default:
	        break;
   }  
}


int main(void)
{
	uint8_t i;
	Delay_Init();    //��ʱ��ʼ��
	SMG_Init();      //����ܳ�ʼ��
	while(1)
	{
		SMG_Sele(i);  //�������ʾ����
		i++;
		i &= 0x07;
	}
}

//end file



