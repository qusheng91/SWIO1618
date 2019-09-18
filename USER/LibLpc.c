#include "LibLpc.h"
#include "AppMain.h"

void lpc_init(void)
{	
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, DISABLE);//ʹ��GPIOA�͸��ù���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, DISABLE);//ʹ��GPIOA�͸��ù���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, DISABLE);//ʹ��GPIOA�͸��ù���ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, DISABLE);//ʹ��GPIOA�͸��ù���ʱ��
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������  
	GPIO_Init(GPIOA, &GPIO_InitStructure);	    //��ʼ��IO
    GPIO_Init(GPIOB, &GPIO_InitStructure);	    //��ʼ��IO
    GPIO_Init(GPIOC, &GPIO_InitStructure);	    //��ʼ��IO
    GPIO_Init(GPIOD, &GPIO_InitStructure);	    //��ʼ��IO
    GPIO_Init(GPIOE, &GPIO_InitStructure);	    //��ʼ��IO
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);//ʹ��GPIOA�͸��ù���ʱ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//PE.3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������  
	GPIO_Init(GPIOE, &GPIO_InitStructure);	    //��ʼ��IO
	
    //ʹ���ⲿ�жϷ�ʽ
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;                  //���ð������е��ⲿ��·
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//�����ⲿ�ж�ģʽ:EXTI��·Ϊ�ж�����
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //�����ش���
 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   // DISABLE;
	EXTI_Init(&EXTI_InitStructure);	                            //��ʼ���ⲿ�ж�

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
      
	TIM_Cmd(TIM2, DISABLE);  //ʹ��TIMx����	
    TIM_ITConfig(TIM2,TIM_IT_Update, DISABLE);                  //ʹ�ܻ���ʧ��ָ����TIM�ж�
    /*�����ж����ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;            //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                             //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);				    //FIFO0/1��Ϣ�Һ��ж�����.	
    CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);    
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
   
    PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);
    
    SystemInit();    
    sys_init();
    AppInit();
}

void EXTI1_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {   
        EXTI_ClearITPendingBit(EXTI_Line1);  /*����жϱ��*/
    }
}    
