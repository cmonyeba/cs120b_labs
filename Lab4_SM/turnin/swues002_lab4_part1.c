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

enum States {Start, Init, Wait, PB1} state;
unsigned char input = 0x00;
unsigned char tempB = 0x00;


void tick(){
	input = PINA;
	switch(state) { //transitions
	    case Start:
	        state = Init;
		break;
	    case Init:
		if(input == 0x00){
		    state = Wait;
		}
		else{
		    state = Init;
		}
		break;
	    case PB1:
		if(input == 0x00){
	            state = Wait;
		}
		else{
		    state = PB1;
		}
		break;
	    case Wait:
		if(input == 0x01 && tempB == 0x01){
		    state = PB1;
		}
		else if(input == 0x01 && tempB == 0x02){
		    state = Init;
		}
		else{
		    state = Wait;
		}
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Init:
		tempB = 0x01;
		PORTB = tempB;
		break;
	    case PB1:
		tempB = 0x02
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
