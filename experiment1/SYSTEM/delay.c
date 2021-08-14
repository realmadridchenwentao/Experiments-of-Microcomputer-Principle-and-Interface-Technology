#include "stm32f4xx.h"

static uint32_t fam_nus = 0;
static uint32_t fam_nms = 0;

/*******************************
功  能：延时初始化函数
参  数：无
返回值：无
*******************************/
void Delay_Init(void)
{
    //关闭计时、不触发中断、计数时钟为AHB/8
    SysTick->CTRL = 0x0;
    fam_nus = SystemCoreClock/8000000;
    fam_nms = fam_nus * 1000;
    SysTick->VAL = 0;
}

/*******************************
功  能：微秒延时
参  数：ctr  微秒
返回值：无
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
功  能：毫秒延时
参  数：ctr  毫秒
返回值：无
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

