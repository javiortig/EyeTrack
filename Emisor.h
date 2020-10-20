#pragma once

#include "Radio.h"

class Emisor: protected Radio{
private:
				//variables
				
				
				
				//methods
				
				
public:
				//variables
				
				
				//methods
				
				
				//constructor and destructors:
				
				Emisor();
				~Emisor();
};
#pragma once

#include "Radio.h"

#define EMISOR_BASE_TIMEOUT 600000 //10 min in millis
#define EMISOR_BASE_SLEEPTIME 28800 //8h in seconds
#define WAKEUP_OFFSET_TIME 1.52 //in s, time arduino usually takes between wake up and new sleep

class Emisor: protected Radio{
private:
				//Attributes
				Message data;
				unsigned long sleepTime;
				
				//methods
				void sleep(unsigned long _sleepTime); //TODO: Turn off all sensors for minimun comsumption(prob create array with extra pins used)
				
public:
				//Attributes
				Message (*dataCollector)(); //pointer to the function which collects data from sensors. the fun should;be created in the main .ino file
				
				//methods
				bool twh();
				bool sendData(Message m);//call after twh
				void routine();
				
				Message getData();
				
				//constructor and destructors:
				Emisor(int _id, Message (*_dataCollector)(), unsigned long _sleepTime = EMISOR_BASE_SLEEPTIME, short int _vcc = VCC, short int _td = TD, short int _rd = RD, short int _set = SET, int bRate = B_RATE);		
				~Emisor();
				
};
