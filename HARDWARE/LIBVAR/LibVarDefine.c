#include "LibVarDefine.h"

u8 DO_State[18];

u8 LibVarCan1BufferMode[56];//CANbuffer的模式 扩展帧/标准帧
u32 LibVarCan1ReceiveTargetID[56];//CANID存储buffer
u8 LibVarCan1ReceiveFlag[56];//CAN的接收标志位
u8 LibVarCan1ReceiveData[56][8];//CAN接收数据缓存区
u8 LibVarCan1ReceiveLength[56];//CAN接收到的数据长度

u8 LibVarCan2BufferMode[56];//CANbuffer的模式 扩展帧/标准帧
u32 LibVarCan2ReceiveTargetID[56];//CANID存储buffer
u8 LibVarCan2ReceiveFlag[56];//CAN的接收标志位
u8 LibVarCan2ReceiveData[56][8];//CAN接收数据缓存区
u8 LibVarCan2ReceiveLength[56];//CAN接收到的数据长度

u8 LibVarTimerUpdateFlag[7];//定时器状态更新标志位
u32 LibVarTimerCounter[7];//定时器中断计数值(模式1时)
u32 LibVarTimerTime[7];//定时器需定时时间
u8 LibVarTimerMode[7];//定时器模式：0为普通计数模式，即小于5s的计时直接使用中断输出定时器状态
										  //1为大时间计数模式，将定时器设置为500ms计时一次，并进行累加
u8 LibVarUsartRecData;
