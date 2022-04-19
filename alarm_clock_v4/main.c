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


void init_system(void);
void global_state_machine(void);

enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY};
enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};
extern int current_global_state;
extern int current_set_state;

extern int deciseconds;
extern int seconds;
extern int minutes;
extern int hours;

extern int set_hr_tens;
extern int set_hr_ones;
extern int set_min_tens;
extern int set_min_ones;

void main(void)
{
    init_system();

    while(1)
    {
        global_state_machine();
//        play_scale();
    }
}

void init_system(void)
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init_SysTick();
    init_timer_A1();
    init_timer_A0();
    init_TA2_PWM();
    init_keypad();
    init_lcd();
    init_button0();
    init_button1();
    init_led();
    init_button_interrupts();
    __enable_irq();

    set_vars();
    hd44780_clear_screen();
}

void global_state_machine(void)
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
    }
}
