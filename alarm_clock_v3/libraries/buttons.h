#include <msp.h>
#include <stdbool.h>
#include <stdint.h>


#define SET(REG,N) (REG |=  (1<<N))
#define CLR(REG,N) (REG &= ~(1<<N))
#define BUTTON_ZERO_MASK 0x01
#define BUTTON_ONE_MASK 0x02

void init_button0(void);
void init_button1(void);
bool read_button0(void);
bool read_button1(void);
void init_button_interrupts(void);
