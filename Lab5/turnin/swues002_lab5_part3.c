/*	Author: lab
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

enum States {Start, Rest, Fall, PHASEONE, PHASETWO, PHASETHREE} state;
unsigned char button = 0x00;
unsigned char temp = 0x00;
unsigned char val = 0x00;
unsigned char cnt = 0x00;
void tick(){
	temp = PINA;
	button = ~PINA&0x01;//button one

	switch(state){//transitions
		case Start: state=Rest; break;
                case Rest:
			    if(button==0x01 && cnt==0x00){
				    state = PHASEONE;
			    }
			    else if(button==0x01 && cnt==0x01){
				    state = PHASETWO;
			    }
			    else if(button==0x01 && cnt==0x02){
				    state = PHASETHREE;
			    }
			    else{
				    state = Rest;
			    }
			    break;
		case Fall:
			   if(button==0x00){
				   state = Rest;
		           }
			   else{
			   	   state = Fall;
			   }
			   break;
		case PHASEONE: cnt++; state=Fall; break;
		case PHASETWO: cnt++; state=Fall; break;
		case PHASETHREE: cnt = cnt -2; state=Fall; break;
		default: state=Start; break;
	}//transitions
	
	switch(state){//state actions
		case PHASEONE:
			val = 0x0C;
			break;
		case PHASETWO:
			val = 0x12;
			break;
		case PHASETHREE:
			val = 0x21;
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
