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

unsigned char SetBit(unsigned char x, unsigned char k) {
	return ((x&(0x01<<k))!=0;
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned short cnt = 0x00;
    unsigned char check= 0x01;

    while (1) {
	tempA = PINA;
	tempB = PINB;
	
	for(cnt=0;cnt<8;cnt++){
	    if(GetBit(tempA, cnt)){
	        check++;
	    }
            if(GetBit(tempB, cnt)){
	    	check++;
	    }
	}	
	PORTC = cnt;
    }
    return 1;
}
