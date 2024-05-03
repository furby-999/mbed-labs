#include "mbed.h"

#define BUTTON_1 p5
#define BUTTON_2 p6
#define BUTTON_3 p7
#define BUTTON_4 p8

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11


// Define the Input pins
DigitalIn b1(BUTTON_1);
DigitalIn b2(BUTTON_2);
DigitalIn b3(BUTTON_3);
DigitalIn b4(BUTTON_4);

//Define the Output pins
DigitalOut rled(RED_LED);
DigitalOut yled(YELLOW_LED);
DigitalOut bled(BLUE_LED);

//Define Input/Output buses
BusIn ButtonBus(BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4);
BusOut LedBus(RED_LED, YELLOW_LED, BLUE_LED);

void ControlLED_DigitalIO ();
void ControlLED_BusIO ();


int main()
{
    while(1) {
        //ControlLED_DigitalIO ();
        ControlLED_BusIO ();
        wait(0.25);
    }
}

void ControlLED_DigitalIO (){
  rled = 
        ((!b4&&!b3&&!b2&&!b1)|| // 0
        (!b4&&!b3&&(b2||b1)) || // 1 - 3
        (!b4&&(b3&&b2)) ||      // 6-7
        (b4&&b3&&b2&&b1));      // 15
  
  yled = 
        ((b4^b3) ||  // 4-5 & 6-7 & 8-11
        (b4&&b3&&b2&&b1));  // 15
        
  bled = (b4); // 8 - 15
}

void ControlLED_BusIO () {
    for (int i=0; i<3; i++) {
        switch (i) {
            case 0:
                LedBus[i] = 
                        ((!ButtonBus[3]&&!ButtonBus[2]&&!ButtonBus[1]&&!ButtonBus[0])|| // 0
                        (!ButtonBus[3]&&!ButtonBus[2]&&(ButtonBus[1]||ButtonBus[0])) || // 1 - 3
                        (!ButtonBus[3]&&(ButtonBus[2]&&ButtonBus[1])) ||      // 6-7
                        (ButtonBus[3]&&ButtonBus[2]&&ButtonBus[1]&&ButtonBus[0]));      // 15
                break;
            case 1:
                LedBus[i] = 
                        ((ButtonBus[3]^ButtonBus[2]) ||  // 4-5 & 6-7 & 8-11
                        (ButtonBus[3]&&ButtonBus[2]&&ButtonBus[1]&&ButtonBus[0]));  // 15
                break;
            case 2:
                LedBus[i] =  (ButtonBus[3]); // 8 - 15
                break;
                    
        }
    }
}
