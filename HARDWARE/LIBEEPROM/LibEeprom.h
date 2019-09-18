#ifndef LIBEEPROM_H_
#define LIBEEPROM_H_
#include "stm32f10x.h"

extern void eeprom_init(void);
extern s8 eeprom_read_byte(u16 addr, u8 *data);
extern s8 eeprom_write_byte(u16 addr, u8 data);
extern s8 eeprom_write_page(u16 addr, u8 *data, u16 size);

#endif

