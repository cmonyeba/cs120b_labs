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

enum States {Start, Zero, One} state;
unsigned char tempA = 0x00;

void tick(){
	tempA = PINA;
	switch(state) { //transitions
	    case Start:
	        state = Zero;
		break;
	    case Zero:
		state = ((tempA & 0x01) == 0x01) ? One : Zero;
		break;
	    case One:
		state = ((tempA & 0x01) == 0x01) ? Zero : One;
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Start:
		break;
	    case Zero:
		PORTB = 0x02;
		break;
	    case One:
		PORTB = 0x01;
		break;
	    default: break;
	} //state actions
		
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
 	DDRB = 0xff; PORTB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
