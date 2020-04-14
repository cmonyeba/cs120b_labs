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
    DDRB = 0x00; PORTB = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	
    unsigned char tempA = 0x00;
    unsigned char tempB = 0x00;
    unsigned char cnt = 0x00;
    unsigned char check= 0x01;

    while (1) {
	tempA = PINA;
	tempB = PINB;
	
	while(tempA != 0x00){
	if((tempA & check) == check){
	    cnt++;
	    tempA >>1;  //shift down one
	}
	}
	while(tempB != 0x00){
	if((tempB & check) == check){
	    cnt++;
	    tempB >>1; //shift
	}	
		
	PORTC = cnt;
    }
    return 1;
}
