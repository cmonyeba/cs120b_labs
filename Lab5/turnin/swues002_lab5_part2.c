/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//LAB DEMO: https://youtu.be/4TYgO-n4nO4

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Rest, Fall, Inc, Dec, Clear} state;
unsigned char button = 0x00;
unsigned char temp = 0x00;
unsigned char val = 0x00;
void tick(){
	temp = PINA;
	button = ~PINA&0x03;

	switch(state){//transitions
		case Start: state=Rest; break;
                case Rest:
			    if(button==0x01){
				    state = Inc;
			    }
			    else if(button==0x02){
				    state = Dec;
			    }
			    else if(button==0x03){
				    state = Clear;
			    }
			    else{
				    state = Rest;
			    }
			    break;
		case Fall://waits for button to be released
			    if(button==0x00){
				    state = Rest;
			    }
			    else if(button==0x03){
				    state = Clear;
			    }
			    else{
				    state = Fall;
			    }
			    break;
		case Inc: state=Fall; break;
	        case Dec: state=Fall; break;
		case Clear: state=Fall; break;
		default: state=Start; break;
	}//transitions
	
	switch(state){//state actions
		case Inc:
			if(val<0x09){
				val++;
			}
			break;
		case Dec:
			if(val>0){
				val--;
			}
			break;
		case Clear:
			val = val * 0;
			break;
		case Fall: 
			PORTC = val;
			break;
		default:break;
	}//state actions
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    state = Start;
    while (1) {
     	tick();
    }
    return 1;
}
