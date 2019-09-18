#include "LibTimer.h"
#include "LibVarDefine.h"

static void LibTimerChannelHandle(void);


__IO uint32_t timer_01_count = 0; 
__IO uint8_t timer_01_flag = 0;

__IO uint32_t timer_02_count = 0;
__IO uint8_t timer_02_flag = 0;

__IO uint32_t timer_03_count = 0;
__IO uint8_t timer_03_flag = 0;

__IO uint32_t timer_04_count = 0;
__IO uint8_t timer_04_flag = 0;

__IO uint32_t timer_05_count = 0;
__IO uint8_t timer_05_flag = 0;

__IO uint32_t timer_06_count = 0;
__IO uint8_t timer_06_flag = 0;

__IO uint32_t timer_07_count = 0;
__IO uint8_t timer_07_flag = 0;

__IO uint32_t timer_08_count = 0;
__IO uint8_t timer_08_flag = 0;

__IO uint32_t timer_09_count = 0;
__IO uint8_t timer_09_flag = 0;

__IO uint32_t timer_10_count = 0;
__IO uint8_t timer_10_flag = 0;


void LibTimerInit(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = 1000; 
	TIM_TimeBaseStructure.TIM_Prescaler =(72-1);   
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设							 
}

void TIM2_IRQHandler(void)
{
    /* 1ms */
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		LibTimerChannelHandle();
	}
}

void LibTimerSet(u8 channel, u32 ms)
{
    switch (channel)
    {
    case 1:
        timer_01_count = ms;
        timer_01_flag = 0;
        break;

    case 2:
        timer_02_count = ms;
        timer_02_flag = 0;
        break;

    case 3:
        timer_03_count = ms;
        timer_03_flag = 0;
        break;

    case 4:
        timer_04_count = ms;
        timer_04_flag = 0;
        break;

    case 5:
        timer_05_count = ms;
        timer_05_flag = 0;
        break;

    case 6:
        timer_06_count = ms;
        timer_06_flag = 0;
        break;

    case 7:
        timer_07_count = ms;
        timer_07_flag = 0;
        break;

    case 8:
        timer_08_count = ms;
        timer_08_flag = 0;
        break;

    case 9:
        timer_09_count = ms;
        timer_09_flag = 0;
        break;

    case 10:
        timer_10_count = ms;
        timer_10_flag = 0;
        break;

    default:
        break;
    }
}

u8 LibTimerGet(u8 channel, u32 *ms)
{
    uint8_t res = 0;
    
    switch (channel)
    {
    case 1:
        res = timer_01_flag; 
        *ms = timer_01_count;
        break;

    case 2:
        res = timer_02_flag; 
        *ms = timer_02_count;
        break;

    case 3:
        res = timer_03_flag; 
        *ms = timer_03_count;
        break;

    case 4:
        res = timer_04_flag; 
        *ms = timer_04_count;
        break;

    case 5:
        res = timer_05_flag; 
        *ms = timer_05_count;
        break;

    case 6:
        res = timer_06_flag; 
        *ms = timer_06_count;
        break;

    case 7:
        res = timer_07_flag; 
        *ms = timer_07_count;
        break;

    case 8:
        res = timer_08_flag; 
        *ms = timer_08_count;
        break;

    case 9:
        res = timer_09_flag; 
        *ms = timer_09_count;
        break;

    case 10:
        res = timer_10_flag; 
        *ms = timer_10_count;
        break;

    default:
        res = 0;
        break;
    }
    
    return res;
}

static void LibTimerChannelHandle(void)
{
    if (timer_01_count > 0 )
    {
        --timer_01_count;
        if (timer_01_count == 0)
        {
            timer_01_flag = 1;
        }
    }

    if (timer_02_count > 0 )
    {
        --timer_02_count;
        if (timer_02_count == 0)
        {
            timer_02_flag = 1;
        }
    }

    if (timer_03_count > 0 )
    {
        --timer_03_count;
        if (timer_03_count == 0)
        {
            timer_03_flag = 1;
        }
    }
    
    if (timer_04_count > 0 )
    {
        --timer_04_count;
        if (timer_04_count == 0)
        {
            timer_04_flag = 1;
        }
    }
    
    if (timer_05_count > 0 )
    {
        --timer_05_count;
        if (timer_05_count == 0)
        {
            timer_05_flag = 1;
        }
    }
    
    if (timer_06_count > 0 )
    {
        --timer_06_count;
        if (timer_06_count == 0)
        {
            timer_06_flag = 1;
        }
    }
    
    if (timer_07_count > 0 )
    {
        --timer_07_count;
        if (timer_07_count == 0)
        {
            timer_07_flag = 1;
        }
    }
    
    if (timer_08_count > 0 )
    {
        --timer_08_count;
        if (timer_08_count == 0)
        {
            timer_08_flag = 1;
        }
    }
    
    if (timer_09_count > 0 )
    {
        --timer_09_count;
        if (timer_09_count == 0)
        {
            timer_09_flag = 1;
        }
    }
    
    if (timer_10_count > 0 )
    {
        --timer_10_count;
        if (timer_10_count == 0)
        {
            timer_10_flag = 1;
        }
    }
}


