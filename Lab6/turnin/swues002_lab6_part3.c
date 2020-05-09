/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Lab Demo: https://youtu.be/LgKSwUrlWBU

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include "timer.h"

enum States {Start, Wait, Inc, Dec, Reset} state;
unsigned char i = 0;
unsigned char b= 0;
void tick(){
	b = ~PINA&0x03;//Buttons

	switch(state){//transitions
		case Start: state=Wait; break;
		case Wait:
			   if(b == 0x01){
				   state=Inc;
			   }
			   else if(b == 0x02){
				  state=Dec;
			   }
			   else if(b==0x03){
				  state=Reset;
			   } 
			   else{
				   state=Wait;
			   }break;
		case Inc: state=Wait; break;
		case Dec: state=Wait; break;
		case Reset: state=Wait; break;

		default: state=Start; break;
	}//transition
	switch(state){//state action
		case Start: i=0; break;
		case Inc:
			   if(i<9){
				   i++;
			   } break;
		case Dec: if(i>0){
				  i--;
			  }break;
		case Reset: i = 0; break;
		case Wait: PORTB=i; break;   
	}//stateaction
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;
    TimerSet(100);
    TimerOn();
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
