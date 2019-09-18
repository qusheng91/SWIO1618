#include "LibLpc.h"
#include "AppMain.h"

void lpc_init(void)
{	
    GPIO_InitTypeDef  GPIO_InitStructure;  		  
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, DISABLE);//使能GPIOA和复用功能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, DISABLE);//使能GPIOA和复用功能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, DISABLE);//使能GPIOA和复用功能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, DISABLE);//使能GPIOA和复用功能时钟
   
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//上拉输入  
	GPIO_Init(GPIOA, &GPIO_InitStructure);	    //初始化IO
    GPIO_Init(GPIOB, &GPIO_InitStructure);	    //初始化IO
    GPIO_Init(GPIOC, &GPIO_InitStructure);	    //初始化IO
    GPIO_Init(GPIOD, &GPIO_InitStructure);	    //初始化IO
    GPIO_Init(GPIOE, &GPIO_InitStructure);	    //初始化IO
    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);//使能GPIOA和复用功能时
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	//PE.3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入  
	GPIO_Init(GPIOE, &GPIO_InitStructure);	    //初始化IO
	
    //使用外部中断方式
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;                  //设置按键所有的外部线路
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//设外外部中断模式:EXTI线路为中断请求
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;     //上升沿触发
 	EXTI_InitStructure.EXTI_LineCmd = ENABLE;                   // DISABLE;
	EXTI_Init(&EXTI_InitStructure);	                            //初始化外部中断

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn; //使能按键所在的外部中断通道
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;  
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //使能外部中断通道
	NVIC_Init(&NVIC_InitStructure); //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
      
	TIM_Cmd(TIM2, DISABLE);  //使能TIMx外设	
    TIM_ITConfig(TIM2,TIM_IT_Update, DISABLE);                  //使能或者失能指定的TIM中断
    /*配置中断优先级*/
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;             //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;          //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;            //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);                             //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
    
    CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);				    //FIFO0/1消息挂号中断允许.	
    CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);    
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;          // 次优先级为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;          // 次优先级为2
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
        EXTI_ClearITPendingBit(EXTI_Line1);  /*清除中断标记*/
    }
}    
