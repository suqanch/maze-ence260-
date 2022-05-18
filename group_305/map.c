/** @file   map.c
    @author Rohan Mathias & Zhenyuan He
    @date   21/10/2021
    @brief map builder for the mazes
    @note This encapsules the code needed to display the mazes
*/
#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

#include "system.h"
#include "pio.h"
#include "ledmat.h"
#include "pacer.h"

static const uint8_t pattern1[] =
{
    0x47, 0x55, 0x44, 0x51, 0x1d
};

static const uint8_t pattern2[] =
{
    0xc, 0x21, 0x14, 0x56, 0x11
};

void map_show (uint16_t time_set) 
{
    uint16_t timer = 0;
    uint8_t current_column = 0;
    //timer init 

    while(timer < time_set) {
        pacer_wait();

        ledmat_display_column(pattern1[current_column], current_column);

        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }
        timer++; 
    }                                                                                                
}

void map_show_2(uint16_t time_set)
{
    uint16_t timer = 0;
    uint8_t current_column = 0;
    //timer init 

    while(timer < time_set) {
        pacer_wait();

        ledmat_display_column(pattern2[current_column], current_column);

        current_column++;

        if (current_column > (LEDMAT_COLS_NUM - 1))
        {
            current_column = 0;
        }
        timer++; 
    } 
}
