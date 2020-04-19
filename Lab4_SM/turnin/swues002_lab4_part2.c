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

enum States {Start, Init, Rest, Fall, Inc, Dec, Clear} state;
unsigned char buttonOne = 0x00;
unsigned char buttonTwo = 0x00;
unsigned char count = 0x00;

void tick(){
	buttonOne = PINA&0x01;
	buttonTwo = PINA&0x02;
	
	switch(state) { //transitions
	    case Start:
	        state = Init;
		break;
	    case Init:
		state = Rest;
		break;
	    case Rest:
		if(buttonOne && !buttonTwo){
		    state = Inc;
		}
	 	else if(buttonTwo && !buttonOne){
		    state = Dec;
		}
		else if(buttonOne && buttonTwo){
		    state = Clear;
		}
		else{
		   state = Rest;
		}
		break;
	    case Fall:
		if(buttonOne || buttonTwo){
		    state = Fall;
		}
		else if(buttonOne && buttonTwo){
		    state = Clear;
		}
		else{
		    state = Rest;
		}
		break;
	    case Inc:state = Fall;break;
	    case Dec:state = Fall;break;
	    case Clear:state = Fall;break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Init:
		count = 7;
		break;
	    case Rest:
		PORTC = count;
		break;
	    case Fall:
		PORTC = count;
		break;
	    case Inc:
		if(count < 9){
		    count++;
		}
		break;
	    case Dec:
		if(count > 0){
		    count--;
		}
		break;
	    case Clear:
		count = 0;
		break;
	    default: break;
	} //state actions
		
}
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
 	DDRC = 0xFF; PORTB = 0x00;
	state = Start;
    /* Insert your solution below */
    while (1) {
	tick();
    }
    return 1;
}
