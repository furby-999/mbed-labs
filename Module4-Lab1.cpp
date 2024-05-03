#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6 
#define BUTTON_3 p7 
#define BUTTON_4 p8 

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

//Define outputs

	DigitalOut redLed(RED_LED);
	DigitalOut yellowLed(YELLOW_LED);
	DigitalOut blueLed(BLUE_LED);


//Define interrupt inputs

	InterruptIn button1(BUTTON_1);
	InterruptIn button2(BUTTON_2);
	InterruptIn button3(BUTTON_3);
	InterruptIn button4(BUTTON_4);


//Define ISRs for the interrupts
void button_1_handler(){
	
	redLed = !redLed;
	
}

void button_2_handler(){
	
	yellowLed = !yellowLed;
	
}

void button_3_handler(){
	
	blueLed = !blueLed;
	
}

void button_4_handler(){
	
	redLed = 1;
	yellowLed = 1;
	blueLed = 1;
	
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs
	redLed = 0;
	yellowLed = 0;
	blueLed = 0;

	//Interrupt handlers
	button1.rise(&button_1_handler);
	button2.rise(&button_2_handler);
	button3.rise(&button_3_handler);
	button4.rise(&button_4_handler);
	
	//Attach the address of the ISR to the rising edge
	
	//Write your code here
	
	//wait 100 ms
	while(1)
		wait_ms(100);
}

