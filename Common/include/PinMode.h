#ifndef PINMODE_H
#define PINMODE_H

#include<avr/io.h>
//status values
typedef enum { 
    input,
    output
    } status_t;
/**
 * @brief Set pin configuration.
 * @param port_addr port data direction register
 * @param pin number pin in register
 * @param mode define pin funcion INPUT or OUTPUT
 */
void PinMode(volatile uint8_t *ddr_addr, uint8_t pin, status_t mode);

#endif