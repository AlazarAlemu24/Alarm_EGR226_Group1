/*
 * led.h
 *
 *  Created on: Feb 9, 2020
 *      Author: michael
 */

#ifndef LED_H_
#define LED_H_

#define LED0 0x08 // P3.3
#define LED1 0x04 // P3.2

void led_init(void);
void led_on(int led);
void led_off(int led);


#endif /* LED_H_ */
