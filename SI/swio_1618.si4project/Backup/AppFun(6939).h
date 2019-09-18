#ifndef _APPFUN_H
#define _APPFUN_H

#include "sys.h"
#include "LibUsart.h"
#include "LibEeprom.h"
#include "LibCAN.h"
#include "LibDI.h"
#include "LibDO.h"
#include "LibVarDefine.h"
#include "led.h"
#include "LibTimer.h"
#include "LibWatchDog.h"
#include "delay.h"

void AppInit(void);
void AppMain(void);


#endif
