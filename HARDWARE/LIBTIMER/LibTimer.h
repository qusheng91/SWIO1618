#ifndef _LIBTIMER_H
#define _LIBTIMER_H
#include "sys.h"
#include <stdint.h>
#include "stm32f10x.h"

extern void LibTimerInit(void);
extern void LibTimerSet(u8 channel, u32 ms);
extern u8 LibTimerGet(u8 channel, u32 *ms);
extern void TIM2_IRQHandler(void);

#endif
