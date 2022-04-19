#include <msp.h>
#include <stdbool.h>


int current_global_state;
int current_set_state;

int deciseconds;
int seconds;
int minutes;
int hours;

bool alarm_set;
bool alarm_sounding;
int alarm_hr_tens;
int alarm_hr_ones;
int alarm_min_tens;
int alarm_min_ones;

int set_hr_tens;
int set_hr_ones;
int set_min_tens;
int set_min_ones;

int keyval;

int blink;
int toggle;
int marker;
int note;

bool snoozing;
int snooze_seconds;

void set_vars();
