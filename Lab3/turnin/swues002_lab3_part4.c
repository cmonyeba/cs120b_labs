/*	Author: swues002
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF; //input
    DDRB = 0xFF; PORTB = 0x00; //output
    DDRC = 0xFF; PORTC = 0x00; //other
    /* Insert your solution below */
	
    unsigned char tempUpper = 0x00;
    unsigned char tempLower = 0x00;

    while (1) {
	tempUpper = PINA & 0xF0; // keep upper bits
	tempLower = PINA & 0x0F; // keep lower bits

	tempUpper = tempUpper >> 4; //move to lower
	tempLower = tempLower << 4; //move to upper

	PORTB = tempUpper;
	PORTC = tempLower;
    }
    return 1;
}
