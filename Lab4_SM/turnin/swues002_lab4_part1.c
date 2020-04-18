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
unsigned char tempB = 0x00;

void tick(){
	tempA = PINA;
	switch(state) { //transitions
	    case Start:
	        state = Zero;
		break;
	    case Zero:
		if(tempA){
		    state = One;
		}
		else{
		    state = Zero;
		}
		break;
	    case One:
		if(tempA){
		    state = Zero;	
		}
		else{
		    state = One;
		}
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Zero:
		tempB = 0x01;
		PORTB = tempB;
		break;
	    case One:
		tempB = 0x02;
		PORTB = tempB;
		break;
	    default: break;
	} //state actions
		
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
 	DDRB = 0xFF; PORTB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
