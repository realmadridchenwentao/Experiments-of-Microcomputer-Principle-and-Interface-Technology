/*************************************************************
实验名称：数码管动态扫描实验

硬件模块：计算机原理应用实验箱

硬件接线：ARM P12接口---------数码管 P4接口 
				PF0--------SI
				PF1--------RCK
				PF2--------SCK
				PF3--------A
				PF4--------B
				PF5--------C
         注：可用20P排线直连P12、P4接口
					
实验现象：数码管上显示数字0~7。

更新时间：2018-10-31
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
功  能：数码管端口初始化
参  数：无
返回值：无
*******************************/
void SMG_Init(void)
{
	GPIO_InitTypeDef   GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(SMG_RCC_GPIO, ENABLE);       //开启GPIOC的时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 
														| GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;       //输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度50MHz
	GPIO_Init(SMG_GPIO, &GPIO_InitStructure);
}

/*******************************
功  能：HC595发送数据
参  数：dat    数据
返回值：无
*******************************/
void HC595_Send(uint8_t dat)
{
	uint8_t dat_buf = 0, i;
	for(i=0; i<8; i++)
	{
		dat_buf = dat & 0x80;
		if (dat_buf)      //输出1bit数据
		{
			HC595_SI(1);    //将74HC595串行数据输入引脚设置为高电平
		}
		else
		{
			HC595_SI(0);    //将74HC595串行数据输入引脚设置为低电平
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



//显示的数字数组，依次为0,1,..,7
uint8_t digivalue[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07}; 

/*******************************
功  能：数码管位段控制
参  数：index   对应的数码管
返回值：无
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
	Delay_Init();    //延时初始化
	SMG_Init();      //数码管初始化
	while(1)
	{
		SMG_Sele(i);  //数码管显示数据
		i++;
		i &= 0x07;
	}
}

//end file



