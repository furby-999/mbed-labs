#include "mbed.h"


// Define the Input pins
DigitalIn guard(p5);
DigitalIn temp(p6);
DigitalIn startButton(p7);
DigitalIn stopButton(p8);

//Define the Output pins
DigitalOut readyLed(p9);
DigitalOut runningLed(p10);
DigitalOut guardLed(p11);
DigitalOut tempLed(p12);

bool motorRunning = false;

void runMotor(bool run) {
    motorRunning = run;
    runningLed.write((int)run);
}

void activateLEDHalfSec(DigitalOut& led) {
    led.write(1);
    wait(.5);
    led.write(0);
}

int main()
{
    while(1) {
        bool readyState = true;
        
        if (guard == 0) {
            readyState = false;
            if(readyLed == 0) {
                wait(1);
                readyLed.write(1);
            } else {
                wait(1);
                readyLed.write(0);
            }
            
            activateLEDHalfSec(guardLed);

            runMotor(false);
            goto CONTINUE;
        } 
        
        if (temp == 1) {
            readyState = false;
            if(readyLed == 0) {
                wait(1);
                readyLed.write(1);
            } else {
                wait(1);
                readyLed.write(0);
            }

            activateLEDHalfSec(tempLed);
            
            runMotor(false);
            goto CONTINUE;
        } 
        
        readyState = true;
        readyLed.write(1);
        
        if (startButton == 1 && motorRunning == false) {
            runMotor(true);
            goto CONTINUE;
        } 
        

        if (stopButton == 1 && motorRunning == true) {
            runMotor(false);
            goto CONTINUE;
        }
        
		CONTINUE:
        wait(0.25);
    }
}