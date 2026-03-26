/** 
 * @file Seg7_IandD.c
 * @author Luis Cardenas
 * @brief Main application for a 0-9999 counter on ATmega328P.
 * * This program implements a digital counter using multiplexed 4-digit 
 * 7-segment displays. It features real-time control via external buttons 
 * for incrementing, decrementing, and resetting the count
 * @version 1.0
 * @date 2026-03
*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Hw_Config.h"
#include "Seg7.h"

/**
 * @brief Decomposes a 16-bit integer into individual digits for the 7-segment display.
 * * @param count The 16-bit integer value to be decomposed (Range: 0-9999).
 * @param values_buff_seg7 Array where the decomposed digits (thousands, hundreds, tens, units) will be stored.
 * @return int Returns 0 after successful decomposition.
 * * @note This function uses successive subtraction to extract each decimal digit.
 */
int values_buff_seg7(int count, uint8_t values_buff_seg7[]);

int main(){
    OUTPUTS_SEG7;
    OUTPUTS_SELECT_DISPLAY;
    INPUTS_BUTTONS;
    ENABLE_PULLUPS;
    int count = 0;
    int buff_count = 0;
    uint8_t buff_seg_count[4] = {0,0,0,0};
    while (1){
        if (CHECK_INPUT(INCREMENT_BUTTON)) {
            _delay_ms(20);
            if (count < 9999){
                ++count;
            }else{
                count = 0;
            }
        }
        if (CHECK_INPUT(DECREMENT_BUTTON)){
            _delay_ms(20);
            if (count > 0) --count;
        }
        if (CHECK_INPUT(RESET_BUTTON)){
            _delay_ms(20);
            count = 0;
        }
        if (buff_count != count){
            values_buff_seg7(count, buff_seg_count);
            buff_count = count;
        }
        Seg7_4values(buff_seg_count);
    }
    
    return 0;
}

int values_buff_seg7(int count, uint8_t values_buff_seg7[]){
    uint8_t thousands = 0;
    uint8_t hundreds = 0;
    uint8_t tens = 0;
    uint8_t units = 0;
    while (count >= 1000){
        count -= 1000;
        thousands++;
    }
    while (count >= 100){
        count -= 100;
        hundreds++;
    }
    while (count >= 10){
        count -= 10;
        tens++;
    }
    units = count;
    values_buff_seg7[0] = thousands;
    values_buff_seg7[1] = hundreds;
    values_buff_seg7[2] = tens;
    values_buff_seg7[3] = units;
    return 0;
}