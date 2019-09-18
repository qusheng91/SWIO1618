#include "AppVar.h"
#include "AppFun.h"
#include "AppDefine.h"

void AppMain(void)
{
	u8 di1, di2;
	u8 RecData[8];
	
	LED = ~LED;
	
	di1 = LibGetValueDI(11);
	di2 = LibGetValueDI(12);
	
	printf("DI1 = %d\r\n", di1);
	printf("DI2 = %d\r\n", di2);
	delay_ms(500);
	
	LibCan1SendData(0x121, 0, RecData, 8);
	
	if (LibCan1ReceiveFlag(1))
	{

		LibCan1ReadReceiveData(1, RecData);
		printf("CAN[0] = %d\r\n", RecData[0]);

	}
}

