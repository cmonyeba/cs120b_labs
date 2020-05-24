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
#include "io.h"

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
				case '\0':break;
				case '0':LCD_DisplayString(1,"0");break;
				case '1':LCD_DisplayString(1,"1");break;
				case '2':LCD_DisplayString(1,"2");break;
				case '3':LCD_DisplayString(1,"3");break;
				case '4':LCD_DisplayString(1,"4");break;
				case '5':LCD_DisplayString(1,"5");break;
				case '6':LCD_DisplayString(1,"6");break;
				case '7':LCD_DisplayString(1,"7");break;
				case '8':LCD_DisplayString(1,"8");PORTB=0x00;break;
				case '9':LCD_DisplayString(1,"9");PORTB=0x01;break;
				case 'A':LCD_DisplayString(1,"A");break;
				case 'B':LCD_DisplayString(1,"B");break;
				case 'C':LCD_DisplayString(1,"C");break;
				case 'D':LCD_DisplayString(1,"D");break;
				case '*':LCD_DisplayString(1,"*");break;
				case '#':LCD_DisplayString(1,"#");break;
			}
			break;
	}
	return state;
}


	
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA=0xF0; PORTA=0x0F;
    DDRB=0xFF; PORTB=0x00;
    DDRC=0xFF; PORTC=0x00;
    DDRD=0xFF; PORTD=0x00;
    static task task1;
    task *tasks[]={&task1};
    const unsigned short numTasks=sizeof(tasks)/sizeof(task*);

    task1.state=-1;
    task1.period=100;
    task1.elapsedTime=task1.period;
    task1.TickFct=&SM1_Tick;

    LCD_init();
   


    TimerSet(10);
    TimerOn();

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
   

