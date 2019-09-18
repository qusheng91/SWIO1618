#include "LibDI.h"

//DI初始化函数
void LibDIInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能GPIOA,B,C的时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_1;//GPIOA1,2,3,
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//调用初始化函数对GPIOA进行初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9;//GPIOB0,1,8,9
	GPIO_Init(GPIOB, &GPIO_InitStructure);//调用初始化函数对GPIOB进行初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//GPIOC0,1,2,3,4,5,13,14,15
	GPIO_Init(GPIOC, &GPIO_InitStructure);//调用初始化函数对GPIOC进行初始化
}

//获取DI端口值
//参数channal为通道号
//返回值为通道对应IO的结果
u8 LibGetValueDIH(u8 Channal)
{
	u8 DI_State;
	switch(Channal)
	{
		case 0:
			DI_State = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2);//读取相关IO的输入值
			if(DI_State == 1) return 0;
			else return 1;
		case 1:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1);
			if(DI_State == 1) return 0;
			else return 1;
		case 2:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0);
			if(DI_State == 1) return 0;
			else return 1;
		case 3:
			DI_State = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3);
			if(DI_State == 1) return 0;
			else return 1;
		case 4:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2);
			if(DI_State == 1) return 0;
			else return 1;
		case 5:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15);
			if(DI_State == 1) return 0;
			else return 1;
		case 6:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5);
			if(DI_State == 1) return 0;
			else return 1;
		case 7:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3);
			if(DI_State == 1) return 0;
			else return 1;
		case 8:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14);
			if(DI_State == 1) return 0;
			else return 1;
		case 9:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4);
			if(DI_State == 1) return 0;
			else return 1;
		case 10:
			DI_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0);
			if(DI_State == 1) return 0;
			else return 1;
		case 11:
			DI_State = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1);
			if(DI_State == 1) return 0;
			else return 1;
		case 12:
			DI_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
			if(DI_State == 1) return 0;
			else return 1;
		case 13:
			DI_State = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);
			if(DI_State == 1) return 0;
			else return 1;
		case 14:
			DI_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8);
			if(DI_State == 1) return 0;
			else return 1;
		case 15:
			DI_State = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
			if(DI_State == 1) return 0;
			else return 1;
 	}
	return 1;
}


