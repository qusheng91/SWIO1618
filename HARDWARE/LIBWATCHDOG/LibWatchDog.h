#ifndef _LIBWATCHDOG_H
#define _LIBWATCHDOG_H
#include "sys.h"

u8 LibWatchDogInit(u16 OverflowTimeMS);
void LibWatchDogFeed(void);

#endif
