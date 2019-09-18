#include "LibDO.h"
#include "LibVarDefine.h"

//初始化函数
//将DO对应IO口全部初始化
void LibDOInit(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能GPIOA,B,C,D的时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_15;//GPIOA8,15,
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);//调用初始化函数对GPIOA进行初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_14|GPIO_Pin_15;//GPIOB4,5,6,7,10,11,14,15
	GPIO_Init(GPIOB, &GPIO_InitStructure);//调用初始化函数对GPIOB进行初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//GPIOC6,7,8,9,10,11,12
	GPIO_Init(GPIOC, &GPIO_InitStructure);//调用初始化函数对GPIOC进行初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//GPIOD2
	GPIO_Init(GPIOD, &GPIO_InitStructure);//调用初始化函数对GPIOD进行初始化
}

//设置DO值函数
//返回值为设置结果：0为设置失败，1为设置成功。
u8 LibSetValueDOH(u8 Channal, u8 Data)
{
	if(Channal > 17)
	{
		return 0;
	}

    if ((Data != 0) || (Data != 1))
    {
        return 0;
    }
    
	switch(Channal)
	{
		case 0:
			PBout(7) = Data;
			DO_State[0] = Data;
			break;
		case 1:
			PBout(6) = Data;
			DO_State[1] = Data;
			break;
		case 2:
			PBout(5) = Data;
			DO_State[2] = Data;
			break;
		case 3:
			PBout(4) = Data;
			DO_State[3] = Data;
			break;
		case 4:
			PDout(2) = Data;
			DO_State[4] = Data;
			break;
		case 5:
			PCout(12) = Data;
			DO_State[5] = Data;
			break;
		case 6:
			PCout(11) = Data;
			DO_State[6] = Data;
			break;
		case 7:
			PCout(10) = Data;
			DO_State[7] = Data;
			break;
		case 8:
			PAout(15) = Data;
			DO_State[8] = Data;
			break;
		case 9:
			PAout(8) = Data;
			DO_State[9] = Data;
			break;
		case 10:
			PCout(9) = Data;
			DO_State[10] = Data;
			break;
		case 11:
			PCout(8) = Data;
			DO_State[11] = Data;
			break;
		case 12:
			PCout(7) = Data;
			DO_State[12] = Data;
			break;
		case 13:
			PCout(6) = Data;
			DO_State[13] = Data;
			break;
		case 14:
			PBout(15) = Data;
			DO_State[14] = Data;
			break;
		case 15:
			PBout(14) = Data;
			DO_State[15] = Data;
			break;
		case 16:
			PBout(10) = Data;
			DO_State[16] = Data;
			break;
		case 17:
			PBout(11) = Data;
			DO_State[17] = Data;
			break;
	}
	return 1;
}

u8 LibGetValueDOH(u8 Channal)
{
	return DO_State[Channal];
}
