/** 
 * @file Seg7.c
 * @brief 7-Segment logic control to 7-Segments display of
 * 1 and 4 digits.
 */
#include <avr/io.h>
#include "Seg7.h"
#include <util/delay.h>
#include "Hw_Config.h"

static const uint8_t dispay_map[] ={
//  0bGFEDCBA
    0b00111111,//0
    0b00000110,//1
    0b01011011,//2
    0b01001111,//3
    0b01100110,//4
    0b01101101,//5
    0b01111101,//6
    0b00000111,//7
    0b01111111,//8
    0b01101111,//9
    0b01110111,//A
    0b01111100,//b
    0b00111001,//C
    0b01011110,//d
    0b01111001,//E
    0b01110001,//F
};

int Seg7_control(uint8_t *value_to_show){
    UPDATE_SEGMENTS(dispay_map[*value_to_show]);
    return 0;
}

int Seg7_4values(uint8_t buff[]){
    for(int digit =0; digit<4; ++digit){
        SELECTOR_DIGIT_1_OFF;
        SELECTOR_DIGIT_2_OFF;
        SELECTOR_DIGIT_3_OFF;
        SELECTOR_DIGIT_4_OFF;
        switch (digit)
        {
        case 0:
            Seg7_control(&buff[3]);
            SELECTOR_DIGIT_4_ON;
            break;
        case 1:
            Seg7_control(&buff[2]);
            SELECTOR_DIGIT_3_ON;
            break;
        case 2:
            Seg7_control(&buff[1]);
            SELECTOR_DIGIT_2_ON;
            break;
        case 3:
            Seg7_control(&buff[0]);
            SELECTOR_DIGIT_1_ON;
            break;
        }
        _delay_ms(5);
    }
    return 0;
}
