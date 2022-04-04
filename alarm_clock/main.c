#include "msp.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "hd44780/hd44780.h"
#include "util.h"
#include "app_logic.h"
#include "button.h"
#include "led.h"

void system_init(void);
void lcd_init(void);
void keypad_init(void);
void init_timer_a0(void);
void init_timer_a1(void);
void init_timer_32(void);

enum GLOBAL_STATES {SET_TIME_HOUR, SET_TIME_MINUTE, SET_ALARM, TICKING, ALARM_SOUNDING, SNOOZING};
//enum SET_TIME_STATES {TIME_NONE, TIME_HOUR, TIME_MIN, TIME_SEC};
//enum SET_ALARM_STATE {ALARM_NONE, ALARM_HOUR, ALARM_MIN, ALARM_SEC}

int current_global_state = SET_TIME_HOUR;
//int current_set_time_state = TIME_NONE;
//int current_set_alarm_state = ALARM_NONE;
int hour = 0;
int min = 0;
int sec = 0;
bool alarm_on = false;

void main(void)
{
    system_init();
    hd44780_clear_screen();

    while(1)
    {
        switch(current_global_state)
        {
            case SET_TIME_HOUR:
                hd44780_clear_screen();
                hd44780_write_string((hour + ":" + min), 1, 1, NO_CR_LF);
                hd44780_write_string("^^", 2, 1, NO_CR_LF);
                hd44780_write_string("Use keypad to set time", 3, 1, NO_CR_LF);
                hd44780_write_string("Btn1: Continue", 4, 1, NO_CR_LF);
                break;

            case SET_TIME_MINUTE:
                break;

            case SET_ALARM:
                break;

            case TICKING:
                break;

            case ALARM_SOUNDING:
                break;

            case SNOOZING:
                break;
        }
    }
}

void system_init()
{
    __disable_irq();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    lcd_init();
    keypad_init();
    init_timer_a0();
    init_timer_a1();
    init_timer_32();
    init_button_zero();
    init_button_one();
    init_button_interrupts();
    led_init();
    led_off(LED0);
    led_off(LED1);
    __enable_irq();
}

void init_timer_a0()
{
    TIMER_A0->CTL = 0x02D1;// SMCLK, ID= /8, up mode, TA clear
    TIMER_A0->EX0 = 7; // Divide by 8;
    TIMER_A0->CCR[0] = 18702; // Value in Cycles for 100ms
    TIMER_A0->CCTL[0] |= 0x10; // Enable TA1.0 interrupt

    NVIC_SetPriority(TA0_0_IRQn, 3); // Set priority to 3 in NVIC
    NVIC_EnableIRQ(TA0_0_IRQn);
}

void init_timer_a1()
{
    TIMER_A1->CTL = 0x02D1;// SMCLK, ID= /8, up mode, TA clear
    TIMER_A1->EX0 = 7; // Divide by 8;
    TIMER_A1->CCR[0] = 47; // 29
    TIMER_A1->CCTL[0] |= 0x10; // Enable TA1.0 interrupt

    NVIC_SetPriority(TA1_0_IRQn, 3); // Set priority to 3 in NVIC
    NVIC_EnableIRQ(TA1_0_IRQn);
}

void init_timer_32()
{
    TIMER32_1->CONTROL = 0xAA;
    TIMER32_1->LOAD = UPPER_LIMIT;
    NVIC_SetPriority(T32_INT1_IRQn, 1);
    NVIC_EnableIRQ(T32_INT1_IRQn);
}

void lcd_init()
{
    P4->SEL1 &= ~0xFF;
    P4->SEL0 &= ~0xFF;
    P4->DIR |= 0xFF;
    P1->SEL1 &= ~0xC0;
    P1->SEL0 &= ~0xC0;
    P1->DIR |= 0xC0;
}

void keypad_init()
 {
//     P4->DIR = 0;
//     P4->REN = 0xF0;     /* enable pull resistor for column pins */
//     P4->OUT = 0xF0;     /* make column pins pull-ups */

     // Setup rows and columns as input on their respective Ports
     CLR(P3->DIR, BIT5); // col0
     CLR(P3->DIR, BIT6); // col1
     CLR(P3->DIR, BIT7); // col2
     CLR(P2->DIR, BIT4); // row0
     CLR(P2->DIR, BIT5); // row1
     CLR(P2->DIR, BIT6); // row2
     CLR(P2->DIR, BIT7); // row3

     // Enable pull up resistors for column pins
     CLR(P2->REN, (BIT4 | BIT5 | BIT6 | BIT7));
     SET(P3->REN, (BIT5 | BIT6 | BIT7));

     // make column pins pullups
     SET(P3->OUT, (BIT5 | BIT6 | BIT7));
 }
