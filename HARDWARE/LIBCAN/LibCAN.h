#ifndef __LIBCAN_H
#define __LIBCAN_H	  
#include "stm32f10x.h"
					    
										 							 				    
u8 CAN1_Mode_Init(u16 bps);//CAN��ʼ��
u8 CAN1_Filter_Init(void);//�˲�����ʼ������
u8 Can1_Receive_Msg(u8 *buf);							//��������
u8 LibCan1SendData(u32 FrameID,u16 FrameEx, u8 *Data,u16 DataLength);//CAN���ݷ��ͺ���
u8 LibCan1ReadReceiveData(u8 BufferID,u8 *Data);
u8 LibCan1ReceiveFlag(u8 BufferID);
void LibCan1SetRecMode(u16 BufferID,u16 FrameEx,u32 FrameID);

u8 CAN2_Mode_Init(u16 bps);//CAN��ʼ��
u8 CAN2_Filter_Init(void);//�˲�����ʼ������
u8 Can2_Receive_Msg(u8 *buf);							//��������
u8 LibCan2SendData(u32 FrameID,u16 FrameEx, u8 *Data,u16 DataLength);//CAN���ݷ��ͺ���
u8 LibCan2ReadReceiveData(u8 BufferID,u8 *Data);
u8 LibCan2ReceiveFlag(u8 BufferID);
void LibCan2SetRecMode(u16 BufferID,u16 FrameEx,u32 FrameID);
#endif

















