#include "keypad.h"

/*Keypad initialization function.
 * Row 1:       P2.7
 * Row 2:       P2.6
 * Row 3:       P2.5
 * Row 4:       P2.4
 *
 * Column 1:    P3.5
 * Column 2:    P3.6
 * Column 3:    P3.7
 */

void init_keypad(){

    uint8_t col_mask = 0b11100000;      //mask for column keypad pins
    uint8_t row_mask = 0b11110000;      //mask for row keypad pins

    /* Set up Columns*/
    P3->SEL1 &= ~col_mask;              //clear col bits for GPIO
    P3->SEL0 &= ~col_mask;              //clear col for GPIO
    P3->DIR &= ~col_mask;               //clear all col bits initially for input

    /* Set up Rows */
    P2->SEL1 &= ~row_mask;              //clear row bits for GPIO
    P2->SEL0 &= ~row_mask;              //clear row bits for GPIO
    P2->DIR &= ~row_mask;               //clear row bits initially for input
    P2->REN |= row_mask;                //enable resistors on row pins
    P2->OUT |= row_mask;                //enable pull-up resistors on row pins
}

int read_keypad(){
    uint8_t col, row;

    for(col = 5; col < 8; col++){
        P3->DIR &= ~(BIT5 | BIT6 | BIT7);       // set column bits to inputs
        P3->DIR |= (1<<col);                    //set column pin as output
        P3->OUT &= ~(1<<col);                   //set column pin as LOW
        SysTick_delay_ms(15);                   //configure pins/ debounce

        row = P2->IN & (0b11110000);

        /* wait for buttons to be released */
        while (!(P2->IN & BIT4) | !(P2->IN & BIT5) | !( P2->IN & BIT6) | !( P2->IN & BIT7));

        if (row != 0b11110000)
            break;
    }
    P3->DIR &= ~(BIT5 | BIT6 | BIT7);       //return all columns to input

    if (col == 8)
            return 0;                       //no keys read, return 0
    /* return an integer that corresponds to the key in the keypad array */
    if (row == 0b01110000)
        return (col - 5) + 1;
    if (row == 0b10110000)
        return 3 + (col - 5) + 1;
    if (row == 0b11010000)
        return 6 + (col - 5) + 1;
    if (row == 0b11100000)
        return 9 + (col - 5) + 1;


    /* return -1 if an error has occurred */
    return -1;
}
