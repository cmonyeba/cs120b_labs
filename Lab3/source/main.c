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
    DDRD = 0x00; PORTD = 0xFF; //input
    DDRB = 0xFE; PORTB = 0x01; //output except for PB0
    /* Insert your solution below */
	
    unsigned char weight = 0x00;
    unsigned char tempD = 0x00;
    unsigned char tempB = 0x00;
    while (1) {
	tempD = PIND;
	tempB = PINB;
	tempD = tempD << 1;
	weight = tempD | tempB; // 9 bit weight
	if(weight >= 0x46){
		PORTB = 0x02;		
	}
	if((weight > 0x05)&&(weight < 0x46)){
		PORTB = 0x04;
	}
	if(weight <= 0x05){
		PORTB = 0x00;
	}
    }
    return 1; //return
}

