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

enum States {Start, One, Two, Three} state;
unsigned char three = 0;//globals
unsigned char blink =0;
unsigned char ring=0;
void t_tick(){
	switch(state){//transitions
		case Start: state=One; break;
		case One: state=Two; break;
		case Two: state=Three; break;
		case Three: state=One; break;
		default: state=Start; break;
	}//transition
	switch(state){//state action
		case Start: three = 0x00; break;
		case One: three = 0x01; break;
		case Two: three = 0x02; break;
		case Three: three = 0x04; break;
	}//stateaction
}

enum O_States {one_Start, On} one_state;
void o_tick(){
	switch(one_state){//transitions
		case one_Start: one_state=On; break;
		case On: one_state=On; break;
		default: one_state=one_Start; break;
	}//transition
	switch(one_state){//state action
		case one_Start: break;
		case On: blink = (~blink&0x08); break;
		
	}//stateaction
}

enum R_States {RStart, Hold, Ring, Stop} Rstate;
unsigned char button=0;
void r_tick(){
	button=~PINA&0x04;
        switch(Rstate){//transitions
                case RStart: Rstate=Hold; break;
		case Hold: if(button){
				   Rstate=Ring;
			   }else{
				  Rstate=Hold;
			   } break;
                case Ring: if(button){
				   Rstate=Stop;
			   }else{
				  Rstate=Hold;
			   } break;
		case Stop: if(button){
				   Rstate=Ring;
			   }else{
				   Rstate=Hold;
			   } break;
                default: Rstate=RStart; break;
        }//transition
        switch(Rstate){//state action
                case RStart: break;
		case Hold: break;
                case Ring: ring=0x10;break;
		case Stop: ring=0x00; break;
        }//stateaction
}


enum S_States {FStart, Check} Fstate;
unsigned char final = 0;
void f_tick(){
	switch(Fstate){//transitions
		case FStart: Fstate=Check; break;
		case Check: Fstate=Check; break;
		default: Fstate=FStart; break;
	}//transition
	switch(Fstate){//state action
		case FStart: break;
	case Check: final=(blink|three|ring); PORTB = final; break;
	}//stateaction
}

int main(void) {
    DDRB = 0xFF; PORTB = 0x00;
    DDRA = 0x00; PORTA = 0xFF;	
    unsigned long three_time=0;
    unsigned long one_time=0;
    unsigned long blink_time=0;
    unsigned long ring_time=0;
    const unsigned long period=1;

    TimerSet(period);
    TimerOn();
    while (1) {
	    if(three_time>=300){
		t_tick();
		three_time=0;
	    }
	    if(one_time>=1000){
		o_tick();
		one_time=0;
	    }
	    if(blink_time>=2){
		f_tick();
		blink_time=0;
	    }
	    if(ring_time>=2){
		    r_tick();
		    ring_time=0;
	    }
	while(!TimerFlag);
	TimerFlag=0;
	three_time+=period;
	one_time+=period;
	blink_time+=period;
	ring_time+=period;
    }
    return 1;
}

