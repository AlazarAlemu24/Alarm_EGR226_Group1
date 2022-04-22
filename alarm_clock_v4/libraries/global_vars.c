/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         global_vars.c
 *Description:  Initialization/declaration of all variables used globally */

#include "global_vars.h"

/*Function:     set_vars()
 *Description:  Set all variables to initial values */
void set_vars()
{
    enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY};
    enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};

    current_global_state = TICKING_OVERLAY;
    last_global_state = TICKING_OVERLAY;
    current_set_state = NONE;

    deciseconds = 0;                //default: 0
    seconds = 0;                    //default: 0
    minutes = 0;                    //default: 0
    hours = 0;                      //default: 0

    alarm_set = false;              //default: false
    alarm_sounding = false;         //default: false
    alarm_hr_tens = 0;              //default: 0
    alarm_hr_ones = 0;              //default: 0
    alarm_min_tens = 0;             //default: 0
    alarm_min_ones = 0;             //default: 0

    set_hr_tens = 0;
    set_hr_ones = 0;
    set_min_tens = 0;
    set_min_ones = 0;

    keyval = 0;
    button = 0;

    blink = 0;
    toggle = 0;
    marker = 0;
    note = 0;
    note_interval = 10;             //default: 10

    snoozing = false;
    snooze_seconds = 0;
}
