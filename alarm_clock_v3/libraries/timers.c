#include "timers.h"


void init_SysTick_NoInterrupts(void)
{
    SysTick->CTRL  &= ~BIT0;                             //clears enable to stop the counter
    SysTick->LOAD   = 0x00FFFFFF;                        //sets the period... note: (3006600/1000 - 1) = 1ms
    SysTick->VAL    = 0;                                 //clears the value
    SysTick->CTRL   = (STCSR_CLKSRC | STCSR_EN);         //enable SysTick with core clock, no interrupts -> this is the ENABLE and CLKSOURSE bits: Systic->CTRL |= 0x05;
}

void SysTick_delay_ms(uint32_t ms_delay){
    //Delays time_ms number of milliseconds
    //Assume 3MHz clock -> 3000 cycles per millisecond
    SysTick->LOAD  = 3000 * (uint32_t)ms_delay;
    SysTick->VAL   = 0;                               // starts counting from 0
    SysTick->CTRL |= (STCSR_CLKSRC | STCSR_EN);       // ENABLE, CLKSOURSE bits  .... Systic->CTRL |= 0x05;
    while(!(SysTick->CTRL & ((uint32_t)1)<<16));      // Continue while bit 16 is high or use   ....while( (SysTick->CTRL & BIT16) == 0);
    SysTick->CTRL &= ~(STCSR_CLKSRC | STCSR_EN);      // Disable the Systic timer               .... Systic->CTRL =0 ;
}

void init_TimerA1(void)
{
    TIMER_A1->CTL = 0x02D1;// SMCLK, ID= /8, up mode, TA clear
    TIMER_A1->EX0 = 7; // Divide by 8;
    TIMER_A1->CCR[0] = 47; // 29
    TIMER_A1->CCTL[0] |= 0x10; // Enable TA1.0 interrupt

    NVIC_SetPriority(TA1_0_IRQn, 3); // Set priority to 3 in NVIC
    NVIC_EnableIRQ(TA1_0_IRQn);
}

void init_TimerA0(void)
{
    TIMER_A0->CTL = 0x02D1;// SMCLK, ID= /8, up mode, TA clear
    TIMER_A0->EX0 = 7; // Divide by 8;
    TIMER_A0->CCR[0] = 18702; // Value in Cycles for 100ms
    TIMER_A0->CCTL[0] |= 0x10; // Enable TA1.0 interrupt

    NVIC_SetPriority(TA0_0_IRQn, 3); // Set priority to 3 in NVIC
    NVIC_EnableIRQ(TA0_0_IRQn);
}
