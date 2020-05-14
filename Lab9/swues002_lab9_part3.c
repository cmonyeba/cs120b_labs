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
#include "pwm.h"
#include "timer.h"

enum States {Start, Rest, Play, Hold, Wait} state;
unsigned char button=0x00;
double f[]={523.2511,659.2551,587.3295,659.2551,698.4565,659.2551,587.3295,523.2511,587.3295,659.2551,440.0000,523.2511,587.3295,659.2551,440.0000,523.2511,523.2511,783.9909,659.2551,523.2511,587.3295,659.2551,783.9909,880.0000,783.9909,659.2551,587.3295,587.3295,587.3295,659.2551,587.3295,587.3295,659.2551,587.3295,587.3295,659.2551,587.3295,587.3295,659.2551,523.2511};
char h[]={5,7,1,1,5,3,1,3,5,1,3,5,5,1,3,5,1,1,5,1,1,1,1,1,1,1,1,1,1,1,5,1,1,5,1,1,5,1,1,1,10};
char w[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned char temp=0x00;
unsigned char i = 0x00;
unsigned char x=0x00;
void tick(){
	temp = PINA;
	button = ~PINA;

	switch(state){//transitions
		case Start: state=Rest; break;
                case Rest:
			    if(button){
				    state = Play;
			    }else{
				    i=0;
				    state=Rest;
			    }break;
		case Play:
			    if(i<40){
			    state=Hold;
			    }else{
				    state=Rest;
			    }break;
		case Hold: if(x<h[i]){
				   x++;
				   state=Hold;
			   }else{
				   x=0;
				   state=Wait;
			   }break;
	 	case Wait:if(x<w[i]){
				  x++;
				  state=Wait;
			  }else{
				  x=0;
				  i++;
				  state=Play;
			  }break;  
		default: state=Start; break;
	}//transitions

	switch(state){//state actions
		case Rest:
			set_PWM(0);
			break;
		case Play: 
			set_PWM(f[i]);
			break;
		default:break;
	}//state actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0x00; PORTA=0xFF;
    DDRB=0xFF; PORTB=0x00;
    /* Insert your solution below */
    state=Start;
    PWM_on();
    set_PWM(0);
    TimerSet(100);
    TimerOn(); 
    while (1) {
	tick();
	while(!TimerFlag);
	TimerFlag=0;
    }
    return 1;
}
