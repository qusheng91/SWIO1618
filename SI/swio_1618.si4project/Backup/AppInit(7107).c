#include "AppVar.h"
#include "AppFun.h"
#include "AppDefine.h"

void AppInit(void)
{
    u16 i;
    u8 read;

    printf("app init start\r\n");
	LibSetValueDOH(0, 1);
	LibSetValueDOH(1, 0);
    LibSetValueDOH(2, 0);
	LibSetValueDOH(3, 0);
    LibSetValueDOH(4, 0);
	LibSetValueDOH(5, 0);
    LibSetValueDOH(6, 0);
	LibSetValueDOH(7, 0);
    LibSetValueDOH(8, 0);
	LibSetValueDOH(9, 0);
    LibSetValueDOH(10, 0);
	LibSetValueDOH(11, 0);
    LibSetValueDOH(12, 0);
    LibSetValueDOH(13, 0);
	LibSetValueDOH(14, 0);
    LibSetValueDOH(15, 0);
    LibSetValueDOH(16, 0);
	LibSetValueDOH(17, 0);

		//delay_ms(1000);
    eeprom_write_byte(2, 0x5a);
    eeprom_read_byte(2, &read);
    printf("read = %x\r\n", read);
/*
    #if 1
    for (i = 0; i < 100; i++)
    {
        if (eeprom_write_byte(i, 0xaa) == 1)
        {
            printf("eeprom fail %d\r\n", i);
        }
    }
    #endif

    
    
    delay_ms(1000);
    for (i = 0; i < 100; i++)
    {
        eeprom_read_byte(i, &read);
        printf("i = %d read = %x\r\n", i, read);
    }
*/
	CAN1_Mode_Init(20);
	LibCan1SetRecMode(1, 0, 0x181);
}

