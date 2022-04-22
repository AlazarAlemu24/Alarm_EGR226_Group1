/*Author:       Ben Snyder
 *Course:       EGR 226: Introduction to Digital Systems
 *Assignment:   Final Project - Alarm Clock
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         main.c
 *Description:  Main function iterates program's global switch machine */

#include "msp.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "hd44780/hd44780.h"
#include "libraries/timers.h"
#include "libraries/keypad.h"
#include "libraries/lcd.h"
#include "libraries/buttons.h"
#include "libraries/led.h"
#include "libraries/states.h"
#include "libraries/global_vars.h"
#include "libraries/interrupts.h"

/*Local function declarations*/
void init_system(void);
void global_switch_machine(void);

/*Global state enum conditional int for switch machine*/
enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY, BUTTON_PRESS};
extern int current_global_state;

/*main*/
void main(void)
{
    init_system();                  //Initialize system and peripheral components

    while(1)
    {
        global_switch_machine();    //Loop thru state machine
    }
}

/*Function:     init_system()
 *Description:  Runs all initialization/setup functions for timers and external components */
void init_system(void)
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init_SysTick();                 //Initialize SysTick timer
    init_timer_A1();                //Initialize Timer A1
    init_timer_A0();                //Initialize Timer A0
    init_TA2_PWM();                 //Initialize Timer A2
    init_keypad();                  //Initialize keypad
    init_lcd();                     //Initialize LCD display
    init_button0();                 //Initialize button "0"
    init_button1();                 //Initialize button "1"
    init_led();                     //Initialize LED lights
    init_button_interrupts();       //Initialize button interrupts
    __enable_irq();

    set_vars();                     //Set all global variables to initial values
    hd44780_clear_screen();         //Clear LCD display
}

/*Function:     global_switch_machine()
 *Description:  State machine to facilitate the program's primary functions.
 *              The primary states set the time, set the alarm, and tick the
 *              clock. Each of these are preceded with an overlay, displaying
 *              the relevant information for control on the screen. The snooze
 *              state is an alternative overlay for ticking. The button press
 *              state is an interrupt handler triggered by buttons. */
void global_switch_machine(void)
{
    switch(current_global_state)
    {
        case SET_TIME_OVERLAY:
            set_time_overlay();
            break;
        case SET_TIME:
            set_time_logic();
            break;
        case SET_ALARM_OVERLAY:
            set_alarm_overlay();
            break;
        case SET_ALARM:
            set_alarm_logic();
            break;
        case TICKING_OVERLAY:
            ticking_overlay();
            break;
        case TICKING:
            tick_logic();
            break;
        case SNOOZE_OVERLAY:
            snooze_overlay();
            break;
        case BUTTON_PRESS:
            button_press();
            break;
    }

}
