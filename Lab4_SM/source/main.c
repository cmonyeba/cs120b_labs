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

enum States {Start, Rest, Switch} state;
unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
unsigned char light = 0x01;

void tick(){
	tempA = PINA;
	switch(state) { //transitions
	    case Start:
	        state = Rest;
		PORTB = light;
		break;
	    case Rest:
		if(tempA == 0x01){
		    state = Switch;
		}
		else{
		    state = Rest;
		}
		break;
	    case Switch:
		state = Rest;
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Rest:
		PORTB = light;
		break;
	    case Switch:
		light = ~light & 0x03;
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
