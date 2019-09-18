#ifndef _LIBEEPROM_H
#define _LIBEEPROM_H
#include "sys.h"

void LibSpiInit(void);
void LibSpiSetSpeed(u8 SpeedSet);
u8 LibSpiReadWriteByte(u8 TxData);
void LibEepromInit(void);
u8 LibReadOneByte(u16 addr);
u8 LibWriteOneByte(u16 addr,u8 data);


#endif
