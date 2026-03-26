/** 
 * @file Seg7.h
 * @brief 7-Segment Driver Header
 * @note REQUISITES: tThis library requires the following macros to be defined
 * in "Hw_config.h"
 * -UPDATE_SEGMENTS(bits): Maps the 7-bit pattern to the physical port. 
 * -SELECTOR_DIGIT_X_ON / SELECTOR_DIGIT_X_OFF: specific macros to eneable/disable digits.
 */

#ifndef SEG7_H
#define SEG7_H

/*
     *********
    *    A    *
   *           *
   F           B
   *           *
    *    G    *
   *           *
   E           C
   *           *
    *    D    *
     *********
*/

/**
 * @brief Updates the physical segments with the corresponding value.
 * @param value_to_show Pointer type uint8_t hexadecimal value 0-F.
 * @return int Returns 0
 */
int Seg7_control(uint8_t *value_to_show);

/**
 * @brief Multiplexes 4 values onto the 4-digit display.
 * @param Count[] Array type uint8_t (Units, Tens, Hundreds, Thousands)
 * @return int Returns 0
 */
int Seg7_4values(uint8_t Count[]);
#endif