/*Author:       Ben Snyder
 *Date:         4/21/22
 *Instructor:   Michael Doran
 *File:         led.c
 *Description:  Contains the function to initialize and turn ON/OFF the LED
 *              lights. */

#include "led.h"

/*Function:     init_led()
 *Description:  Initialize pins for LED lights */
void init_led(void)
{
    CLR(P3->SEL0, 3);
    CLR(P3->SEL1, 3);
    SET(P3->DIR, 3);
    SET(P3->OUT, 3); // Set P3.3 as output

    CLR(P3->SEL0, 2);
    CLR(P3->SEL1, 2);
    SET(P3->DIR, 2);
    SET(P3->OUT, 2); // Set P3.2 as output

    led_off(LED0);
    led_off(LED1);
}

/*Function:     led_on()
 *Description:  Turn ON LED light of LED that is passed */
void led_on(int led)
{
    if(led == LED0)
    {
        SET(P3->OUT, 3);
    }
    else if(led == LED1)
    {
        SET(P3->OUT, 2);
    }
}

/*Function:     led_off()
 *Description:  Turn OFF LED light of LED that is passed */
void led_off(int led)
{
    if(led == LED0)
    {
        CLR(P3->OUT, 3);
    }
    else if(led == LED1)
    {
        CLR(P3->OUT, 2);
    }
}
