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
	DDRA = 0x00; PORTA = 0xFF; 
	DDRC = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    unsigned char cntAvail = 0x00;
    unsigned char parkOne = 0x00;
    unsigned char parkTwo = 0x00;
    unsigned char parkThree = 0x00;
    unsigned char parkFour = 0x00;
    while (1) {
	parkOne = PINA & 0x01;
	parkTwo = PINA & 0x02;
	parkTwo = parkTwo >> 1;
	parkThree = PINA & 0x04;
	parkThree = parkThree >> 2;
	parkFour = PINA & 0x08;
	parkFour = parkFour >> 3;
	
	cntAvail = parkOne + parkTwo + parkThree + parkFour;
	cntAvail = 0x04 - cntAvail;
	PORTC = cntAvail;
	 
    }	
	return 1;
}
