/*
 * keyandpeele.c
 *
 * Created: 5/4/2021 3:25:34 PM
 * Author : conrad
 */ 

#include <avr/io.h>
#define F_CPU 1000000ul
#include <util/delay.h>
#include <avr/interrupt.h>
#define rs PH0
#define rw PH1
#define enable PH2
#define dataline PORTJ
unsigned char word[] = "P1 Close";
unsigned char word2[] = "P2 Close";
unsigned char word3[] = "P3 Close";
unsigned char word4[] = "P4 Close";
unsigned char word5[] = "P1: Open";
unsigned char word6[] = "P2: Open";
unsigned char word7[] = "P3: Open";
unsigned char word8[] = "P4: Open";
//initializing all integer variables to be used
int y,d,o,x,f,u,l,t,i;
int wer = 0;
int counter = 0; //Grazing counter

//Function to increment the timer
void diplayOnScreen(int time_counter){
	if(time_counter >= 1000 && time_counter < 9999 ){
		PORTK = 0b00000001;
		PORTL = (int) (time_counter/1000);
		
		_delay_ms(1);
		
		PORTK = 0b00000010;
		PORTL = (int) ( (time_counter % 1000) / 100 );
		
		_delay_ms(1);
		
		PORTK = 0b00000100;
		PORTL = (int) ( ( (time_counter % 1000) % 100 ) / 10 );
		
		_delay_ms(1);
		
		PORTK = 0b00001000;
		PORTL = (int) (time_counter % 10 );
	}
	else if(time_counter >= 100 ){
// 		PORTK = 0x01;
// 		PORTL = (int) (time_counter/1000);
// 		
		
		PORTK = 0b00000010;
		PORTL = (int) ( (time_counter / 100) );
		_delay_ms(1);
		
		PORTK = 0b00000100;
		PORTL = (int) ( (time_counter % 100 ) / 10 );
		
		_delay_ms(1);
		
		PORTK = 0b00001000;
		PORTL = (int) (time_counter % 10 );
	}
	else if( time_counter >= 10 ) {
		PORTK = 0b00000100;
		PORTL = (int)  (time_counter / 10 );
		
		_delay_ms(1);
		
		PORTK = 0b00001000;
		PORTL = (int) (time_counter % 10 );
		
	} 
	else {
		
		PORTK = 0b00001000;
		PORTL = (int) (time_counter % 10 );
		
	}
}

void closer(){
	//function for closing all main doors on lcd
	//latching
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);
	
	//command mode and write to screen
	PORTH &= ~(1<<rs);
	PORTH &= ~(1<<rw);
	
	//latching			
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);
	
	//clear screen				
	PORTJ = 0x01;

	//latching
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);

	//sending data to the lcd
	PORTH |= (1<<rs);
	//setting write mode on lcd
	PORTH &= ~(1<<rw);

	//loop for printing "p1 close" on lcd
	for(y = 0; y < 8; y++){
		PORTJ = word[y];
		//latching
		PORTH &= ~(1<<enable);
		_delay_ms(1);
		PORTH |= (1<<enable);
		_delay_ms(1);
	}
	//loop for printing "p2 close" on lcd
	for(x = 0; x < 8; x++){
		PORTJ = word2[x];
		//latching
		PORTH &= ~(1<<enable);
		_delay_ms(1);
		PORTH |= (1<<enable);
		_delay_ms(1);
	}
	//loop for printing "p3 close" on lcd
	for(d = 0; d < 8; d++){
		PORTJ = word3[d];
		//latching
		PORTH &= ~(1<<enable);
		_delay_ms(1);
		PORTH |= (1<<enable);
		_delay_ms(1);
	}
	//loop for printing "p4 close" on lcd
	for(o = 0; o < 8; o++){
		PORTJ = word4[o];
		//latching
		PORTH &= ~(1<<enable);
		_delay_ms(1);
		PORTH |= (1<<enable);
		_delay_ms(1);
	}
}

void opener(){
	//function for initiating opening sequence of main door(s)
	//latching
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);
			
	//command mode and write
	PORTH &= ~(1<<rs);
	PORTH &= ~(1<<rw);
			
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);
			
	//clear screen
	PORTJ = 0x01;

	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);
			
	//sending data to lcd in write mode
	PORTH |= (1<<rs);
	PORTH &= ~(1<<rw);
}

void padd(int green_led_value, int red_led_value){
	//function for transitions
	//light green led
	for (i = 0; i < 40; i++)
	{
		_delay_ms(100);
	}
	PORTB = green_led_value;
	for (i = 0; i < 360; i++)
	{
		_delay_ms(100);
	}
	//close doors
	closer();

	for (i = 0; i < 200; i++)
	{
		_delay_ms(100);
	}
	//add 1 minute to grazing counter
	counter++;
	for (i = 0; i < 600; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//add 1 minute to grazing counter
	counter++;
	for (i = 0; i < 600; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//add 1 minute to grazing counter
	counter++;
	for (i = 0; i < 600; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//sound buzzer
	PORTE |= (1<<0);
	//switch off green led
	PORTB &= ~(green_led_value);
	//add 1 minute to grazing counter
	counter++;
	diplayOnScreen( counter );
	//light red led
	while (wer < 60)
	{
		diplayOnScreen( counter );
		//while loop for creating 60 seconds
		PORTB ^= red_led_value;
		for (i = 0; i < 10; i++)
		{
			//for loop for creating 1 second
			_delay_ms(100);
		}
		if (wer == 40){
			//if 40 seconds pass lught green led
			PORTE &= ~(1<<0);
			//switch on green led
			PORTB ^= green_led_value;
		}
		wer++;
	}
	//switch off red led
	PORTB &= ~(red_led_value);
	for (i = 0; i < 1000; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//sound buzzer
	PORTE |= (1<<0);
	//switch off green led
	PORTB &= ~(green_led_value);
	//light red led
	wer = 0;
	while (wer < 60)
	{
		diplayOnScreen( counter );
		PORTB ^= red_led_value;
		for (i = 0; i < 10; i++)
		{
			_delay_ms(100);
		}
		if (wer == 40){
			PORTE &= ~(1<<0);
			//switch on green led
			PORTB ^= green_led_value;
		}
		wer++;
	}
	//switch off red led
	PORTB &= ~(red_led_value);
	for (i = 0; i < 400; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//add 1 minute to grazing counter
	counter++;
	for (i = 0; i < 600; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//add 1 minute to grazing counter
	counter++;
	for (i = 0; i < 600; i++)
	{
		diplayOnScreen( counter );
		_delay_ms(100);
	}
	//sound buzzer
	PORTE |= (1<<0);
	//switch off green led
	PORTB &= ~(green_led_value);
	//add 1 minute to grazing counter
	counter++;
	diplayOnScreen( counter );
	//open main door
	opener();
}

int main(void)
{
    /*
		LWANGA CONRAD ARTHUR 18/U/21116/PS
		BAKUNGA BRONSON 18/U/23411/PS
		DALI HILLARY 18/U/21102/PS
		KATUSIIME CONRAD 18/U/855
	*/
	//setting ports to respective input or output
	DDRG = 0x00;
	DDRF = 0b00001111;
	DDRE = 0xFF;
	DDRJ = 0xFF;
	DDRH = 0xFF;
	DDRK = 0xFF;
	DDRL = 0xFF;
	DDRB = 0xFF;
	DDRA = 0xFF;
	PORTA = 0x3;
	PING = 0xFF;

	//latching by setting and unsetting the enable pin
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);

	//setting command mode
	PORTH &= ~(1<<rs);
	//setting write mode on lcd
	PORTH &= ~(1<<rw);

	//latching
	PORTH &= ~(1<<enable);
	_delay_ms(1);
	PORTH |= (1<<enable);
	_delay_ms(1);

	//turn display on, show cursor, blink on
	PORTJ = 0x0F;

	//closing all doors using closer function
	closer();

	    while (1) 
    {
		//when 0 is pressed
		PORTF = 0b11111011;
		if((PINF & (1<<7)) == 0){
			diplayOnScreen( counter );
			//change all door statuses to open
			opener();
			//loop for printing P1 open
			for(f = 0; f < 8; f++){
				PORTJ = word5[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//loop for printing P2 open
			for(u = 0; u < 8; u++){
				PORTJ = word6[u];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//loop for printing P3 open
			for(l = 0; l < 8; l++){
				PORTJ = word7[l];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//loop for printing P4 open
			for(t = 0; t < 8; t++){
				PORTJ = word8[t];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
					padd(0x0F, 0xF0);
					for(f = 0; f < 8; f++){
						PORTJ = word5[f];
						PORTH &= ~(1<<enable);
						_delay_ms(1);
						PORTH |= (1<<enable);
						_delay_ms(1);
					}
					for(u = 0; u < 8; u++){
						PORTJ = word6[u];
						PORTH &= ~(1<<enable);
						_delay_ms(1);
						PORTH |= (1<<enable);
						_delay_ms(1);
					}
					for(l = 0; l < 8; l++){
						PORTJ = word7[l];
						PORTH &= ~(1<<enable);
						_delay_ms(1);
						PORTH |= (1<<enable);
						_delay_ms(1);
					}
					for(t = 0; t < 8; t++){
						PORTJ = word8[t];
						PORTH &= ~(1<<enable);
						_delay_ms(1);
						PORTH |= (1<<enable);
						_delay_ms(1);
					}
					//light red led
					wer = 0;
					while (wer < 60)
					{
						diplayOnScreen( counter );
						PORTB ^= 0xF0;
						for (i = 0; i < 10; i++)
						{
							_delay_ms(100);
						}
						if (wer == 40){
							PORTE &= ~(1<<0);
							//close doors
							closer();
						}
						wer++;
					}
					//switch off red led
					PORTB &= 0xF;
			}
		//when 2 is pressed on keypad
		PORTF = 0b11111011;
		if((PINF & (1<<4)) == 0){
			diplayOnScreen( counter );
			opener();
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word6[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			padd(0x02, 0x20);
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word6[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//light red led
			wer = 0;
			while (wer < 60)
			{
				diplayOnScreen( counter );
				PORTB ^= (1<<5);
				for (i = 0; i < 10; i++)
				{
					_delay_ms(100);
				}
				if (wer == 40){
					PORTE &= ~(1<<0);
					//close doors
					closer();
				}
				wer++;
			}
			//switch off red led
			PORTB &= ~(1<<5);
		}
		//when 1 is pressed on keypad
		PORTF = 0b11110111;
		if((PINF & (1<<4)) == 0){
			diplayOnScreen( counter );
			opener();
			for(f = 0; f < 8; f++){
				PORTJ = word5[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			padd(0x01, 0x10);
			for(f = 0; f < 8; f++){
				PORTJ = word5[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//light red led
			wer = 0;
			while (wer < 60)
			{
				diplayOnScreen( counter );
				PORTB ^= (1<<4);
				for (i = 0; i < 10; i++)
				{
					_delay_ms(100);
				}
				if (wer == 40){
					PORTE &= ~(1<<0);
					//close doors
					closer();
				}
				wer++;
			}
			//switch off red led
			PORTB &= ~(1<<4);
		}
		//when 3 is pressed
		PORTF = 0b11111101;
		if((PINF & (1<<4)) == 0){
			diplayOnScreen( counter );
			opener();
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word7[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			padd(0x04, 0x40);
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word7[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word4[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//light red led
			wer = 0;
			while (wer < 60)
			{
				diplayOnScreen( counter );
				PORTB ^= (1<<6);
				for (i = 0; i < 10; i++)
				{
					_delay_ms(100);
				}
				if (wer == 40){
					PORTE &= ~(1<<0);
					//close doors
					closer();
				}
				wer++;
			}
			//switch off red led
			PORTB &= ~(1<<6);
		}
		//when 4 is pressed
		PORTF = 0b11110111;
		if((PINF & (1<<5)) == 0){
			diplayOnScreen( counter );
			opener();
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word8[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			padd(0x08, 0x80);
			for(f = 0; f < 8; f++){
				PORTJ = word[f];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(x = 0; x < 8; x++){
				PORTJ = word2[x];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(d = 0; d < 8; d++){
				PORTJ = word3[d];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			for(o = 0; o < 8; o++){
				PORTJ = word8[o];
				PORTH &= ~(1<<enable);
				_delay_ms(1);
				PORTH |= (1<<enable);
				_delay_ms(1);
			}
			//light red led
			wer = 0;
			while (wer < 60)
			{
				diplayOnScreen( counter );
				PORTB ^= (1<<7);
				for (i = 0; i < 10; i++)
				{
					_delay_ms(100);
				}
				if (wer == 40){
					PORTE &= ~(1<<0);
					//close doors
					closer();
				}
				wer++;
			}
			//switch off red led
			PORTB &= ~(1<<7);
		}
		PORTF = 0xFF;
	}
}
