#include "buttons.h"


void init_button0(void)
{
    CLR(P5->SEL0, 0); // Configure I/O as general purpose
    CLR(P5->SEL1, 0);
    CLR(P5->DIR, 0); // Set P5.0 as input
    SET(P5->REN, 0); // Enable pull/down resistor
    CLR(P5->OUT, 0); // Pull down
    CLR(P5->IES, 0); // Clear the interrupt select for a low to high transition
    SET(P5->IE, 0); // Enable Interrupt
}

void init_button1(void)
{
    CLR(P5->SEL0, 1); // Configure I/O as general purpose
    CLR(P5->SEL1, 1);
    CLR(P5->DIR, 1); // Set P5.1 as input
    SET(P5->REN, 1); // Enable resistor
    CLR(P5->OUT, 1); // Pull down
    CLR(P5->IES, 1); // Clear the interrupt select for a low to high transition
    SET(P5->IE, 1); // Enable Interrupt
}

bool read_button0(void)
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ZERO_MASK)
    {
        is_pressed = true;
        SysTick_delay_ms(100);
    }

    return is_pressed;
}

bool read_button1(void)
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ONE_MASK)
    {
        is_pressed = true;
        SysTick_delay_ms(100);
    }

    return is_pressed;
}

void init_button_interrupts(void)
{
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
}
