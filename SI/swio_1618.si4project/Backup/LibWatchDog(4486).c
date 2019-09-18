#include "LibWatchDog.h"
#include "led.h"
#include "delay.h"

//看门狗初始化函数
//参数为溢出时间设置 单位为MS
//最大可设置溢出时间为6553.6ms，最短溢出时间为1.6ms
//返回值为1时，表示设置错误，溢出时间不符合规定
//为0时，初始化成功
u8 LibWatchDogInit(u16 OverflowTimeMS)
{
	u16 rlr;
	if(OverflowTimeMS > 6553 || OverflowTimeMS < 2)
		return 1;
	rlr = OverflowTimeMS * 40 / 64;
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(4);
	
	IWDG_SetReload(rlr);
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
	
	return 0;
}

//喂狗函数
void LibWatchDogFeed(void)
{
	LED = ~LED;
	delay_ms(100);
	IWDG_ReloadCounter();//reload
}
