#include <msp.h>
#include <stdint.h>


#define STCSR_CLKSRC    (0x0004)        // This is the CLKSOURSE bit, BIT2
#define STCSR_INT_EN    (0x0002)        // This is the TICKINT  bit, BIT1
#define STCSR_EN        (0x0001)        // This is the ENABLE bit, BIT0

void init_SysTick_NoInterrupts(void);
void SysTick_delay_ms(uint32_t ms_delay);
void init_TimerA1(void);
void init_TimerA0(void);
