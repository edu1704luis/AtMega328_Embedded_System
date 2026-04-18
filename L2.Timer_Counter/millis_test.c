#include <avr/io.h>
#include <avr/interrupt.h>
#include "millis.h"
#include "Hw_Config_Timer.h"

int main(){
    LED_OUTPUT;
    init_millis();
    millis(1000);
    while (1){
        if(bandera_evento == 1){
            PORTB ^=(1 << PB5);
            bandera_evento = 0;
        }
    }
    return 0;
}
