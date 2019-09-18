#include "LibCAN.h"
#include "LibVarDefine.h"
#include "LibUsart.h"	


//CAN1初始化函数
u8 CAN1_Mode_Init(u16 bps)
{ 
	u8 Flag=0;
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	NVIC_InitTypeDef  		NVIC_InitStructure;

	//GPIO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;	                //PA11:CAN-RX 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	    //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	//PA12:CAN-TX 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	//Mode
	CAN_InitStructure.CAN_TTCM=DISABLE;			//非时间触发通信模式  
	CAN_InitStructure.CAN_ABOM=ENABLE;			//软件自动离线管理	 
	CAN_InitStructure.CAN_AWUM=DISABLE;			//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART=ENABLE;			//禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	//报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP=DISABLE;			//优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	        //模式设置： mode:0,普通模式;1,回环模式; 
	//设置波特率
	switch(bps)
	{
		case 10:
			CAN_InitStructure.CAN_SJW=1;				//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 			//Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				//Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~	CAN_BS2_8tq
			CAN_InitStructure.CAN_Prescaler=300;        //分频系数(Fdiv)为brp+1	
		break;
		case 20:
			CAN_InitStructure.CAN_SJW=1;			
			CAN_InitStructure.CAN_BS1=CAN_BS1_8tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;	
			CAN_InitStructure.CAN_Prescaler=180;     
		break;
		case 50:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=60;     
		break;
		case 100:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=20;     
		break;
		case 125:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=16;     
		break;
		case 250:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=8;     
		break;
		case 500:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=4;     
		break;
		case 1000:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=2;     
		break;
	}
	Flag = CAN_Init(CAN1, &CAN_InitStructure);        	//初始化CAN1 
	while(CAN_InitStatus_Success!=Flag)
	{
		Flag = CAN_Init(CAN1, &CAN_InitStructure);        	//初始化CAN1 
	}
	CAN_ITConfig(CAN1,CAN_IT_FMP0|CAN_IT_FMP1,ENABLE);				//FIFO0/1消息挂号中断允许.		    

	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // 次优先级为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // 次优先级为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	return 0;
}

//CAN2初始化函数
u8 CAN2_Mode_Init(u16 bps)
{ 
	u8 Flag=0;
	GPIO_InitTypeDef 		GPIO_InitStructure; 
	CAN_InitTypeDef        	CAN_InitStructure;
	NVIC_InitTypeDef  		NVIC_InitStructure;

	//GPIO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	                //PB12:CAN-RX 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	    //
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;	//PB13:CAN-TX 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	//Mode
	CAN_InitStructure.CAN_TTCM=DISABLE;			//非时间触发通信模式  
	CAN_InitStructure.CAN_ABOM=ENABLE;			//软件自动离线管理	 
	CAN_InitStructure.CAN_AWUM=DISABLE;			//睡眠模式通过软件唤醒(清除CAN->MCR的SLEEP位)
	CAN_InitStructure.CAN_NART=ENABLE;			//禁止报文自动传送 
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	//报文不锁定,新的覆盖旧的  
	CAN_InitStructure.CAN_TXFP=DISABLE;			//优先级由报文标识符决定 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	        //模式设置： mode:0,普通模式;1,回环模式; 
	//设置波特率
	switch(bps)
	{
		case 10:
			CAN_InitStructure.CAN_SJW=1;				//重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 			//Tbs1=tbs1+1个时间单位CAN_BS1_1tq ~CAN_BS1_16tq
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				//Tbs2=tbs2+1个时间单位CAN_BS2_1tq ~	CAN_BS2_8tq
			CAN_InitStructure.CAN_Prescaler=300;        //分频系数(Fdiv)为brp+1	
		break;
		case 20:
			CAN_InitStructure.CAN_SJW=1;			
			CAN_InitStructure.CAN_BS1=CAN_BS1_8tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;	
			CAN_InitStructure.CAN_Prescaler=180;     
		break;
		case 50:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=60;     
		break;
		case 100:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=20;     
		break;
		case 125:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=16;     
		break;
		case 250:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=8;     
		break;
		case 500:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=4;     
		break;
		case 1000:
			CAN_InitStructure.CAN_SJW=1;				
			CAN_InitStructure.CAN_BS1=CAN_BS1_16tq; 		
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				
			CAN_InitStructure.CAN_Prescaler=2;     
		break;
	}
	Flag = CAN_Init(CAN2, &CAN_InitStructure);        	//初始化CAN1 
	while(CAN_InitStatus_Success!=Flag)
	{
		Flag = CAN_Init(CAN2, &CAN_InitStructure);        	//初始化CAN1 
	}
	CAN_ITConfig(CAN2,CAN_IT_FMP0|CAN_IT_FMP1,ENABLE);				//FIFO0/1消息挂号中断允许.		    

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // 次优先级为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // 主优先级为2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // 次优先级为2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	return 0;
}

void CAN1_RX0_IRQHandler(void)
{
	u8 i = 0,j = 0;
	CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP0) != RESET)
	{
		CAN_Receive(CAN1, 0, &RxMessage);
	}
	while(RxMessage.StdId != LibVarCan1ReceiveTargetID[i])
		i++;
	LibVarCan1ReceiveFlag[i] = 1;
	for(j = 0;j < 8;j++)
	{
		LibVarCan1ReceiveData[i][j] = RxMessage.Data[j];
	}
	LibVarCan1ReceiveLength[i] = RxMessage.DLC;
}

void CAN1_RX1_IRQHandler(void)
{
	u8 i = 0,j = 0;
	CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN1,CAN_IT_FMP1) != RESET)
	{
		CAN_Receive(CAN1, 1, &RxMessage);
	}
	while(RxMessage.ExtId != LibVarCan1ReceiveTargetID[i])
		i++;
	LibVarCan1ReceiveFlag[i] = 1;
	for(j = 0;j < 8;j++)
	{
		LibVarCan1ReceiveData[i][j] = RxMessage.Data[j];
	}
	LibVarCan1ReceiveLength[i] = RxMessage.DLC;
}

void CAN2_RX0_IRQHandler(void)
{
	u8 i = 0,j = 0;
	CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP0) != RESET)
	{
		CAN_Receive(CAN2, 0, &RxMessage);
	}
	while(RxMessage.StdId != LibVarCan2ReceiveTargetID[i])
	{
		i++;
	  if (i > 15) return;
	}
	
	LibVarCan2ReceiveFlag[i] = 1;
	for(j = 0;j < 8;j++)
	{
		LibVarCan2ReceiveData[i][j] = RxMessage.Data[j];
	}
	LibVarCan2ReceiveLength[i] = RxMessage.DLC;
}

void CAN2_RX1_IRQHandler(void)
{
	u8 i = 0,j = 0;
	CanRxMsg RxMessage;
	if(CAN_GetITStatus(CAN2,CAN_IT_FMP1) != RESET)
	{
		CAN_Receive(CAN2, 1, &RxMessage);
	}
	while(RxMessage.ExtId != LibVarCan2ReceiveTargetID[i])
	{
		i++;
		if (i > 15) return;
	}
	LibVarCan2ReceiveFlag[i] = 1;
	for(j = 0;j < 8;j++)
	{
		LibVarCan2ReceiveData[i][j] = RxMessage.Data[j];
	}
	LibVarCan2ReceiveLength[i] = RxMessage.DLC;
}

//设置CAN接收buffer函数
//bufferID范围为0~27
//FrameEx:0为标准帧，1为扩展帧
//FrameID为需要接收的目标ID
//返回值为0时，设置成功；返回值为1时，设置失败
void LibCan1SetRecMode(u16 BufferID,u16 FrameEx,u32 FrameID)
{
	if(BufferID < 14)
	{
		CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
		if(FrameEx)
		{
			LibVarCan1BufferMode[BufferID] = 2; 
			LibVarCan1ReceiveTargetID[BufferID] = FrameID;
			FrameID = FrameID & (u32)0x1FFFFFFF;
			CAN_FilterInitStructure.CAN_FilterNumber = BufferID;	//过滤器0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32位宽 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<3)&0xFFFF0000)>>16;	//32位ID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32位MASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=1;//过滤器0关联到FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//激活过滤器0
			CAN_FilterInit(&CAN_FilterInitStructure);			//滤波器初始化
		}
		else
		{
			LibVarCan1BufferMode[BufferID] = 1; 
			LibVarCan1ReceiveTargetID[BufferID] = FrameID;
			FrameID = FrameID & (u32)0x000007FF;
			CAN_FilterInitStructure.CAN_FilterNumber = BufferID;	//过滤器0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32位宽 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<21)&0xFFFF0000)>>16;	//32位ID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32位MASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//过滤器0关联到FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//激活过滤器0
			CAN_FilterInit(&CAN_FilterInitStructure);			//滤波器初始化
		}
	}
}

//设置CAN接收buffer函数
//bufferID范围为0~27
//FrameEx:0为标准帧，1为扩展帧
//FrameID为需要接收的目标ID
//返回值为0时，设置成功；返回值为1时，设置失败
void LibCan2SetRecMode(u16 BufferID,u16 FrameEx,u32 FrameID)
{
	if(BufferID < 14)
	{
		CAN_FilterInitTypeDef  	CAN_FilterInitStructure;
		if(FrameEx)
		{
			LibVarCan2BufferMode[BufferID] = 2; 
			LibVarCan2ReceiveTargetID[BufferID] = FrameID & (u32)0x1FFFFFFF;
			FrameID = FrameID & (u32)0x1FFFFFFF;
			CAN_FilterInitStructure.CAN_FilterNumber = (BufferID + 14);	//过滤器0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32位宽 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<3)&0xFFFF0000)>>16;	//32位ID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32位MASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=1;//过滤器0关联到FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//激活过滤器0
			CAN_FilterInit(&CAN_FilterInitStructure);			//滤波器初始化
		}
		else
		{
			LibVarCan2BufferMode[BufferID] = 1; 
			LibVarCan2ReceiveTargetID[BufferID] = FrameID & (u32)0x000007FF;
			FrameID = FrameID & (u32)0x000007FF;
			CAN_FilterInitStructure.CAN_FilterNumber = (BufferID + 14);	//过滤器0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32位宽 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<21)&0xFFFF0000)>>16;	//32位ID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32位MASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//过滤器0关联到FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//激活过滤器0
			CAN_FilterInit(&CAN_FilterInitStructure);			//滤波器初始化
		}
	}
}

//can发送一组数据(固定格式:ID为0X12,标准帧,数据帧)	
//len:数据长度(最大为8)				     
//msg:数据指针,最大为8个字节.
//返回值:0,成功;
//		 其他,失败;
u8 LibCan1SendData(u32 FrameID,u16 FrameEx, u8 *Data,u16 DataLength)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	if(FrameEx == 1)
	{
		TxMessage.ExtId=FrameID;			// 设置扩展标示符 
		TxMessage.IDE=CAN_Id_Extended; 	// 扩展帧
	}
	else if(FrameEx == 0)
	{
		TxMessage.StdId=FrameID;			// 标准标识符 
		TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	}
	else
	{
		return 2;
	}
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=DataLength;				// 要发送的数据长度
	for(i=0;i<DataLength;i++)
	TxMessage.Data[i]=Data[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	 
}

u8 LibCan2SendData(u32 FrameID,u16 FrameEx, u8 *Data,u16 DataLength)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	if(FrameEx == 1)
	{
		TxMessage.ExtId=FrameID;			// 设置扩展标示符 
		TxMessage.IDE=CAN_Id_Extended; 	// 扩展帧
	}
	else if(FrameEx == 0)
	{
		TxMessage.StdId=FrameID;			// 标准标识符 
		TxMessage.IDE=CAN_Id_Standard; 	// 标准帧
	}
	else
	{
		return 2;
	}
	TxMessage.RTR=CAN_RTR_Data;		// 数据帧
	TxMessage.DLC=DataLength;				// 要发送的数据长度
	for(i=0;i<DataLength;i++)
	TxMessage.Data[i]=Data[i];			          
	mbox= CAN_Transmit(CAN2, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//等待发送结束
	if(i>=0XFFF)return 1;
	return 0;	 
}

//can口接收数据查询
//buf:数据缓存区;	 
//返回值:0,无数据被收到;
//		 其他,接收的数据长度;
u8 Can1_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//读取数据	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}

u8 Can2_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN2,CAN_FIFO0)==0)return 0;		//没有接收到数据,直接退出 
    CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);//读取数据	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}

u8 LibCan1ReceiveFlag(u8 BufferID)
{
	if(BufferID < 14 && LibVarCan1BufferMode[BufferID] != 0)
	{
		return LibVarCan1ReceiveFlag[BufferID];
	}
	return 0;
}

u8 LibCan2ReceiveFlag(u8 BufferID)
{
	if(BufferID < 14 && LibVarCan2BufferMode[BufferID] != 0)
	{
		return LibVarCan2ReceiveFlag[BufferID];
	}
	return 0;
}

u8 LibCan1ReadReceiveData(u8 BufferID,u8 *Data)
{
	u8 i;
	if( BufferID<14&& LibVarCan1BufferMode[BufferID]!=0 )
	{
		for(i=0;i<8;i++)
		{
			*(Data+i) = LibVarCan1ReceiveData[BufferID][i];
		}
		LibVarCan1ReceiveFlag[BufferID] = 0;
		if(LibVarCan1ReceiveLength[BufferID] > 8)
		{
			LibVarCan1ReceiveLength[BufferID] = 8;
		}
		return LibVarCan1ReceiveLength[BufferID];
	}
	return 0;
}

u8 LibCan2ReadReceiveData(u8 BufferID,u8 *Data)
{
	u8 i;
    
	if (BufferID < 14 && LibVarCan2BufferMode[BufferID] != 0)
	{
		for(i=0;i<8;i++)
		{
			*(Data+i) = LibVarCan2ReceiveData[BufferID][i];
		}
		LibVarCan2ReceiveFlag[BufferID] = 0;
		if(LibVarCan2ReceiveLength[BufferID] > 8)
		{
			LibVarCan2ReceiveLength[BufferID] = 8;
		}
		return LibVarCan2ReceiveLength[BufferID];
	}
	return 0;
}
