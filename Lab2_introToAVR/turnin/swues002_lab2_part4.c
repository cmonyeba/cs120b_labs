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
#include <stdlib.h>
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
    unsigned char weightOne = 0x00;
    unsigned char weightTwo = 0x00;
    unsigned char weightThree = 0x00;
    unsigned char totalWeight = 0x00;
    unsigned char shift = 0x00;
    unsigned char temp = 0x00;
 
    while (1) {
	weightOne = PINA;
	weightTwo = PINB;
	weightThree = PINC;

	totalWeight = weightOne + weightTwo + weightThree;
	shift = (totalWeight/10 *4);

	if(totalWeight >= 140){
	    temp =  ((temp&0xFE) | 0x01); //set PD0 = 1
	}
	else{
	    temp = ((temp&0xFE) | 0x00);
	}
	if(((weightOne-weightThree) | (weightThree-weightOne)) >= 80){
	    temp = (temp&0xFD) | 0x02;
	}
	temp = temp + shift; 
	PORTD = temp;
    }	
	return 1;
}
