/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         global_vars.h
 *Description:  Initialization/declaration of all variables used globally */

#include <msp.h>
#include <stdbool.h>


int current_global_state;           //Current state in program's global switch machine
int last_global_state;              //Last state in program's global state machine
int current_set_state;              //Current local state while setting time or alarm

/*Variables used in clock ticking */
int deciseconds;
int seconds;
int minutes;
int hours;

/*Variables used to detect alarm time and play alarm */
bool alarm_set;
bool alarm_sounding;
int alarm_hr_tens;
int alarm_hr_ones;
int alarm_min_tens;
int alarm_min_ones;

/*Variables used to set time or alarm */
int set_hr_tens;
int set_hr_ones;
int set_min_tens;
int set_min_ones;

int keyval;                         //Numerical value of key being pressed
int button;                         //Used to determine which button is pressed

int blink;                          //Used to intermittently blink displayed time while setting time or alarm is
int toggle;                         //Used to determine if alarm is set to on or off
int marker;                         //Used to determine where the marker should be while setting time or alarm to show which digit is being set
int note;                           //Used to cycle notes while playing alarm
int note_interval;                  //How long each note plays

bool snoozing;                      //Used to determine whether the alarm is currently being snoozed
int snooze_seconds;                 //How long the alarm has been snoozed for

void set_vars();
