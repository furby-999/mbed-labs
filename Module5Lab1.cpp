#include "mbed.h"

#define SPEAKER p21
#define AIN1 p15
#define AIN2 p16

// Define the PWM speaker output
PwmOut speaker(SPEAKER);

// Define analog inputs
AnalogIn pot1(AIN1);
AnalogIn pot2(AIN2);

//Define variables
float val1;
float val2;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
int main(){
    
    while(1){
		val1 = pot1.read();
		val2 = pot2.read();
    
        // Create a saw-tooth sound wave
        // Make the period and volume adjustable using the potentiometers
        
        for(float i=0; i<1; i+=.05) {
            speaker.period(.003125-(.002*val1));
            speaker = i*.05*val2;
        }
        wait_ms(1000);
    }
}