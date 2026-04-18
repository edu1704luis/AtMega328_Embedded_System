#include <avr/io.h>

#define LED_OUTPUT DDRB |= ( 1<< 5);
#define OC0A_OUTPUT (DDRD |= OC_OUTPUT)