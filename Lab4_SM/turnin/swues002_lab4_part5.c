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

enum States {Start, Locked, Code, Wait, Fall, Unlocked} state;
unsigned char input = 0x00;
unsigned int code[4];
unsigned char check = 0x00;
unsigned char temp = 0x00;

void tick(){
	input = PINA;
	
	switch(state) { //transitions
	    case Start:
	        state = Locked;
		break;
	    case Locked:
		temp = 0;
		state = Code;
		break;
	    case Unlocked:
		temp = 0;
               	state = Code;
		break;
	    case Code:
	    	if(input == 0x01 || input == 0x02 || input == 0x04){
		    if(temp < 4){
			code[temp]= input;
			temp++:
		    }
		    if(temp == 4){
			if(!check){//locked
			    if(code[0] == 4 && code[1] == 1 && code[2] == 2 && code[3] == 1){
			        state = Unlocked;
			    }
			    else{
			        state = Locked;
			    }
			}
			if(check){ //unlocked
			    if(code[0] == 4 && code[1] == 1 && code[2] == 2 && code[3] == 1){
			        state = Locked;
			    }
			    else{
			        state = Unlocked;
			    }
			}  
		    }
		    else{
		        state = Fall;
		    }
		}
		else{
		    state = Code;
		}
		break;
	    case Fall:
		if(!input){
		    state = Code;
		}
		else{
		    state = Fall;
		}  
		break;
	    default:
		state = Start;
		break;
	} //transitions
	switch(state) { //state actions
	    case Locked:
		check = 0x00;
		PORTB = check;
		break;
	    case Unlocked:
		check = 0x01;
		PORTB = check;
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
