#include "delay.h"
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
#include "AppFun.h"

int main(void)
{       
    u8 i;
    
    SCB->VTOR = FLASH_BASE | 0x10000;
    
    uart_init(115200);
    delay_init();
    LibTimerInit();
    LibEepromInit();
    LibDIInit();
    LibDOInit();
    
    for (i = 0; i < 18; i++)
    {
        LibSetValueDOH(i, 0);
    }
    LED_Init();
    AppInit();
    
    while(1)
    {
        AppMain();
    }          
}

