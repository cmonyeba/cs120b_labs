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

unsigned char flag=0;
unsigned char t=11;
unsigned char b=32;
unsigned char c=21;
unsigned char s=0;
unsigned char begin=0;

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
			key=0x1F;
		case SM1_Press:
			switch(key){
				case '\0':break;
				case '0':begin=~begin&0x01;break;
				case 'A':flag=1;break;
				case 'B':flag=0;break;
				}			
			break;
	}
	return state;
}

enum Shift_States {Start, Lobby, Shift};

int Shift_Tick(int state){
	switch(state){
		case Start:state=Lobby;break;
		case Lobby:if(begin==1){
				LCD_ClearScreen();
				state=Shift;
			   }
			   else{
				state=Lobby;
			   }break;

		case Shift:if(begin==0){
				   state=Lobby;
			   }else{
				   state=Shift;
			   }break;
		default:state=Start;break;
	}
	switch(state){
		case Start:break;
		case Lobby:LCD_DisplayString(1, "Press 0 to Play");s=0;break;
		case Shift:
				   if(t>0){
					   LCD_WriteData(' ');
					   LCD_Cursor(t);
					   LCD_WriteData('*');
					   t--;
				   }
				   else{
					   LCD_WriteData(' ');
					   LCD_Cursor(1);
					   LCD_WriteData(' ');
					   t=16;
					   LCD_Cursor(t);
				   }
				   if(t==c){
					   begin=0;
				   }
				   if(b>16){
					   LCD_WriteData(' ');
					   LCD_Cursor(b);
					   LCD_WriteData('*');
					   LCD_WriteData(' ');
					   b--;
				   }
				   else{
					   LCD_WriteData(' ');
					   LCD_Cursor(17);
					   LCD_WriteData(' ');
					   b=32;
					   LCD_Cursor(b);
				   }
				   if(b==c){
					   begin=0;
				   }break;

	}
	return state;
}


enum Player_States {Player_Start, Idle, Up, Down};

int Play_Tick(int state){
	switch(state){
		case Player_Start: state=Idle;break;
		case Idle: if(begin==1){
				   state=Down;
			   }else{
				   state=Idle;
			   }break;
		case Down: if(flag==0){
				   state=Down;
			   }else{
				   state=Up;
			   }
			   if(begin==0){
				   state=Idle;
			   }break;
		case Up: if(flag==1){
				 state=Up;
			 }else{
				 state=Down;
			 }
			 if(begin==0){
				 state=Idle;
			 }break;
		default: state=Idle;
	}
	switch(state){
		case Down:
			LCD_Cursor(c);
			LCD_WriteData(' ');
			c = 21;
			LCD_Cursor(c);
			LCD_WriteData('0');
			break;
		case Up:
			LCD_Cursor(c);
			LCD_WriteData(' ');
			c = 5;
			LCD_Cursor(c);
			LCD_WriteData('0');
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
    static task task1, task2, task3;
    task *tasks[]={&task1, &task2, &task3};
    const unsigned short numTasks=sizeof(tasks)/sizeof(task*);

    task1.state=-1;
    task1.period=100;
    task1.elapsedTime=task1.period;
    task1.TickFct=&SM1_Tick;

    LCD_init();
    task2.state=-1;
    task2.period=100;
    task2.elapsedTime=task2.period;
    task2.TickFct=&Shift_Tick;

    task3.state=-1;
    task3.period=100;
    task3.elapsedTime=task3.period;
    task3.TickFct=&Play_Tick;  

    

    TimerSet(100);
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
   

