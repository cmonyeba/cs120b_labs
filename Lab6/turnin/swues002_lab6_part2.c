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
#include "timer.h"

enum States {Start, One, Two, Three, Fall, Win} state;
unsigned char i = 0;
unsigned char button = 0;
void tick(){
	button = ~PINA&0x01;//Button

	switch(state){//transitions
		case Start: state=One; break;
		case One:
			   if(button){
				   state=One;
			   }else{
				  state=Two;
			   } break;
		case Two:
			  if(button){
				  state=Fall;
			  }
			  else{
				  state=Three;
			  }
			  break;
		case Three: 
			  if(button){
				  state=Three;
			  }else{
				 state=One;
			  } break;
		case Fall: if(button){
				   state=Fall;
			   }else{
				   state=Win;
			   }
			   break;
		case Win: if(button){
				  state=One;
			  }else{
				  state=Win;
			  }
			  break;

		default: state=Start; break;
	}//transition
	switch(state){//state action
		case Start: i=0x00;PORTB=i; break;
		case One: i=0x01;PORTB=i; break;
		case Two: i=0x02;PORTB=i; break;
		case Three: i=0x04;PORTB=i; break;
	        case Fall: break;
		case Win: break;	   
	}//stateaction
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(300);
    TimerOn();
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
