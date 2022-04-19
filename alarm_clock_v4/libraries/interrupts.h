#include <msp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hd44780/hd44780.h"
#include "global_vars.h"
#include "buttons.h"


extern int current_global_state;

extern int deciseconds;
extern int seconds;
extern int minutes;
extern int hours;

extern bool alarm_set;
extern bool alarm_sounding;

extern int blink;
extern int toggle;
extern int note;

extern bool snoozing;

void alarm_toggle(void);
