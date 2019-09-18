#include "LibCAN.h"
#include "LibVarDefine.h"
#include "LibUsart.h"	


//CAN1��ʼ������
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
	CAN_InitStructure.CAN_TTCM=DISABLE;			//��ʱ�䴥��ͨ��ģʽ  
	CAN_InitStructure.CAN_ABOM=ENABLE;			//����Զ����߹���	 
	CAN_InitStructure.CAN_AWUM=DISABLE;			//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART=ENABLE;			//��ֹ�����Զ����� 
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	//���Ĳ�����,�µĸ��Ǿɵ�  
	CAN_InitStructure.CAN_TXFP=DISABLE;			//���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	        //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; 
	//���ò�����
	switch(bps)
	{
		case 10:
			CAN_InitStructure.CAN_SJW=1;				//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 			//Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				//Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
			CAN_InitStructure.CAN_Prescaler=300;        //��Ƶϵ��(Fdiv)Ϊbrp+1	
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
	Flag = CAN_Init(CAN1, &CAN_InitStructure);        	//��ʼ��CAN1 
	while(CAN_InitStatus_Success!=Flag)
	{
		Flag = CAN_Init(CAN1, &CAN_InitStructure);        	//��ʼ��CAN1 
	}
	CAN_ITConfig(CAN1,CAN_IT_FMP0|CAN_IT_FMP1,ENABLE);				//FIFO0/1��Ϣ�Һ��ж�����.		    

	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	return 0;
}

//CAN2��ʼ������
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
	CAN_InitStructure.CAN_TTCM=DISABLE;			//��ʱ�䴥��ͨ��ģʽ  
	CAN_InitStructure.CAN_ABOM=ENABLE;			//����Զ����߹���	 
	CAN_InitStructure.CAN_AWUM=DISABLE;			//˯��ģʽͨ���������(���CAN->MCR��SLEEPλ)
	CAN_InitStructure.CAN_NART=ENABLE;			//��ֹ�����Զ����� 
	CAN_InitStructure.CAN_RFLM=DISABLE;		 	//���Ĳ�����,�µĸ��Ǿɵ�  
	CAN_InitStructure.CAN_TXFP=DISABLE;			//���ȼ��ɱ��ı�ʶ������ 
	CAN_InitStructure.CAN_Mode= CAN_Mode_Normal;	        //ģʽ���ã� mode:0,��ͨģʽ;1,�ػ�ģʽ; 
	//���ò�����
	switch(bps)
	{
		case 10:
			CAN_InitStructure.CAN_SJW=1;				//����ͬ����Ծ���(Tsjw)Ϊtsjw+1��ʱ�䵥λ  CAN_SJW_1tq	 CAN_SJW_2tq CAN_SJW_3tq CAN_SJW_4tq
			CAN_InitStructure.CAN_BS1=CAN_BS1_10tq; 			//Tbs1=tbs1+1��ʱ�䵥λCAN_BS1_1tq ~CAN_BS1_16tq
			CAN_InitStructure.CAN_BS2=CAN_BS2_1tq;				//Tbs2=tbs2+1��ʱ�䵥λCAN_BS2_1tq ~	CAN_BS2_8tq
			CAN_InitStructure.CAN_Prescaler=300;        //��Ƶϵ��(Fdiv)Ϊbrp+1	
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
	Flag = CAN_Init(CAN2, &CAN_InitStructure);        	//��ʼ��CAN1 
	while(CAN_InitStatus_Success!=Flag)
	{
		Flag = CAN_Init(CAN2, &CAN_InitStructure);        	//��ʼ��CAN1 
	}
	CAN_ITConfig(CAN2,CAN_IT_FMP0|CAN_IT_FMP1,ENABLE);				//FIFO0/1��Ϣ�Һ��ж�����.		    

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     // �����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;            // �����ȼ�Ϊ2
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

//����CAN����buffer����
//bufferID��ΧΪ0~27
//FrameEx:0Ϊ��׼֡��1Ϊ��չ֡
//FrameIDΪ��Ҫ���յ�Ŀ��ID
//����ֵΪ0ʱ�����óɹ�������ֵΪ1ʱ������ʧ��
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
			CAN_FilterInitStructure.CAN_FilterNumber = BufferID;	//������0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32λ�� 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<3)&0xFFFF0000)>>16;	//32λID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32λMASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=1;//������0������FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//���������0
			CAN_FilterInit(&CAN_FilterInitStructure);			//�˲�����ʼ��
		}
		else
		{
			LibVarCan1BufferMode[BufferID] = 1; 
			LibVarCan1ReceiveTargetID[BufferID] = FrameID;
			FrameID = FrameID & (u32)0x000007FF;
			CAN_FilterInitStructure.CAN_FilterNumber = BufferID;	//������0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32λ�� 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<21)&0xFFFF0000)>>16;	//32λID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32λMASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//������0������FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//���������0
			CAN_FilterInit(&CAN_FilterInitStructure);			//�˲�����ʼ��
		}
	}
}

//����CAN����buffer����
//bufferID��ΧΪ0~27
//FrameEx:0Ϊ��׼֡��1Ϊ��չ֡
//FrameIDΪ��Ҫ���յ�Ŀ��ID
//����ֵΪ0ʱ�����óɹ�������ֵΪ1ʱ������ʧ��
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
			CAN_FilterInitStructure.CAN_FilterNumber = (BufferID + 14);	//������0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32λ�� 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<3)&0xFFFF0000)>>16;	//32λID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<3)|CAN_ID_EXT|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32λMASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=1;//������0������FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//���������0
			CAN_FilterInit(&CAN_FilterInitStructure);			//�˲�����ʼ��
		}
		else
		{
			LibVarCan2BufferMode[BufferID] = 1; 
			LibVarCan2ReceiveTargetID[BufferID] = FrameID & (u32)0x000007FF;
			FrameID = FrameID & (u32)0x000007FF;
			CAN_FilterInitStructure.CAN_FilterNumber = (BufferID + 14);	//������0
			CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
			CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit; 	//32λ�� 
			CAN_FilterInitStructure.CAN_FilterIdHigh=(((u32)FrameID<<21)&0xFFFF0000)>>16;	//32λID
			CAN_FilterInitStructure.CAN_FilterIdLow=(((u32)FrameID<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xFFFF;
			CAN_FilterInitStructure.CAN_FilterMaskIdHigh=0xffff;//32λMASK
			CAN_FilterInitStructure.CAN_FilterMaskIdLow=0xffff;
			CAN_FilterInitStructure.CAN_FilterFIFOAssignment=0;//������0������FIFO0
			CAN_FilterInitStructure.CAN_FilterActivation=ENABLE;//���������0
			CAN_FilterInit(&CAN_FilterInitStructure);			//�˲�����ʼ��
		}
	}
}

//can����һ������(�̶���ʽ:IDΪ0X12,��׼֡,����֡)	
//len:���ݳ���(���Ϊ8)				     
//msg:����ָ��,���Ϊ8���ֽ�.
//����ֵ:0,�ɹ�;
//		 ����,ʧ��;
u8 LibCan1SendData(u32 FrameID,u16 FrameEx, u8 *Data,u16 DataLength)
{	
	u8 mbox;
	u16 i=0;
	CanTxMsg TxMessage;
	if(FrameEx == 1)
	{
		TxMessage.ExtId=FrameID;			// ������չ��ʾ�� 
		TxMessage.IDE=CAN_Id_Extended; 	// ��չ֡
	}
	else if(FrameEx == 0)
	{
		TxMessage.StdId=FrameID;			// ��׼��ʶ�� 
		TxMessage.IDE=CAN_Id_Standard; 	// ��׼֡
	}
	else
	{
		return 2;
	}
	TxMessage.RTR=CAN_RTR_Data;		// ����֡
	TxMessage.DLC=DataLength;				// Ҫ���͵����ݳ���
	for(i=0;i<DataLength;i++)
	TxMessage.Data[i]=Data[i];			          
	mbox= CAN_Transmit(CAN1, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN1, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
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
		TxMessage.ExtId=FrameID;			// ������չ��ʾ�� 
		TxMessage.IDE=CAN_Id_Extended; 	// ��չ֡
	}
	else if(FrameEx == 0)
	{
		TxMessage.StdId=FrameID;			// ��׼��ʶ�� 
		TxMessage.IDE=CAN_Id_Standard; 	// ��׼֡
	}
	else
	{
		return 2;
	}
	TxMessage.RTR=CAN_RTR_Data;		// ����֡
	TxMessage.DLC=DataLength;				// Ҫ���͵����ݳ���
	for(i=0;i<DataLength;i++)
	TxMessage.Data[i]=Data[i];			          
	mbox= CAN_Transmit(CAN2, &TxMessage);   
	i=0; 
	while((CAN_TransmitStatus(CAN2, mbox)==CAN_TxStatus_Failed)&&(i<0XFFF))i++;	//�ȴ����ͽ���
	if(i>=0XFFF)return 1;
	return 0;	 
}

//can�ڽ������ݲ�ѯ
//buf:���ݻ�����;	 
//����ֵ:0,�����ݱ��յ�;
//		 ����,���յ����ݳ���;
u8 Can1_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);//��ȡ����	
    for(i=0;i<8;i++)
    buf[i]=RxMessage.Data[i];  
	return RxMessage.DLC;	
}

u8 Can2_Receive_Msg(u8 *buf)
{		   		   
 	u32 i;
	CanRxMsg RxMessage;
    if( CAN_MessagePending(CAN2,CAN_FIFO0)==0)return 0;		//û�н��յ�����,ֱ���˳� 
    CAN_Receive(CAN2, CAN_FIFO0, &RxMessage);//��ȡ����	
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
