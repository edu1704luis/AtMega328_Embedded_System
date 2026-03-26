/** 
 * @file Hw_Config.h
 * @author Luis Cardenas
 * @brief Hardware description and configuration for a 0-9999 counter.
 * Features: increment, decrement, and reset buttons using a 4-digit 7-segment display.
 * @version 1.0
 * @date 2026-03
*/

#ifndef HW_CONFIG_H
#define HW_CONFIG_H

#include <avr/io.h>

/*---set I/O ports----*/
#define OUTPUTS_SEG7 (DDRD = 0xFF) //config port D as outputs 7bit(7seg digit 1) 6-0bits (7seg leds)
#define OUTPUTS_SELECT_DISPLAY (DDRB |= 0x07) //config port B 2-0bits(7seg digits 4-2) as outputs 
#define INPUTS_BUTTONS (DDRC &= 0Xf8) //config port C 2-0(reset-decrement-increment) bits as inputs
#define ENABLE_PULLUPS (PORTC |= 0x07) //eneable pull_up resistors for port C inputs

#define SEG7_PORT PORTD // PORT D Data Register
#define SELECTOR_DIGIT PORTB // PORT B Data Register
#define SEG7_MASK 0x80 

/* ---Display Digit Control---*/
/** @brief  Macro bit shift eneable digit x of 7seg display*/
#define SELECTOR_DIGIT_1 (1<<PORTD7)
#define SELECTOR_DIGIT_2 (1<<PORTB0)
#define SELECTOR_DIGIT_3 (1<<PORTB1)
#define SELECTOR_DIGIT_4 (1<<PORTB2)

/** @brief Macro to turn off digit x 7seg display */
#define SELECTOR_DIGIT_1_OFF (SEG7_PORT |= SELECTOR_DIGIT_1)
#define SELECTOR_DIGIT_2_OFF (SELECTOR_DIGIT |= SELECTOR_DIGIT_2)
#define SELECTOR_DIGIT_3_OFF (SELECTOR_DIGIT |= SELECTOR_DIGIT_3)
#define SELECTOR_DIGIT_4_OFF (SELECTOR_DIGIT |= SELECTOR_DIGIT_4)

/** @brief Macro to turn on digit x 7seg display */
#define SELECTOR_DIGIT_1_ON (SEG7_PORT &= ~(SELECTOR_DIGIT_1))
#define SELECTOR_DIGIT_2_ON (SELECTOR_DIGIT &= ~(SELECTOR_DIGIT_2))
#define SELECTOR_DIGIT_3_ON (SELECTOR_DIGIT &= ~(SELECTOR_DIGIT_3))
#define SELECTOR_DIGIT_4_ON (SELECTOR_DIGIT &= ~(SELECTOR_DIGIT_4))

#define UPDATE_SEGMENTS(bits) \
((SEG7_PORT = (SEG7_PORT & SEG7_MASK) | bits)) // sets output to 7seg display

/** @brief bit shift select input (increment-decrement-reset) button*/
#define INCREMENT_BUTTON PINC0
#define DECREMENT_BUTTON PINC1
#define RESET_BUTTON PINC2 

#define CHECK_INPUT(BUTTON) (!(PINC & (1 << BUTTON))) // read input pin address

#endif