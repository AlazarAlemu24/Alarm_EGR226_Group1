#include "msp.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hd44780/hd44780.h"
#include "libraries/timers.h"
#include "libraries/keypad.h"
#include "libraries/lcd.h"
#include "libraries/buttons.h"
#include "libraries/led.h"


void init_system(void);
void interrupt_TA1(void);
void interrupt_TA0(void);

enum states{SET_TIME, SET_ALARM, TICKING};
int current_state = TICKING;
char string_time[10];
int seconds = 0;
int minutes = 0;
int hours = 0;
char keys[14] = {'x', '1', '2', '3', '4', '5', '6', '7', '8', '9', '*',  '0', '#'};

void main(void)
{
	init_system();

	while(1)
	{
	    switch(current_state)
	    {
	        case TICKING:
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
	                hd44780_clear_row(1);
	                if(hours < 1)
	                    sprintf(string_time, "12:%02d AM", minutes);
	                else if(hours < 12)
	                    sprintf(string_time, "%02d:%02d AM", hours, minutes);
	                else if(hours < 13)
	                    sprintf(string_time, "%02d:%02d PM", hours, minutes);
	                else if(hours < 24)
	                    sprintf(string_time, "%02d:%02d PM", (hours - 12), minutes);
	                hd44780_write_string(string_time, 1, 1, NO_CR_LF);
	            }
	    }
	}
}

void init_system(void)
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    init_SysTick_NoInterrupts();
    init_TimerA1();
    init_TimerA0();
    init_keypad();
    init_lcd();
    init_button0();
    init_button1();
    init_led();
    init_button_interrupts();
    hd44780_clear_screen();
    __enable_irq();
}

void interrupt_TA1(void)
{
    TIMER_A1->CCTL[0] &= ~1;  // clear the interrupt flag
    hd44780_timer_isr();
}

void interrupt_TA0(void)
{
    if(current_state == TICKING)
        seconds++;
    TIMER_A0->CCTL[0] &= ~1;
}

void PORT5_IRQHandler()
{
    if(current_state == TICKING)
    {
        if(read_button0())
            current_state = SET_TIME;
        else if(read_button1())
            current_state = SET_ALARM;
    }
    P5->IFG &= ~3;// Clear the flag
}
