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
	
//Define counters

volatile unsigned int count1 = 0;
volatile unsigned int count2 = 0;
volatile unsigned int count3 = 0;
volatile unsigned int countMax = 0;

void updateLEDs(){
	redLed = 0;
	yellowLed = 0;
	blueLed = 0;
	
    if(count1 == countMax) redLed = 1;
	if(count2 == countMax) yellowLed = 1;
	if(count3 == countMax) blueLed = 1;
}


//Define ISRs for the interrupts
void button_1_handler(){
	
	count1++;
	if (count1 > countMax) countMax = count1;
	updateLEDs();	

}

void button_2_handler(){
	
	count2++;
	if (count2 > countMax) countMax = count2;
	updateLEDs();	
	
}

void button_3_handler(){
	
	count3++;
	if (count3 > countMax) countMax = count3;
	updateLEDs();	
	
}

void button_4_handler(){
	
	redLed = 0;
	yellowLed = 0;
	blueLed = 0;
	
	count1 = 0;
	count2 = 0;
	count3 = 0;
	countMax = 0;
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){
		
	//Initially turn off all LEDs and set all the counters to 0	
	button_4_handler();

	//Interrupt handlers
	button1.rise(&button_1_handler);
	button2.rise(&button_2_handler);
	button3.rise(&button_3_handler);
	button4.rise(&button_4_handler);	

	//wait 100 ms
	while(1)
		wait_ms(100);
}
