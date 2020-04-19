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

enum States {Start, Locked, WaitFirst, WaitFall, WaitSecond, Unlocked} state;
unsigned char input = 0x00;
unsigned char temp = 0x00;

void tick(){
	input = PINA;
	
	switch(state) { //transitions
	    case Start:
	        state = Locked;
		break;
	    case Locked:
		state = WaitFirst;
		break;
	    case WaitFirst:
		if(input == 0x01 || input == 0x02 || input == 0x04){
		    if(input == 0x04){
			temp = 1;
		    }
		    state = WaitFall;
		}
		else if(input == 0x80){
		    state = Locked;
		}
		else{
		   state = WaitFirst;
		}
		break;
	    case WaitFall:
		if(input == 0x00){
		    state = WaitSecond;
		}
		else{
		    state = WaitFall;
		}
		break;
	    case WaitSecond:
		if(input == 0x02){
	 	    if(temp == 1){
		        state = Unlocked;
		    }
		    else{
		        state = Locked;	
		    }
		}
		else if(input == 0x80){
		    state = Locked;
		} 
		else if(input == 0x00){
		    state = WaitSecond;
		}
		else{
		    state = Locked;
		}
		break;
	    case Unlocked:
		if(input == 0x80){
	            state = Locked;
		}
		else{
		    state = Unlocked;
		}
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Locked:
		PORTB = 0x00;
		break;
	    case Unlocked:
		PORTB = 0x01;
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
