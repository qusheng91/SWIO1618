#include "LibVarDefine.h"

u8 DO_State[18];

u8 LibVarCan1BufferMode[56];//CANbuffer��ģʽ ��չ֡/��׼֡
u32 LibVarCan1ReceiveTargetID[56];//CANID�洢buffer
u8 LibVarCan1ReceiveFlag[56];//CAN�Ľ��ձ�־λ
u8 LibVarCan1ReceiveData[56][8];//CAN�������ݻ�����
u8 LibVarCan1ReceiveLength[56];//CAN���յ������ݳ���

u8 LibVarCan2BufferMode[56];//CANbuffer��ģʽ ��չ֡/��׼֡
u32 LibVarCan2ReceiveTargetID[56];//CANID�洢buffer
u8 LibVarCan2ReceiveFlag[56];//CAN�Ľ��ձ�־λ
u8 LibVarCan2ReceiveData[56][8];//CAN�������ݻ�����
u8 LibVarCan2ReceiveLength[56];//CAN���յ������ݳ���

u8 LibVarTimerUpdateFlag[7];//��ʱ��״̬���±�־λ
u32 LibVarTimerCounter[7];//��ʱ���жϼ���ֵ(ģʽ1ʱ)
u32 LibVarTimerTime[7];//��ʱ���趨ʱʱ��
u8 LibVarTimerMode[7];//��ʱ��ģʽ��0Ϊ��ͨ����ģʽ����С��5s�ļ�ʱֱ��ʹ���ж������ʱ��״̬
										  //1Ϊ��ʱ�����ģʽ������ʱ������Ϊ500ms��ʱһ�Σ��������ۼ�
u8 LibVarUsartRecData;
