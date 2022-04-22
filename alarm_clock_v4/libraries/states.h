/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         states.h
 *Description:  Functions used by all states in global switch machine and sub
 *              functions used by those functions. */

#include <msp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hd44780/hd44780.h"
#include "global_vars.h"
#include "timers.h"
#include "keypad.h"
#include "buttons.h"
#include "led.h"

/*Global variables used*/
extern int current_global_state;
extern int last_global_state;
extern int current_set_state;

extern int deciseconds;
extern int seconds;
extern int minutes;
extern int hours;

extern bool alarm_set;
extern bool alarm_sounding;
extern int alarm_hr_tens;
extern int alarm_hr_ones;
extern int alarm_min_tens;
extern int alarm_min_ones;

extern int set_hr_tens;
extern int set_hr_ones;
extern int set_min_tens;
extern int set_min_ones;

extern int keyval;
extern int button;

extern int toggle;
extern int blink;
extern int marker;
extern int note;
extern int note_interval;

extern bool snoozing;
extern int snooze_seconds;

/*Local function declarations */
void set_time_overlay(void);
void set_time_logic(void);
void set_alarm_overlay(void);
void set_alarm_logic(void);
void ticking_overlay();
void tick_logic(void);
void snooze_overlay(void);
void button_press(void);

void alarm_toggle(void);
void display_time(void);
void display_set_time(void);
void display_alarm_toggle(void);
void alarm(void);
void play_alarm(void);
void led_toggle(void);
