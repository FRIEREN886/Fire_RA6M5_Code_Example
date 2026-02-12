#include "FSP_Systick.h"

static  uint32_t FSP_Systick_period;//中断周期
static volatile uint32_t FSP_Delay_Nums; //延迟需要触发中断的次数

void FSP_Systick_Init(uint32_t FSP_Systick_Frequency)
{
    FSP_Systick_period = SystemCoreClock / FSP_Systick_Frequency;
    SysTick_Config(FSP_Systick_period);
}

void FSP_Delay_Systick(uint32_t FSP_Delay_time,sys_delay_units_t uint)
{
    uint32_t Sum_Time = FSP_Delay_time * uint;
    FSP_Delay_Nums = Sum_Time/FSP_Systick_period;
    SysTick->VAL = 0UL;//计数清零 
    while(FSP_Delay_Nums != 0);
    
}

extern void SysTick_Handler();

void SysTick_Handler()
{
    if(FSP_Delay_Nums != 0)
    {
        FSP_Delay_Nums--;
    }
}
