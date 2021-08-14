#include "stm32f4xx.h"

static uint32_t fam_nus = 0;
static uint32_t fam_nms = 0;

/*******************************
��  �ܣ���ʱ��ʼ������
��  ������
����ֵ����
*******************************/
void Delay_Init(void)
{
    //�رռ�ʱ���������жϡ�����ʱ��ΪAHB/8
    SysTick->CTRL = 0x0;
    fam_nus = SystemCoreClock/8000000;
    fam_nms = fam_nus * 1000;
    SysTick->VAL = 0;
}

/*******************************
��  �ܣ�΢����ʱ
��  ����ctr  ΢��
����ֵ����
*******************************/
void Delay_Us(uint16_t ctr)
{
    uint32_t Tick_Flag = 0;
    
    SysTick->LOAD = ctr*fam_nus;
    SysTick->VAL = 0;
    SysTick->CTRL |= 0x01;
    do
    {
        Tick_Flag = SysTick->CTRL;
    }
    while(!(Tick_Flag&(1<<16)) && (Tick_Flag&0x01));
    SysTick->CTRL = 0x00;
}


/*******************************
��  �ܣ�������ʱ
��  ����ctr  ����
����ֵ����
*******************************/
void Delay_Ms(uint16_t ctr)
{
    uint32_t Tick_Flag = 0;
    
    SysTick->LOAD = ctr * fam_nms;
    SysTick->VAL = 0;
    SysTick->CTRL = 0x01;
    do
    {
        Tick_Flag = SysTick->CTRL;
    }
    while(!(Tick_Flag & (1<<16)) && (Tick_Flag & 0x01));
    SysTick->CTRL = 0x00;
}

