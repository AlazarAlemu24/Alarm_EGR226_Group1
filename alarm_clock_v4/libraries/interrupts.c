#include "interrupts.h"



enum global_states{SET_TIME_OVERLAY, SET_TIME, SET_ALARM_OVERLAY, SET_ALARM, TICKING_OVERLAY, TICKING, SNOOZE_OVERLAY};
enum set_states{NONE, HR_TENS, HR_ONES, MIN_TENS, MIN_ONES};

void TA1_0_IRQHandler(void)
{
    TIMER_A1->CCTL[0] &= ~1;  // clear the interrupt flag
    hd44780_timer_isr();
}

void TA0_0_IRQHandler(void)
{
    TIMER_A0->CCTL[0] &= ~1;
    if(current_global_state == TICKING || current_global_state == SET_ALARM)
        deciseconds++;

    if(current_global_state == SET_TIME || current_global_state == SET_ALARM)
        blink++;

    if(alarm_sounding)
        note++;
}

//void TA2_0_IRQHandler(void)
//{
//    TIMER_A0->CCTL[0] &= ~1;
//    if(current_global_state == SET_TIME || current_global_state == SET_ALARM)
//        blink++;
//}

void PORT5_IRQHandler()
{
    switch(current_global_state)
    {
        case TICKING:
            if(!alarm_sounding)
            {
                if(read_button0())
                    current_global_state = SET_TIME_OVERLAY;
                else if(read_button1())
                    current_global_state = SET_ALARM_OVERLAY;
            }
            else
            {
                alarm_sounding = false;
                if(read_button0())
                    snoozing = true;
                else if(read_button1())
                    current_global_state = TICKING_OVERLAY;
            }
            break;
        case SET_ALARM:
            if(read_button0())
            {
                alarm_toggle();
                toggle++;
            }
//            else if(read_button1())
//            {
//                current_set_state = NONE;
//                current_global_state = TICKING_OVERLAY;
//            }
    }
    P5->IFG &= ~3;// Clear the flag
}

void alarm_toggle(void)
{
    if(alarm_set)
        alarm_set = false;
    else
        alarm_set = true;
}
