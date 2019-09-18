#include "LibWatchDog.h"
#include "led.h"
#include "delay.h"

//���Ź���ʼ������
//����Ϊ���ʱ������ ��λΪMS
//�����������ʱ��Ϊ6553.6ms��������ʱ��Ϊ1.6ms
//����ֵΪ1ʱ����ʾ���ô������ʱ�䲻���Ϲ涨
//Ϊ0ʱ����ʼ���ɹ�
u8 LibWatchDogInit(u16 OverflowTimeMS)
{
	u16 rlr;
	if(OverflowTimeMS > 6553 || OverflowTimeMS < 2)
		return 1;
	rlr = OverflowTimeMS * 40 / 64;
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(4);
	
	IWDG_SetReload(rlr);
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
	
	return 0;
}

//ι������
void LibWatchDogFeed(void)
{
	LED = ~LED;
	delay_ms(100);
	IWDG_ReloadCounter();//reload
}
