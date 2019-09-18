#ifndef SERIAL_H_
#define SERIAL_H_
#include <stdio.h>
#include "serial_queue.h"

extern def_queue serial_rx_buffer;

extern void serial_init(uint32_t baudrate);
extern uint16_t serial_read(uint8_t *pbBuffer, uint16_t uiSize);
extern uint16_t serial_write(uint8_t *pbBuffer, uint16_t uiSize);
extern uint16_t serial_get_readable_size(void);

extern int fputc(int ch, FILE *f);

#endif

