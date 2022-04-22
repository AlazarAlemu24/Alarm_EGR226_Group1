/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         interrupts.h
 *Description:  Defines the various interrupt handlers used in the program. These
 *              include port and TA types. */

#include <msp.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hd44780/hd44780.h"
#include "global_vars.h"
#include "buttons.h"

/*Global variables used*/
extern int current_global_state;

extern int deciseconds;

extern int button;

extern int blink;
extern int note;
