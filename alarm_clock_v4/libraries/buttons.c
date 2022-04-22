/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         button.h
 *Description:  Functions included to initialize pines utilizing interrupts
 *              activated by external components, i.e. buttons */

#include "buttons.h"

/*Function:     init_button0()
 *Description:  Set up button ports for GPIO and port interrupts */
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

/*Function:     init_button1()
 *Description:  Set up button ports for GPIO and port interrupts */
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
/*Function:     read_button0()
 *Description:  Return true if button "0" is pressed */
bool read_button0(void)
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ZERO_MASK)
    {
        is_pressed = true;
    }

    return is_pressed;
}

/*Function:     read_button1()
 *Description:  Return true if button "1" is pressed */
bool read_button1(void)
{
    bool is_pressed = false;
    if(P5->IN & BUTTON_ONE_MASK)
    {
        is_pressed = true;
    }

    return is_pressed;
}

/*Function:     init_button_interrupts()
 *Description:  Interrupt on Port 5 when button pressed */
void init_button_interrupts(void)
{
    NVIC_SetPriority(PORT5_IRQn, 3);
    NVIC_EnableIRQ(PORT5_IRQn);
}
