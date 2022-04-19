#include <msp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hd44780/hd44780.h"
#include "global_vars.h"
#include "timers.h"
#include "keypad.h"


//int deciseconds;
//int seconds;
//int minutes;
//int hours;
extern int current_global_state;
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

extern int toggle;
extern int blink;
extern int marker;
extern int note;

extern bool snoozing;
extern int snooze_seconds;

void set_time_overlay(void);
void set_time_logic(void);
void set_alarm_overlay(void);
void set_alarm_logic(void);
void ticking_overlay();
void tick_logic(void);
void snooze_overlay(void);

void display_time(void);
void display_set_time(void);
void display_alarm_toggle(void);
void alarm(void);
void play_alarm(void);
//void play_scale();
