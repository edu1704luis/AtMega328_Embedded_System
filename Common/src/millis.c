#include <avr/io.h>
#include <millis.h>
//249-124


void init_millis(){
    TCCR0A |= MODE_CTC;
    TCCR0A |= COM0A1_0;
    TCCR0B |= CLK_64;
    OCR0A = 249;
    TIMSK0 |= ENEABLE_INTERRUPT_COUNTERA;
}

volatile uint16_t contador_to_ms = 0;
volatile uint8_t bandera_evento = 0;
volatile uint16_t m_seconds;

int millis(uint16_t mili_seconds){
    cli();
    m_seconds = mili_seconds;
    contador_to_ms = 0;
    sei();
    
    return 0;
}

ISR(TIMER0_COMPA_vect){
    contador_to_ms++;
    if (contador_to_ms >= m_seconds)
    {
        bandera_evento= 1;
        contador_to_ms= 0;
    }
    
}