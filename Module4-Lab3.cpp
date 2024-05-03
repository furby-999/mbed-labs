#include "mbed.h"
//#include <mutex>
#include <list>

#define ADULT_BUTTON p5
#define CHILD_BUTTON p6 
#define FIRE_ALARM_BUTTON p7
#define STOP_BUTTON p8

#define RED_LED p9
#define YELLOW_LED p10
#define BLUE_LED p11

using namespace std;

//Define outputs

	DigitalOut redLed(RED_LED);
	DigitalOut yellowLed(YELLOW_LED);
	DigitalOut blueLed(BLUE_LED);

//Define interrupt inputs

	InterruptIn button1(ADULT_BUTTON);
	InterruptIn button2(CHILD_BUTTON);
	InterruptIn button3(FIRE_ALARM_BUTTON);
	InterruptIn button4(STOP_BUTTON);
	
	volatile bool enabled = false;


class Customer {
	public:
		enum CUSTOMER_TYPE {ADULT, CHILD};
		CUSTOMER_TYPE customerType;
		int timeElapsed;
		
		Customer(): timeElapsed(0) {}
};

	const int HAIRCUT_DURATION = 12;
	const int MAX_WAITING_AREA_SIZE = 8;
	
	Mutex haircutMutex;
	list<Customer> waitingArea;
	Customer* barber1Seat;
	Customer* barber2Seat;
	Customer* barber3Seat;
	

//Adult Button
void button_1_handler(){
	
	haircutMutex.lock();
	
	if (waitingArea.size() == MAX_WAITING_AREA_SIZE) {
		return;
	}
	
	Customer adult;
	adult.customerType = Customer::ADULT;
	waitingArea.push_back(adult);
	
	haircutMutex.unlock();
}

//Child Button
void button_2_handler(){

	haircutMutex.lock();

	if (waitingArea.size() >= MAX_WAITING_AREA_SIZE-1) {
		return;
	}

	Customer child;
	child.customerType = Customer::CHILD;
	waitingArea.push_back(child);
	
	Customer adult;
	adult.customerType = Customer::ADULT;
	waitingArea.push_back(adult);
	
	haircutMutex.unlock();
}

// Fire Alarm Button
void button_3_handler(){
	
	haircutMutex.lock();
	redLed = 0;
	yellowLed = 0;
	blueLed = 0;
	
	waitingArea.clear();
	
	enabled = false;
	haircutMutex.unlock();
}

void button_4_handler(){

	enabled = false;
}


void processCustomers() {
	haircutMutex.lock();

	if (waitingArea.empty())
		return;

	if (redLed == 0 && waitingArea.front().customerType == Customer::ADULT) {
		barber1Seat = &waitingArea.front();
		waitingArea.pop_front();
		redLed = 1;
	} else if (redLed == 1 && barber1Seat->timeElapsed >= HAIRCUT_DURATION) {
		delete barber1Seat;
		barber1Seat = NULL;
		redLed = 0;
	}

	if (yellowLed == 0 && waitingArea.front().customerType == Customer::ADULT) {
		barber2Seat = &waitingArea.front();
		waitingArea.pop_front();
		yellowLed = 1;
	} else if (yellowLed == 1 && barber2Seat->timeElapsed >= HAIRCUT_DURATION) {
		delete barber2Seat;
		barber2Seat = NULL;
		yellowLed = 0;
	}

	if (blueLed == 0 && waitingArea.front().customerType == Customer::CHILD) {
		barber3Seat = &waitingArea.front();
		waitingArea.pop_front();
		blueLed = 1;
	} else if (blueLed == 1 && barber3Seat->timeElapsed >= HAIRCUT_DURATION) {
		delete barber3Seat;
		barber3Seat = NULL;
		blueLed = 0;
	}
	haircutMutex.unlock();
}

void incrementHaircutTime() {
	haircutMutex.lock();
	
	if (barber1Seat) {
		barber1Seat->timeElapsed++;
	}
	
	if (barber2Seat) {
		barber1Seat->timeElapsed++;
	}

	if (barber3Seat) {
		barber1Seat->timeElapsed++;
	}

	haircutMutex.unlock();
}

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/

int main(){

	//Interrupt handlers
	button1.rise(&button_1_handler);
	button2.rise(&button_2_handler);
	button3.rise(&button_3_handler);
	button4.rise(&button_4_handler);	
	
	barber1Seat = NULL;
	barber2Seat = NULL;
	barber3Seat = NULL;

	enabled = true;
	while(enabled) {
		processCustomers();
		wait_ms(1000);
		incrementHaircutTime();
	}
}
