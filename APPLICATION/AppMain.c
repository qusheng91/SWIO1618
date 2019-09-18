#include "swio_1618.h"
#include "LibLpc.h"

void AppInit(void)
{
    #if EEPROM_TEST
    u16 i;
    u8 read;
    u8 buff[50];
    #endif
    
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

    #if EEPROM_TEST
    for (i = 0; i < 4096; i++)
    {
        if (eeprom_write_byte(i, i) == -1)
        {
            printf("eeprom fail %d\r\n", i);
        }
    }
    
    for (i = 0; i < 4096; i++)
    {
        eeprom_read_byte(i, &read);
        printf("i = %d read = %x\r\n", i, read);
    }
    
    #endif
    CAN1_Mode_Init(250);
    LibCan1SetRecMode(0, 0, 0x181);
    LibTimerSet(1, 100);
}

void AppMain(void)
{

    u8 RecData[8];
    u32 ms;
    
    uint8_t buff[100];
    uint16_t len;

    if (LibTimerGet(1, &ms))
    {
        LibTimerSet(1, 100);
        LED = ~LED;
       
        RecData[0] = 0x01;
        RecData[1] = 0x02;
        RecData[2] = 0x03;
        RecData[3] = 0x04;
        RecData[4] = 0x05;
        RecData[5] = 0x06;
        RecData[6] = 0x07;
        RecData[7] = 0x08;
        
        len = serial_read(buff, 10);

        serial_write(buff, len);
        
        //serial_write(RecData, 8);
        
        LibCan1SendData(0x125, 0, RecData, 8);
        LibCan1SendData(0x122, 0, RecData, 8);
        LibCan1SendData(0x123, 0, RecData, 8);
        LibCan1SendData(0x124, 0, RecData, 8);
    }
   
    if (LibCan1ReceiveFlag(0))
    {
        LibCan1ReadReceiveData(0, RecData);
        LibCan1SendData(0x131, 0, RecData, 8);
    }
}
