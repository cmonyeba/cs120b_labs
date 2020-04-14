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
#include <avr/math.h>
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
    unsigned char difference = 0x00;
    unsigned char maxFlag = 0x00;
    unsigned char balanceFlag = 0x00;
    unsigned char temp = 0x00;
 
    while (1) {
	seatOne = PINA;
	seatTwo = PINB;
	seatThree = PINC;

	totalWeight = weightOne + weightTwo + weightThree;
	difference = abs(weightOne - weightThree);	

	if(totalWeight >= 0x8C){
	    maxFlag = 0x01; //set PD0 = 1
	}
	if(difference >= 0x50){
	    balanceFlag = 0x02; //another flag
	}
	temp = totalWeight & 0xFC;
	temp = temp | maxFlag | balanceFlag;
	PORTD = temp;
    }	
	return 1;
}
