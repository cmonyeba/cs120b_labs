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
#include "bit.h"
#include "timer.h"
#include "keypad.h"

typedef struct _task{
	signed char state;
	unsigned long int period;
	unsigned long int elapsedTime;
	int(*TickFct)(int);
} task;

enum SM1_States {SM1_Start, SM1_Wait, SM1_Press};

int SM1_Tick(int state){
	unsigned char key = GetKeypadKey();
	switch(state){
		case SM1_Start:state=SM1_Wait;break;
		case SM1_Wait:
			       if(key!='\0'){
				       state=SM1_Press;
			       }break;
		case SM1_Press:
			       if(key=='\0'){
				       state=SM1_Wait;
			       }else{
				       state=SM1_Press;
			       }break;
		default:state=SM1_Wait;break;
	}
	switch(state){
		case SM1_Wait:
			key=0x1F;break;
		case SM1_Press:
			switch(key){
				case '\0':PORTB=0x1F;break;
				case '0':PORTB=0x00;break;
				case '1':PORTB=0x01;break;
				case '2':PORTB=0x02;break;
				case '3':PORTB=0x03;break;
				case '4':PORTB=0x04;break;
				case '5':PORTB=0x05;break;
				case '6':PORTB=0x06;break;
				case '7':PORTB=0x07;break;
				case '8':PORTB=0x08;break;
				case '9':PORTB=0x09;break;
				case 'A':PORTB=0x0A;break;
				case 'B':PORTB=0x0B;break;
				case 'C':PORTB=0x0C;break;
				case 'D':PORTB=0x0D;break;
				case '*':PORTB=0x0E;break;
				case '#':PORTB=0x0F;break;
				default:PORTB=0x1F;break;
			}
			break;
	}
	return state;
}


enum LCD_States {Start, Shift};
unsigned char i = 0;
unsigned char p = 32;
int LCD_Tick(int state){
	switch(state){
		case Start:state=Shift;break;
		case Shift:state=Shift;
		default:state=Shift;break;
	}
	switch(state){
		case Shift:
			
			  LCD_DisplayString(p,"CS120B is Legend... wait for it DARY!");
	  		  p--;
			  i++;
			  if(i>63){
				  p=32;
				  i=0;
			  }
			  break;
	}
}

	
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0xF0; PORTB=0x0F;
    DDRC=0xFF; PORTC=0x00;
    DDRD=0xFF; PORTD=0x00;
    static task task1, task2;
    task *tasks[]={&task1, &task2};
    const unsigned short numTasks=sizeof(tasks)/sizeof(task*);

    task1.state=-1;
    task1.period=50;
    task1.elapsedTime=task1.period;
    task1.TickFct=&SM1_Tick;
    
    task2.state=-1;
    task2.period=200;
    task2.elapsedTime=task2.period;
    task2.TickFct=&LCD_Tick;

    TimerSet(50);
    TimerOn();
    LCD_init();
    LCD_ClearScreen();

    /* Insert your solution below */
    unsigned short i;
    while (1) {

	for(i=0;i<numTasks;i++){
		if(tasks[i]->elapsedTime==tasks[i]->period){
			tasks[i]->state=tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime=0;
		}
		tasks[i]->elapsedTime+=50;
	}
	while(!TimerFlag);
	TimerFlag=0;
    }
	return 0;
}
   

