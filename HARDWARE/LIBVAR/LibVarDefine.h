#ifndef _LIBVARDEFINE_H
#define _LIBVARDEFINE_H
#include "sys.h"

extern u8 DO_State[18];//DO状态

extern u8 LibVarCan1BufferMode[56];//CANbuffer的模式 扩展帧/标准帧
extern u32 LibVarCan1ReceiveTargetID[56];//CANID存储buffer
extern u8 LibVarCan1ReceiveFlag[56];//CAN的接收标志位
extern u8 LibVarCan1ReceiveData[56][8];//CAN接收数据缓存区
extern u8 LibVarCan1ReceiveLength[56];//CAN接收到的数据长度

extern u8 LibVarCan2BufferMode[56];//CANbuffer的模式 扩展帧/标准帧
extern u32 LibVarCan2ReceiveTargetID[56];//CANID存储buffer
extern u8 LibVarCan2ReceiveFlag[56];//CAN的接收标志位
extern u8 LibVarCan2ReceiveData[56][8];//CAN接收数据缓存区
extern u8 LibVarCan2ReceiveLength[56];//CAN接收到的数据长度

extern u8 LibVarTimerUpdateFlag[7];//定时器状态更新标志位
extern u32 LibVarTimerCounter[7];//定时器中断计数值(模式1时)
extern u32 LibVarTimerTime[7];//定时器需定时时间
extern u8 LibVarTimerMode[7];//定时器模式：0为普通计数模式，即小于5s的计时直接使用中断输出定时器状态
														 //1为大时间计数模式，将定时器设置为500ms计时一次，并进行累加
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

