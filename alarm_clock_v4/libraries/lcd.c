/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         lcd.c
 *Description:  Contains the function to initialize the LCD display. */

#include "lcd.h"

/*Function:     init_lcd()
 *Description:  Set pins for LCD display */
void init_lcd(void)
{
    P4->SEL1 &= ~0xFF;
    P4->SEL0 &= ~0xFF;
    P4->DIR |= 0xFF;
    P1->SEL1 &= ~0xC0;
    P1->SEL0 &= ~0xC0;
    P1->DIR |= 0xC0;
}
