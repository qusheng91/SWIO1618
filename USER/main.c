#include "swio_1618.h"


void sys_init(void)
{
    u8 i;
    
    serial_init(115200);
    delay_init();
    LibTimerInit();
    eeprom_init();
    LibDIInit();
    LibDOInit();
    LED_Init();
    lib_can_queue_init();
    
    for (i = 0; i < 18; i++)
    {
        LibSetValueDOH(i, 0);
    }
}

int main(void)
{       
    SCB->VTOR = FLASH_BASE | 0x10000;
    
    sys_init();
    AppInit();
    
    while(1)
    {
        AppMain();
        can_queue_main();
    }          
}

