/*
 * led.c
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#include "led.h"
#include "util.h"
#include "msp.h"


/*
 *
 * Description:
 *
 * This function will initialize P3.3 and P3.2 as output for
 * our reaction timer system.
 *
 * Returns:
 *
 * Nothing
 *
 */
void led_init()
{
    CLR(P3->SEL0, 3);
    CLR(P3->SEL1, 3);
    SET(P3->DIR, 3);
    SET(P3->OUT, 3); // Set P3.3 as output

    CLR(P3->SEL0, 2);
    CLR(P3->SEL1, 2);
    SET(P3->DIR, 2);
    SET(P3->OUT, 2); // Set P3.2 as output
}


/*
 *
 * Description
 *
 * This function takes one input parameter that will decide if
 * LED0 or LED1 should be on.
 *
 *
 * Returns:
 *
 * Nothing
 *
 */
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


/*
 *
 * Description
 * This function takes one input parameter that will decide if
 * LED0 or LED1 should be off
 *
 * Returns:
 *
 * Nothing
 *
 */
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
