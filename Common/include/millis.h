#ifndef MILLIS_H
#define MILLIS_H
#include <avr/io.h>
#include <avr/interrupt.h>

#define MODE_CTC 2<<0
#define CLK_64  3<<0
#define COM0A1_0 1<<6
#define ENEABLE_INTERRUPT_COUNTERA 1<<OCIE0A
void init_millis();

extern volatile uint8_t bandera_evento;
int millis(uint16_t mili_seconds);

#endif