#include "states.h"


enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY};
enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};

void set_time_overlay(void)
{
    set_hr_tens = 0;
    set_hr_ones = 0;
    set_min_tens = 0;
    set_min_ones = 0;
    hd44780_clear_screen();
    display_set_time();
//    hd44780_write_string("24 hrs", 2, 11, NO_CR_LF);
    current_global_state = SET_TIME;
    current_set_state = HR_TENS;
    marker++;
}

void set_time_logic(void)
{
    switch(current_set_state)
    {
        case HR_TENS:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("^    ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 3))
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
                display_set_time();
                blink = 0;
                current_set_state = HR_ONES;
                marker++;
                break;
            }
            break;
        case HR_ONES:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string(" ^   ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(set_hr_tens == 2)
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
                    display_set_time();
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
                display_set_time();
                blink = 0;
                current_set_state = MIN_TENS;
                marker++;
                break;
            }
            break;
        case MIN_TENS:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("   ^ ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 6))
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
                display_set_time();
                blink = 0;
                current_set_state = MIN_ONES;
                marker++;
                break;
            }
            break;
        case MIN_ONES:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("    ^", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 10))
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
                display_set_time();
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

void set_alarm_overlay(void)
{
    set_hr_tens = alarm_hr_tens;
    set_hr_ones = alarm_hr_ones;
    set_min_tens = alarm_min_tens;
    set_min_ones = alarm_min_ones;
    hd44780_clear_screen();
    display_set_time();
    hd44780_write_string("Alarm:", 3, 1, NO_CR_LF);
//    alarm_set = true;
    display_alarm_toggle();
//    hd44780_write_string("1:ON/OFF 2:Exit", 4, 1, NO_CR_LF);
    hd44780_write_string("1:ON/OFF", 4, 1, NO_CR_LF);
    current_global_state = SET_ALARM;
    current_set_state = HR_TENS;
    marker++;
}

void set_alarm_logic(void)
{
    if(toggle > 0)
    {
        toggle = 0;
        display_alarm_toggle();
    }

    if(deciseconds == 10)
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
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("^    ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 3))
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
                display_set_time();
                blink = 0;
                current_set_state = HR_ONES;
                marker++;
                break;
            }
            break;
        case HR_ONES:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 1, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string(" ^   ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(set_hr_tens == 2)
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
                    display_set_time();
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
                display_set_time();
                blink = 0;
                current_set_state = MIN_TENS;
                marker++;
                break;
            }
            break;
        case MIN_TENS:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("   ^ ", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 6))
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
                display_set_time();
                blink = 0;
                current_set_state = MIN_ONES;
                marker++;
                break;
            }
            break;
        case MIN_ONES:
            if(blink > 9)
            {
                display_set_time();
                blink = 0;
            }
            else if(blink > 4)
            {
                hd44780_write_string("  ", 1, 4, NO_CR_LF);
            }

            if(marker > 0)
            {
                marker = 0;
                hd44780_write_string("    ^", 2, 1, NO_CR_LF);
            }

            keyval = read_keypad();
            if(keyval == 11 || (keyval > 0 && keyval < 10))
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
                display_set_time();
                blink = 0;
//                deciseconds = 0;
//                seconds = 0;
//                minutes = set_min_tens * 10 + set_min_ones;
//                hours = set_hr_tens * 10 + set_hr_ones;
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

void ticking_overlay(void)
{
    hd44780_clear_screen();
    display_time();
    hd44780_write_string("1:Set Time", 3, 1, NO_CR_LF);
    hd44780_write_string("2:Set Alarm", 4, 1, NO_CR_LF);
    current_global_state = TICKING;
}

void tick_logic(void)
{
    play_alarm();
    if(deciseconds == 10)
    {
        deciseconds = 0;
        seconds++;

        if(snoozing)
            snooze_seconds++;
        if(snooze_seconds == 15)
        {
            snooze_seconds = 0;
            snoozing = false;
            alarm();
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
                alarm();
        }
        display_time();
    }
}

void snooze_overlay(void)
{
    hd44780_clear_screen();
    display_time();
    hd44780_write_string("1:Snooze Alarm", 3, 1, NO_CR_LF);
    hd44780_write_string("2:Turn Alarm Off", 4, 1, NO_CR_LF);
    current_global_state = TICKING;
}

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

void display_set_time(void)
{
    char display_time_string[10];
    sprintf(display_time_string, "%d%d:%d%d", set_hr_tens, set_hr_ones, set_min_tens, set_min_ones);
    hd44780_write_string(display_time_string, 1, 1, NO_CR_LF);
    hd44780_write_string("24 hrs", 1, 11, NO_CR_LF);
}

void display_alarm_toggle(void)
{
//    hd44780_clear_row(3);
    if(alarm_set)
        hd44780_write_string("ON ", 3, 7, NO_CR_LF);
    else
        hd44780_write_string("OFF", 3, 7, NO_CR_LF);
}

void alarm(void)
{
    if(alarm_set)
    {
        alarm_sounding = true;
        current_global_state = SNOOZE_OVERLAY;
//        hd44780_write_string("Alarm sounding", 2, 1, NO_CR_LF);
    }
}

void play_alarm(void)
{
    if(alarm_sounding)
    {
        TIMER_A2->CCR[4] = 3409;
//        if(note > 70)
//        {
//            note = 0;
//            TIMER_A2->CCR[0] = 11467;
//        }
//        if(note > 60)
//            TIMER_A2->CCR[0] = 10216;
//        if(note > 50)
//            TIMER_A2->CCR[0] = 9101;
//        if(note > 40)
//            TIMER_A2->CCR[0] = 8590;
//        if(note > 30)
//            TIMER_A2->CCR[0] = 7653;
//        if(note > 20)
//            TIMER_A2->CCR[0] = 6818;
//        if(note > 10)
//            TIMER_A2->CCR[0] = 6074;
    }
    else
        TIMER_A2->CCR[4] = 0;
}

//void play_scale(){
//
//    TIMER_A2->CCR[0] = 183486.2385;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 163487.7384;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 154241.6452;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 137425.5612;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 122448.9796;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 115562.4037;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 102951.2697;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 91743.11927;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 102951.2697;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 115562.4037;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 122448.9796;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 137425.5612;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 154241.6452;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 163487.7384;
//
//    SysTick_delay_ms(200);
//
//    TIMER_A2->CCR[0] = 183486.2385;
//
//    SysTick_delay_ms(200);
//
//}
