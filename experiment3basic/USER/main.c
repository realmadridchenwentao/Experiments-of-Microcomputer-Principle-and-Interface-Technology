/***********************************************************************
实验名称：中断实验

硬件模块：计算机原理应用实验箱

硬件接线：ARM P10接口---------LED P2接口 	
		      ARM P12接口---------按键 P1接口	 
          GPIOB  接 LED
					GPIOC  接 数码管
		      GPIOF  接 按键
实验现象：
更新时间：2018-10-31
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
功  能：LED端口初始化
参  数：无
返回值：无
*******************************/
void LED_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);   //开启GPIOB的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************
功  能：数码管口初始化
参  数：无
返回值：无
*******************************/
void SMG_Configure(void)
{
		GPIO_InitTypeDef   GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);   //开启GPIOC的时钟
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;          //输出模式
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;         //推挽输出 
		GPIO_InitStructure.GPIO_Speed = GPIO_Medium_Speed;     
		GPIO_Init(GPIOC, &GPIO_InitStructure);
}



//Nested Vectored Interrupt Controller (NVIC)
/*******************************
功  能：中断端口初始化
参  数：无
返回值：无
*******************************/
void NVIC_Configure(void)
{
		GPIO_InitTypeDef   GPIO_TypeDefStructure;
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);   //开启GPIOF的时钟

		GPIO_TypeDefStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_11;
		GPIO_TypeDefStructure.GPIO_Mode = GPIO_Mode_IN;     //通用输入模式
		GPIO_TypeDefStructure.GPIO_PuPd = GPIO_PuPd_UP; 	  //上拉
		GPIO_Init(GPIOF, &GPIO_TypeDefStructure);
}


void EXTI8_Configure(void)
{
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
	
	  //中断线关联
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource8);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line8;                // GIPO第8位触发
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;   //下降沿触发
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXTI8_IRQn中断向量优先级设置
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI9_5_IRQn; 
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 0; // 优先级，数越小优先级越高
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}

void EXTI11_Configure(void)
{
		EXTI_InitTypeDef EXTI_TypeDefStructure;
		NVIC_InitTypeDef NVIC_TypeDefStructure;
	
		//开启外部中断时钟
		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	  //中断线关联
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOF, EXTI_PinSource11);
		
		EXTI_TypeDefStructure.EXTI_Line = EXTI_Line11;
		EXTI_TypeDefStructure.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_TypeDefStructure.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
		EXTI_TypeDefStructure.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_TypeDefStructure);
		
		//EXTI11_IRQn中断向量优先级设置
		NVIC_TypeDefStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
		NVIC_TypeDefStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_TypeDefStructure.NVIC_IRQChannelSubPriority = 7;
		NVIC_TypeDefStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_TypeDefStructure);
}




void SMG_SelectPos(int p3To8)
{
	HC138_C(0);  HC138_B(0);  HC138_A(1);   //  选择一位数码管显示
}


/*******************************
功  能：数码管口显示
参  数：无
返回值：无
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
		for(dj = 7; dj >= 0; dj--)         // 根据电路按照 .hgfedcba 输入进入
		{
			HC595_SI(NumLed[i][dj] - '0');   // 通过字符串 转换为0、1数字
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
功  能：外部中断服务函数
参  数：无
返回值：无
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
功  能：外部中断服务函数
参  数：无
返回值：无
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
  
	//开启外部中断时钟
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

