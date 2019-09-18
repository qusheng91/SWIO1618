#include "AppVar.h"
#include "AppFun.h"
#include "AppDefine.h"


static void di_test(void);

void AppMain(void)
{

    u8 RecData[8];
    u32 ms;
    
    if (LibTimerGet(1, &ms))
    {
        LibTimerSet(1, 100);
        LED = ~LED;
        LibWatchDogFeed();
    }
    
    

    LibCan1SendData(0x121, 0, RecData, 8);
    
    if (LibCan1ReceiveFlag(1))
    {

        LibCan1ReadReceiveData(1, RecData);
        printf("CAN[0] = %d\r\n", RecData[0]);

    }
}


static void di_test(void)
{
    u8 di1, di2, di3, di4, di5, di6, di7, di8, di9, di10, di11, di12, di13, di14, di15, di16;
    di1 = LibGetValueDI(0);
    di2 = LibGetValueDI(1);
    di3 = LibGetValueDI(2);
    di4 = LibGetValueDI(3);
    di5 = LibGetValueDI(4);
    di6 = LibGetValueDI(5);
    di7 = LibGetValueDI(6);
    di8 = LibGetValueDI(7);
    di9 = LibGetValueDI(8);
    di10 = LibGetValueDI(9);
    di11 = LibGetValueDI(10);
    di12 = LibGetValueDI(11);
    di13 = LibGetValueDI(12);
    di14 = LibGetValueDI(13);
    di15 = LibGetValueDI(14);
    di16 = LibGetValueDI(15);

    
    printf("DI1 = %d\r\n", di1);
    printf("DI2 = %d\r\n", di2);
    printf("DI3 = %d\r\n", di3);
    printf("DI4 = %d\r\n", di4);
    printf("DI5 = %d\r\n", di5);
    printf("DI6 = %d\r\n", di6);
    printf("DI7 = %d\r\n", di7);
    printf("DI8 = %d\r\n", di8);
    printf("DI9 = %d\r\n", di9);
    printf("DI10 = %d\r\n", di10);
    printf("DI11 = %d\r\n", di11);
    printf("DI12 = %d\r\n", di12);
    printf("DI13 = %d\r\n", di13);
    printf("DI14 = %d\r\n", di14);
    printf("DI15 = %d\r\n", di15);
    printf("DI16 = %d\r\n", di16);

}

