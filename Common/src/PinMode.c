#include "PinMode.h"
void PinMode(volatile uint8_t *ddr_addr, uint8_t pin, status_t mode) {
    // Definimos un puntero al registro PORT
    volatile uint8_t *port_addr;

    // Lógica para encontrar el PORT correspondiente
    if (ddr_addr == &DDRB) port_addr = &PORTB;
    else if (ddr_addr == &DDRC) port_addr = &PORTC;
    else if (ddr_addr == &DDRD) port_addr = &PORTD;

    if (mode == output) {
        *ddr_addr |= (1 << pin);
    } else {
        *ddr_addr &= ~(1 << pin);
        // Aquí el Pull-up se activa automáticamente
        *port_addr |= (1 << pin); 
    }
}