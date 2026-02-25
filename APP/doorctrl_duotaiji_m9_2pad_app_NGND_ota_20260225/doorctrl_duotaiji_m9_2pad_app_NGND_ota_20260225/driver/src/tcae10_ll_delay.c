/**
  ******************************************************************************
  * @brief  Delay source file
  *
  * @file   delay.c
  * @author AE/FAE team
  * @date
  ******************************************************************************
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, TINYCHIP SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <b>&copy; Copyright (c) 2020 Tinychip Microelectronics Co.,Ltd.</b>
  *
  ******************************************************************************
  */
  
  
  
#include "tcae10_ll_delay.h"
#include "system_tcae10.h"


extern uint32_t SystemCoreClock;


void ll_systick_clkconfig(uint32_t source)
{
    if (source == SysTick_CLKSource_HCLK)
    {
        SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
    }
    else
    {
        SysTick->CTRL &= ~SysTick_CTRL_CLKSOURCE_Msk;
    }
}

void delay1ms(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL  = 0;
        u32end = 0x1000000 - SystemCoreClock/1000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

void delay1ms32K(uint32_t u32Cnt)
{
    int32_t temp;
    SysTick->LOAD=(int32_t)u32Cnt*32;
    SysTick->VAL =0x00;
    SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;
    {
        temp=SysTick->CTRL;
    }
    while(temp&0x01&&!(temp&(1<<16)));
    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL =0X00;

}


void delay100us(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/10000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}

void delay1us(uint32_t u32Cnt)
{
    uint32_t u32end;

    SysTick->LOAD = 0xFFFFFF;
    SysTick->VAL  = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk;

    while(u32Cnt-- > 0)
    {
        SysTick->VAL = 0;

        u32end = 0x1000000 - SystemCoreClock/1000000;
        while(SysTick->VAL > u32end)
        {
            ;
        }
    }

    SysTick->CTRL = (SysTick->CTRL & (~SysTick_CTRL_ENABLE_Msk));
}
