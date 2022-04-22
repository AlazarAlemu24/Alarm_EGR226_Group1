/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         interrupts.c
 *Description:  Defines the various interrupt handlers used in the program. These
 *              include port and TA types. */

#include "interrupts.h"


enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY, BUTTON_PRESS};

/*Function:     TA1_0_IRQHandler()
 *Description:  Timer A1 interrupt used to initialize LCD display */
void TA1_0_IRQHandler(void)
{
    TIMER_A1->CCTL[0] &= ~1;  // clear the interrupt flag
    hd44780_timer_isr();
}

/*Function:     TA0_0_IRQHandler()
 *Description:  Timer A0 interrupt used to tick clock, blink displayed time while
 *              setting time and alarm, and changing note while playing alarm */
void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~1;  // clear the interrupt flag
    if(current_global_state == TICKING || current_global_state == SET_ALARM)
        deciseconds++;

    if(current_global_state == SET_TIME || current_global_state == SET_ALARM)
        blink++;

    if(alarm_sounding)
        note++;
}

/*Function:     PORT5_IRQHandler()
 *Description:  Port 5 interrupt used to handle button press */
void PORT5_IRQHandler()
{
    current_global_state = BUTTON_PRESS;
    if(read_button0())
        button = 1;
    else if(read_button1())
        button = 2;

    P5->IFG &= ~3;// Clear the flag
}
