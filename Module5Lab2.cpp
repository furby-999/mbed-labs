#include "mbed.h"

#define AIN1 p15
#define AIN2 p16
#define STOP_BUTTON p17

#define RED_LED p9
#define SPEAKER p21


AnalogIn	tankPot(AIN1);
AnalogIn	tempPot(AIN2);
DigitalIn	stopButton(STOP_BUTTON);

DigitalOut	tankLed(RED_LED);
PwmOut		speaker(SPEAKER);

float		tankLevel;
float		temp;

float		SPEAKER_PERIOD = 0.003125;

void warbleSpeakerFlashLed() {
	tankLed = 1;
	speaker = .5;
	speaker.period(.25);
//	speaker = .25;
	wait_ms(425);
//	speaker = .75;
	speaker.period(.75);
	wait_ms(425);
	tankLed = 0;
//	speaker = .25;
	speaker.period(.25);
	wait_ms(425);
	speaker = .75;
//	speaker.period(.75);
	wait_ms(425);
	tankLed = 1;
}

void speakerContinuous() {
	for(float i=0; i<.5; i+=.05) {
		speaker.period(.003125-(.002*.5));
		speaker = .05*.5;
	}
	
	wait_ms(500);

	for(float i=0; i<.5; i+=.05) {
		speaker.period(.003125-(.002*.5));
		speaker = .05*.5;
	}
}

void speakerBeep() {
	speaker.period(SPEAKER_PERIOD);
	speaker = .5;
}

void speakerTwoTone() {
	for(float i=0; i<.5; i+=.05) {
		speaker.period(.003125-(.002*.7));
		speaker = .05*.5;
	}
	
	wait_ms(500);

	for(float i=0; i<.5; i+=.05) {
		speaker.period(.003125-(.002*.5));
		speaker = .05*.5;
	}	
}

int main() {

	bool stop = false;

	while(stop==false) {
		tankLed = 0;
		speaker = 0;
		
		tankLevel = tankPot; 
		temp = tempPot;
		
		if(tankLevel < .75) {
			warbleSpeakerFlashLed();
			goto CONTINUE;
		}
		
		if(tankLevel != 1) {
			goto CONTINUE;
		}
		
		if(temp < .33) {
			speakerBeep();
			goto CONTINUE;
		}
		
		if(temp > .66) {
			speakerTwoTone();
			goto CONTINUE;
		}
		
		speakerContinuous();
			
CONTINUE:
		wait_ms(100);
		stop = stopButton;
	}
}
