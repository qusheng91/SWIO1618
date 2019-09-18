#ifndef _LIBTIMER_H
#define _LIBTIMER_H
#include "sys.h"
#include <stdint.h>

extern void LibTimerInit(void);
extern void LibTimerSet(uint8_t channel, uint32_t ms);
extern uint8_t LibTimerGet(uint8_t channel, uint32_t *ms);
extern void TIM2_IRQHandler(void);

#endif
