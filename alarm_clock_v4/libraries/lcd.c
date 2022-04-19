#include "lcd.h"


void init_lcd(void)
{
    P4->SEL1 &= ~0xFF;
    P4->SEL0 &= ~0xFF;
    P4->DIR |= 0xFF;
    P1->SEL1 &= ~0xC0;
    P1->SEL0 &= ~0xC0;
    P1->DIR |= 0xC0;
}
