#define F_CPU 16000000UL
#include <avr/io.h>
#include <7seg_pinout.h>
#include <PinMode.h>

int main(){
    PinMode(&DDRC, PORTC0, input);
    PinMode(&DDRC, PORTC1, input);
    PinMode(&DDRC, PORTC2, input);
    PinMode(&DDRC, PORTC3, input);
    PinMode(&DDRD, PORTD0, output);
    PinMode(&DDRD, PORTD1, output);
    PinMode(&DDRD, PORTD2, output);
    PinMode(&DDRD, PORTD3, output);
    PinMode(&DDRD, PORTD4, output);
    PinMode(&DDRD, PORTD5, output);
    PinMode(&DDRD, PORTD6, output);
    
    while (1)
    {
        uint8_t val_input = (~PINC) & 0x0F;
        PORTD = (PORTD & 0x80) | (dispay_map[val_input] & 0x7F);
    }
    
    return 0;
}