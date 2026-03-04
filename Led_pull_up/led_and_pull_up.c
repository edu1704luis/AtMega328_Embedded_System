#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))
int main(){
    DDRD = 0xFF;
    PORTB |= 0x20;
    DDRB &= 0XDF;
    while (1)
    {
        if (CHECK_BIT(PINB,PINB5) == 0){
            PORTD |= 0x10;
        }else{
            PORTD &= 0xEF;
        }
    }
    
}