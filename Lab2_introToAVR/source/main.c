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
	DDRC = 0x00; PORTB = 0xFF; 
	DDRD = 0xFF; PORTC = 0x00;

    /* Insert your solution below */
    unsigned char seatOne = 0x00;
    unsigned char seatTwo = 0x00;
    unsigned char seatThree = 0x00;
    unsigned char maxWeight = 0x00;
    unsigned char difference = 0x00;
    unsigned char limit = 0x00;
    unsigned char temp = 0x00;
 
    while (1) {
	seatOne = PINA;
	seatTwo = PINB;
	seatThree = PINC;

	maxWeight = seatOne + seatTwo + seatThree;
	
	if((seatOne - seatThree) >= 0x50){
	    difference = 0x02; //diff is set
	}
	if(maxWeight >= 0x8C){
	    limit = 0x01; //another flag
	}
	temp = difference | limit;
	PORTD = maxWeight | temp;
    }	
	return 1;
}
