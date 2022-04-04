/*
 * button.c
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#include "button.h"
#include "util.h"
#include "msp.h"

void init_button_zero()
{

    CLR(P5->SEL0, 0); // Configure I/O as general purpose
    CLR(P5->SEL1, 0);
    CLR(P5->DIR, 0); // Set P5.0 as input
    SET(P5->REN, 0); // Enable pull/down resistor
    CLR(P5->OUT, 0); // Pull down
    CLR(P5->IES, 0); // Clear the interrupt select for a low to high transition
    SET(P5->IE, 0); // Enable Interrupt
}

void init_button_one()
{
    CLR(P5->SEL0, 1); // Configure I/O as general purpose
    CLR(P5->SEL1, 1);
    CLR(P5->DIR, 1); // Set P5.1 as input
    SET(P5->REN, 1); // Enable resistor
    CLR(P5->OUT, 1); // Pull down
    CLR(P5->IES, 1); // Clear the interrupt select for a low to high transition
    SET(P5->IE, 1); // Enable Interrupt
}

void init_button_interrupts()
{
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
}

bool read_button_zero()
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ZERO_MASK)
        is_pressed = true;

    return is_pressed;
}

bool read_button_one()
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ONE_MASK)
        is_pressed = true;

    return is_pressed;
}
