#include "LibTimer.h"
#include "LibVarDefine.h"

void LibTimer1Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIMx外设							 
}

void LibTimer2Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM2, ENABLE);  //使能TIMx外设							 
}

void LibTimer3Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设							 
}

void LibTimer4Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  //使能TIMx外设							 
}

void LibTimer5Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM5, ENABLE);  //使能TIMx外设							 
}

void LibTimer6Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);  //使能//使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM6, ENABLE);  //使能TIMx外设							 
}

void LibTimer7Init(u16 Period)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = Period; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到N*10为Nms
	TIM_TimeBaseStructure.TIM_Prescaler =(7200-1); //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	TIM_ITConfig(TIM7,TIM_IT_Update,ENABLE);  //使能或者失能指定的TIM中断

	/*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM7, ENABLE);  //使能TIMx外设							 
}

void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		if(LibVarTimerMode[0] == 0)
		{
			LibVarTimerUpdateFlag[0] = 1;
		}
		else if(LibVarTimerMode[0] == 1)
		{
			LibVarTimerCounter[0]++;
			if(LibVarTimerCounter[0] * 500 == LibVarTimerTime[0])
			{
				LibVarTimerUpdateFlag[0] = 1;
				LibVarTimerCounter[0] = 0;
			}
		}
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		if(LibVarTimerMode[1] == 0)
		{
			LibVarTimerUpdateFlag[1] = 1;
		}
		else if(LibVarTimerMode[1] == 1)
		{
			LibVarTimerCounter[1]++;
			if(LibVarTimerCounter[1] * 500 == LibVarTimerTime[1])
			{
				LibVarTimerUpdateFlag[1] = 1;
				LibVarTimerCounter[1] = 0;
			}
		}
	}
}

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		if(LibVarTimerMode[2] == 0)
		{
			LibVarTimerUpdateFlag[2] = 1;
		}
		else if(LibVarTimerMode[2] == 1)
		{
			LibVarTimerCounter[2]++;
			if(LibVarTimerCounter[2] * 500 == LibVarTimerTime[2])
			{
				LibVarTimerUpdateFlag[2] = 1;
				LibVarTimerCounter[2] = 0;
			}
		}
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		if(LibVarTimerMode[3] == 0)
		{
			LibVarTimerUpdateFlag[3] = 1;
		}
		else if(LibVarTimerMode[3] == 1)
		{
			LibVarTimerCounter[3]++;
			if(LibVarTimerCounter[3] * 500 == LibVarTimerTime[3])
			{
				LibVarTimerUpdateFlag[3] = 1;
				LibVarTimerCounter[3] = 0;
			}
		}
	}
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		if(LibVarTimerMode[4] == 0)
		{
			LibVarTimerUpdateFlag[4] = 1;
		}
		else if(LibVarTimerMode[4] == 1)
		{
			LibVarTimerCounter[4]++;
			if(LibVarTimerCounter[4] * 500 == LibVarTimerTime[4])
			{
				LibVarTimerUpdateFlag[4] = 1;
				LibVarTimerCounter[4] = 0;
			}
		}
	}
}

void TIM6_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
		if(LibVarTimerMode[5] == 0)
		{
			LibVarTimerUpdateFlag[5] = 1;
		}
		else if(LibVarTimerMode[5] == 1)
		{
			LibVarTimerCounter[5]++;
			if(LibVarTimerCounter[5] * 500 == LibVarTimerTime[5])
			{
				LibVarTimerUpdateFlag[5] = 1;
				LibVarTimerCounter[5] = 0;
			}
		}
	}
}

void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
		if(LibVarTimerMode[6] == 0)
		{
			LibVarTimerUpdateFlag[6] = 1;
		}
		else if(LibVarTimerMode[6] == 1)
		{
			LibVarTimerCounter[6]++;
			if(LibVarTimerCounter[6] * 500 == LibVarTimerTime[6])
			{
				LibVarTimerUpdateFlag[6] = 1;
				LibVarTimerCounter[6] = 0;
			}
		}
	}
}

void LibTimerInit(u8 Channal,u32 Time)
{
	LibVarTimerTime[Channal - 1] = Time;
	switch(Channal)
	{
		case 1:
			if(Time < 5000)
			{
				LibTimer1Init(Time*10);
				LibVarTimerMode[0] = 0;
			}
			else
			{
				LibTimer1Init(4999);
				LibVarTimerMode[0] = 1;
			}
			break;
		case 2:
			if(Time < 5000)
			{
				LibTimer2Init(Time*10);
				LibVarTimerMode[1] = 0;
			}
			else
			{
				LibTimer2Init(4999);
				LibVarTimerMode[1] = 1;
			}
			break;
		case 3:
			if(Time < 5000)
			{
				LibTimer3Init(Time*10);
				LibVarTimerMode[2] = 0;
			}
			else
			{
				LibTimer3Init(4999);
				LibVarTimerMode[2] = 1;
			}
			break;
		case 4:
			if(Time < 5000)
			{
				LibTimer4Init(Time*10);
				LibVarTimerMode[3] = 0;
			}
			else
			{
				LibTimer4Init(4999);
				LibVarTimerMode[3] = 1;
			}
			break;
		case 5:
			if(Time < 5000)
			{
				LibTimer5Init(Time*10);
				LibVarTimerMode[4] = 0;
			}
			else
			{
				LibTimer5Init(4999);
				LibVarTimerMode[4] = 1;
			}
			break;
		case 6:
			if(Time < 5000)
			{
				LibTimer6Init(Time*10);
				LibVarTimerMode[5] = 0;
			}
			else
			{
				LibTimer6Init(4999);
				LibVarTimerMode[5] = 1;
			}
			break;
		case 7:
			if(Time < 5000)
			{
				LibTimer7Init(Time*10);
				LibVarTimerMode[6] = 0;
			}
			else
			{
				LibTimer7Init(4999);
				LibVarTimerMode[6] = 1;
			}
			break;
	}
}

//获取定时器状态函数
//参数为对应的定时器：1-7
//返回值为1时，表示定时器已经溢出，返回值为0时，定时器仍在计数
//当没有调用过定时器读取函数，但是已经开启定时器且定时器达到设定时间时，
//第一个返回的状态值一定是1（不管此时定时器是否溢出）；
u8 LibTimer(u8 Channal)
{
	if(LibVarTimerUpdateFlag[Channal-1] == 1)
	{
		LibVarTimerUpdateFlag[Channal-1] = 0;
		return 1;
	}
	else
		return 0;
}
