/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         states.h
 *Description:  Functions used by all states in global switch machine and sub
 *              functions used by those functions. */

#include "states.h"

/*Enums label states for switch machines */
enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY, BUTTON_PRESS};
enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};

/*Function:     set_time_overlay()
 *Description:  Contextual information for controls relevant to setting time */
void set_time_overlay(void)
{
    if(last_global_state != SET_TIME_OVERLAY)
        last_global_state = SET_TIME_OVERLAY;

    set_hr_tens = 0;
    set_hr_ones = 0;
    set_min_tens = 0;
    set_min_ones = 0;
    hd44780_clear_screen();
    display_set_time();
    current_global_state = SET_TIME;
    current_set_state = HR_TENS;
    marker++;
}

/*Function:     set_time_logic()
 *Description:  Logic for state of setting time. */
void set_time_logic(void)
{
    if(last_global_state != SET_TIME)
        last_global_state = SET_TIME;

    switch(current_set_state)
    {
        case HR_TENS:
            if(blink > 9)               //Blink while setting time
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("^    ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 3))  //Determine key
            {
                if(keyval == 11)
                {
                    set_hr_tens = 0;
                    keyval = 0;
                }
                else
                {
                    set_hr_tens = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = HR_ONES;
                marker++;
                break;
            }
            break;
        case HR_ONES:
            if(blink > 9)               //Blink while setting time
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string(" ^   ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(set_hr_tens == 2)        //Determine key
            {
                if(keyval == 11 || (keyval > 0 && keyval < 4))
                {
                    if(keyval == 11)
                    {
                        set_hr_ones = 0;
                        keyval = 0;
                    }
                    else
                    {
                        set_hr_ones = keyval;
                        keyval = 0;
                    }
                    display_set_time(); //Display current set time value that changes with user input
                    blink = 0;
                    current_set_state = MIN_TENS;
                    marker++;
                    break;
                }
            }
            else if(keyval == 11 || (keyval > 0 && keyval < 10))
            {
                if(keyval == 11)
                {
                    set_hr_ones = 0;
                    keyval = 0;
                }
                else
                {
                    set_hr_ones = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = MIN_TENS;
                marker++;
                break;
            }
            break;
        case MIN_TENS:
            if(blink > 9)               //Blink while setting time
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("   ^ ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 6))  //Determine key
            {
                if(keyval == 11)
                {
                    set_min_tens = 0;
                    keyval = 0;
                }
                else
                {
                    set_min_tens = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = MIN_ONES;
                marker++;
                break;
            }
            break;
        case MIN_ONES:
            if(blink > 9)               //Blink while setting time
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("    ^", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 10)) //Determine key
            {
                if(keyval == 11)
                {
                    set_min_ones = 0;
                    keyval = 0;
                }
                else
                {
                    set_min_ones = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                deciseconds = 0;
                seconds = 0;
                minutes = set_min_tens * 10 + set_min_ones;
                hours = set_hr_tens * 10 + set_hr_ones;
                current_set_state = NONE;
                current_global_state = TICKING_OVERLAY;
                break;
            }
            break;
    }
}

/*Function:     set_alarm_overlay()
 *Description:  Contextual information for controls relevant to setting alarm */
void set_alarm_overlay(void)
{
    if(last_global_state != SET_ALARM_OVERLAY)
        last_global_state = SET_ALARM_OVERLAY;

    set_hr_tens = alarm_hr_tens;
    set_hr_ones = alarm_hr_ones;
    set_min_tens = alarm_min_tens;
    set_min_ones = alarm_min_ones;
    hd44780_clear_screen();
    display_set_time();
    hd44780_write_string("Alarm:", 3, 1, NO_CR_LF);
    display_alarm_toggle();
    hd44780_write_string("1:ON/OFF  2:Exit", 4, 1, NO_CR_LF);
    current_global_state = SET_ALARM;
    current_set_state = HR_TENS;
    marker++;
}

/*Function:     set_alarm_logic()
 *Description:  Logic for state of setting alarm. */
void set_alarm_logic(void)
{
    if(last_global_state != SET_ALARM)
        last_global_state = SET_ALARM;

    if(toggle > 0)                  //Only display when changed ON/OFF
    {
        toggle = 0;
        display_alarm_toggle();     //Displays whether alarm is set to ON or OFF
    }

    if(deciseconds == 10)           //Keep track of time
    {
        deciseconds = 0;
        seconds++;
        if(seconds == 60)
        {
            seconds = 0;
            minutes++;
            if(minutes == 60)
            {
                minutes = 0;
                hours++;
                if(hours == 24)
                    hours = 0;
            }
        }
    }

    switch(current_set_state)
    {
        case HR_TENS:
            if(blink > 9)               //Blink while setting alarm
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("^    ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 3))  //Filter keypad input
            {
                if(keyval == 11)        //Determine key
                {
                    set_hr_tens = 0;
                    keyval = 0;
                }
                else
                {
                    set_hr_tens = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = HR_ONES;
                marker++;
                break;
            }
            break;
        case HR_ONES:
            if(blink > 9)               //Blink while setting alarm
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string(" ^   ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(set_hr_tens == 2)        //Determine key
            {
                if(keyval == 11 || (keyval > 0 && keyval < 4))
                {
                    if(keyval == 11)
                    {
                        set_hr_ones = 0;
                        keyval = 0;
                    }
                    else
                    {
                        set_hr_ones = keyval;
                        keyval = 0;
                    }
                    display_set_time();     //Display current set time value that changes with user input
                    blink = 0;
                    current_set_state = MIN_TENS;
                    marker++;
                    break;
                }
            }
            else if(keyval == 11 || (keyval > 0 && keyval < 10))
            {
                if(keyval == 11)
                {
                    set_hr_ones = 0;
                    keyval = 0;
                }
                else
                {
                    set_hr_ones = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = MIN_TENS;
                marker++;
                break;
            }
            break;
        case MIN_TENS:
            if(blink > 9)               //Blink while setting alarm
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("   ^ ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 6))  //Determine key
            {
                if(keyval == 11)
                {
                    set_min_tens = 0;
                    keyval = 0;
                }
                else
                {
                    set_min_tens = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                current_set_state = MIN_ONES;
                marker++;
                break;
            }
            break;
        case MIN_ONES:
            if(blink > 9)               //Blink while setting alarm
            {
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)              //Move marker to digit currently being set
            {
                marker = 0;
                hd44780_write_string("    ^", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();     //Read keypad
            if(keyval == 11 || (keyval > 0 && keyval < 10))     //Determine key
            {
                if(keyval == 11)
                {
                    set_min_ones = 0;
                    keyval = 0;
                }
                else
                {
                    set_min_ones = keyval;
                    keyval = 0;
                }
                display_set_time();     //Display current set time value that changes with user input
                blink = 0;
                alarm_hr_tens = set_hr_tens;
                alarm_hr_ones = set_hr_ones;
                alarm_min_tens = set_min_tens;
                alarm_min_ones = set_min_ones;
                current_set_state = NONE;
                current_global_state = TICKING_OVERLAY;
                break;
            }
            break;
    }
}

/*Function:     ticking_overlay()
 *Description:  Contextual information for controls relevant to clock ticking */
void ticking_overlay(void)
{
    if(last_global_state != TICKING_OVERLAY)
        last_global_state = TICKING_OVERLAY;

    hd44780_clear_screen();
    display_time();
    hd44780_write_string("1:Set Time", 3, 1, NO_CR_LF);
    hd44780_write_string("2:Set Alarm", 4, 1, NO_CR_LF);
    current_global_state = TICKING;
}

/*Function:     tick_logic()
 *Description:  Logic for state of clock ticking. */
void tick_logic(void)
{
    if(last_global_state != TICKING)
        last_global_state = TICKING;

    play_alarm();               //Play alarm if alarm time and turned ON
    if(deciseconds == 10)       //Keep track of time
    {
        deciseconds = 0;
        seconds++;

        if(snoozing)            //Keep track of snooze time
            snooze_seconds++;
        if(snooze_seconds == 15)//End of snooze time
        {
            snooze_seconds = 0;
            snoozing = false;
            alarm();            //Prep alarm to play following snooze time
        }

        if(seconds == 60)
        {
            seconds = 0;
            minutes++;
            if(minutes == 60)
            {
                minutes = 0;
                hours++;
                if(hours == 24)
                    hours = 0;
            }

            if(hours == (alarm_hr_tens * 10 + alarm_hr_ones) && minutes == (alarm_min_tens * 10 + alarm_min_ones))
                alarm();            //Prep alarm to play if alarm time and alarm ON
        }
        display_time();             //Display current clock time
    }
}

/*Function:     snooze_overlay()
 *Description:  Contextual information for controls relevant to snoozing alarm */
void snooze_overlay(void)
{
    if(last_global_state != SNOOZE_OVERLAY)
        last_global_state = SNOOZE_OVERLAY;

    hd44780_clear_screen();
    display_time();
    hd44780_write_string("1:Snooze Alarm", 3, 1, NO_CR_LF);
    hd44780_write_string("2:Turn Alarm Off", 4, 1, NO_CR_LF);
    current_global_state = TICKING;
}

/*Function:     button_press()
 *Description:  Handles interrupts resulting from button press during states of
 *              clock ticking and setting alarm. */
void button_press(void)
{
    switch(last_global_state)
    {
        case TICKING:
            if(!alarm_sounding)
            {
                if(button == 1)
                {
                    current_global_state = SET_TIME_OVERLAY;
                    button = 0;
                }
                else if(button == 2)
                {
                    current_global_state = SET_ALARM_OVERLAY;
                    button = 0;
                }
            }
            else
            {
                alarm_sounding = false;
                if(button == 1)
                {
                    snoozing = true;
                    button = 0;
                    current_global_state = TICKING;
                }
                else if(button == 2)
                {
                    current_global_state = TICKING_OVERLAY;
                    button = 0;
                    snoozing = false;
                    snooze_seconds = 0;
                }
            }
            break;
        case SET_ALARM:
            if(button == 1)
            {
                alarm_toggle();
                toggle++;
                button = 0;
                current_global_state = SET_ALARM;
            }
            else if(button == 2)
            {
                current_set_state = NONE;
                current_global_state = TICKING_OVERLAY;
                button = 0;
            }
            break;
        default:
            break;
    }
}

/*Function:     alarm_toggle()
 *Description:  Toggles alarm to ON or OFF */
void alarm_toggle(void)
{
    if(alarm_set)
        alarm_set = false;
    else
        alarm_set = true;
}

/*Function:     display_time()
 *Description:  Displays current clock time */
void display_time(void)
{
    char display_time_string[10];

    if(hours < 1)
        sprintf(display_time_string, "12:%02d:%02d AM", minutes, seconds);
    else if(hours < 10)
        sprintf(display_time_string, " %d:%02d:%02d AM", hours, minutes, seconds);
    else if(hours < 12)
        sprintf(display_time_string, "%d:%02d:%02d AM", hours, minutes, seconds);
    else if(hours < 13)
        sprintf(display_time_string, "%d:%02d:%02d PM", hours, minutes, seconds);
    else if (hours < 22)
        sprintf(display_time_string, " %d:%02d:%02d PM", (hours - 12), minutes, seconds);
    else if(hours < 24)
        sprintf(display_time_string, "%d:%02d:%02d PM", (hours - 12), minutes, seconds);
    hd44780_write_string(display_time_string, 1, 1, NO_CR_LF);
}

/*Function:     display_set_time()
 *Description:  Displays current set time that changes with user input */
void display_set_time(void)
{
    char display_time_string[10];
    sprintf(display_time_string, "%d%d:%d%d", set_hr_tens, set_hr_ones, set_min_tens, set_min_ones);
    hd44780_write_string(display_time_string, 1, 1, NO_CR_LF);
    hd44780_write_string("24 hrs", 1, 11, NO_CR_LF);
}

/*Function:     display_alarm_toggle()
 *Description:  Displays whether alarm is set to ON or OFF */
void display_alarm_toggle(void)
{
    if(alarm_set)
        hd44780_write_string("ON ", 3, 7, NO_CR_LF);
    else
        hd44780_write_string("OFF", 3, 7, NO_CR_LF);
}

/*Function:     alarm()
 *Description:  Triggers alarm to go off if currently set to ON */
void alarm(void)
{
    if(alarm_set)
    {
        alarm_sounding = true;
        current_global_state = SNOOZE_OVERLAY;
    }
}

/*Function:     play_alarm()
 *Description:  Plays alarm tone and toggles LED lights ON and OFF */
void play_alarm(void)
{
    if(alarm_sounding)
    {
        if(note == (note_interval * 7))
        {
            note = 0;
            TIMER_A2->CCR[0] = 11467;       //Note: C4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_off(LED0);
            led_on(LED1);
        }
        else if(note == (note_interval * 6))
        {
            TIMER_A2->CCR[0] = 10216;       //Note: D4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_on(LED0);
            led_off(LED1);
        }
        else if(note == (note_interval * 5))
        {
            TIMER_A2->CCR[0] = 9101;        //Note: E4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_off(LED0);
            led_on(LED1);
        }
        else if(note == (note_interval * 4))
        {
            TIMER_A2->CCR[0] = 8590;        //Note: F4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_on(LED0);
            led_off(LED1);
        }
        else if(note == (note_interval * 3))
        {
            TIMER_A2->CCR[0] = 7653;        //Note: G4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_off(LED0);
            led_on(LED1);
        }
        else if(note == (note_interval * 2))
        {
            TIMER_A2->CCR[0] = 6818;        //Note: A4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_on(LED0);
            led_off(LED1);
        }
        else if(note == (note_interval * 1))
        {
            TIMER_A2->CCR[0] = 6074;        //Note: B4
            TIMER_A2->CCR[4] = (TIMER_A2->CCR[0] / 2);
            led_off(LED0);
            led_on(LED1);
        }
    }
    else
    {
        TIMER_A2->CCR[4] = 0;
        led_off(LED0);
        led_off(LED1);
        note = 0;
    }
}
