/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         led.h
 *Description:  Contains the function to initialize and turn ON/OFF the LED
 *              lights. */

#include <msp.h>


#define SET(REG,N) (REG |=  (1<<N))
#define CLR(REG,N) (REG &= ~(1<<N))
#define LED0 0x08 // P3.3
#define LED1 0x04 // P3.2

void init_led(void);
void led_on(int led);
void led_off(int led);
