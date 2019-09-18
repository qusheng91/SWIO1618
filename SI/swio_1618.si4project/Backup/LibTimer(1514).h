#ifndef _LIBTIMER_H
#define _LIBTIMER_H
#include "sys.h"

void LibTimer1Init(u16 Period);
void LibTimer2Init(u16 Period);
void LibTimer3Init(u16 Period);
void LibTimer4Init(u16 Period);
void LibTimer5Init(u16 Period);
void LibTimer6Init(u16 Period);
void LibTimer7Init(u16 Period);
u8 LibTimer(u8 Channal);
void LibTimerInit(u8 Channal,u32 Time);
#endif
