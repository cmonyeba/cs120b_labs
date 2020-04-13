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
	parkThree = PINA & 0x04;
	parkFour = PINA & 0x08;
	
	cntAvail = parkOne + (parkTwo>>1) + (parkThree>>2) + (parkFour>>3);
	if(cntAvail == 0x04){
	    PORTC = 0x80; //PC7 is set
	}
	else{
	cntAvail = parkOne + parkTwo + parkThree + parkFour;
	cntAvail = ~cntAvail; //flips taken to zero and availible to one
	cntAvail = cntAvail & 0x0F; //get rid of ones in upper bits
	PORTC = cntAvail;
	}
	 
    }	
	return 1;
}
