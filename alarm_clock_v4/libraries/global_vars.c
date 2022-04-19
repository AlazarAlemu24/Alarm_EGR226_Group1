#include "global_vars.h"


void set_vars()
{
    enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY};
    enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};

    current_global_state = TICKING_OVERLAY;
    current_set_state = NONE;

    deciseconds = 0;
    seconds = 0;                   //default: 0
    minutes = 0;
    hours = 0;

    alarm_set = true;               //default: false
    alarm_sounding = false;
    alarm_hr_tens = 0;
    alarm_hr_ones = 0;
    alarm_min_tens = 0;
    alarm_min_ones = 0;             //default: 0

    set_hr_tens = 0;
    set_hr_ones = 0;
    set_min_tens = 0;
    set_min_ones = 0;

    keyval = 0;

    blink = 0;
    toggle = 0;
    marker = 0;
    note = 0;

    snoozing = false;
    snooze_seconds = 0;
}
