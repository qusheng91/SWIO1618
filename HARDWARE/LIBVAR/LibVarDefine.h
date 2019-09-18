#ifndef _LIBVARDEFINE_H
#define _LIBVARDEFINE_H
#include "sys.h"

extern u8 DO_State[18];//DO״̬

extern u8 LibVarCan1BufferMode[56];//CANbuffer��ģʽ ��չ֡/��׼֡
extern u32 LibVarCan1ReceiveTargetID[56];//CANID�洢buffer
extern u8 LibVarCan1ReceiveFlag[56];//CAN�Ľ��ձ�־λ
extern u8 LibVarCan1ReceiveData[56][8];//CAN�������ݻ�����
extern u8 LibVarCan1ReceiveLength[56];//CAN���յ������ݳ���

extern u8 LibVarCan2BufferMode[56];//CANbuffer��ģʽ ��չ֡/��׼֡
extern u32 LibVarCan2ReceiveTargetID[56];//CANID�洢buffer
extern u8 LibVarCan2ReceiveFlag[56];//CAN�Ľ��ձ�־λ
extern u8 LibVarCan2ReceiveData[56][8];//CAN�������ݻ�����
extern u8 LibVarCan2ReceiveLength[56];//CAN���յ������ݳ���

extern u8 LibVarTimerUpdateFlag[7];//��ʱ��״̬���±�־λ
extern u32 LibVarTimerCounter[7];//��ʱ���жϼ���ֵ(ģʽ1ʱ)
extern u32 LibVarTimerTime[7];//��ʱ���趨ʱʱ��
extern u8 LibVarTimerMode[7];//��ʱ��ģʽ��0Ϊ��ͨ����ģʽ����С��5s�ļ�ʱֱ��ʹ���ж������ʱ��״̬
														 //1Ϊ��ʱ�����ģʽ������ʱ������Ϊ500ms��ʱһ�Σ��������ۼ�
extern u8 LibVarUsartRecData;
	
//eeprom	
#define WRSR    0x01
#define WRITE    0x02
#define READ    0x03
#define WRDI    0x04
#define RDSR     0x05
#define WREN    0x06
#define SPI_EEPROM_CS PAout(4)

#endif

