#include "AppVar.h"
#include "AppFun.h"
#include "AppDefine.h"

void AppInit(void)
{
	LibSetValueDOH(2, 0);
	LibSetValueDOH(3, 1);
	
	LibCan1SetRecMode(1, 0, 0x181);
}
