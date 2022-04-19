#include <msp.h>


#define STCSR_CLKSRC    (0x0004)        // This is the CLKSOURSE bit, BIT2
#define STCSR_INT_EN    (0x0002)        // This is the TICKINT  bit, BIT1
#define STCSR_EN        (0x0001)        // This is the ENABLE bit, BIT0

void init_SysTick(void);
void SysTick_delay_ms(volatile uint32_t);
void init_timer_A1(void);
void init_timer_A0(void);
void init_TA2_PWM();
