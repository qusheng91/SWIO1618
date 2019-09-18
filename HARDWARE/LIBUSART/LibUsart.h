#ifndef __LIBUSART_H
#define __LIBUSART_H
#include "stdio.h"	
#include "sys.h" 


void uart_init(u32 bound);

void LibUsartSendArray(u8 *array,u16 len);

u8 LibUsartReadReceiveData(void);

#endif


