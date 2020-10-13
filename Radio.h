#pragma once

#include <SoftwareSerial.h>
#include <LowPower.h>

#define COMMAND_LEN 2
#define EMISOR_LEN 2
#define DATALEN_LEN 2

//default values
#define VCC 2
#define RD 4
#define TD 3
#define SET 5
#define B_RATE 9600
#define START_C '/'
#define END_C ';'

class Radio{
protected:
				//variables
				SoftwareSerial* hc12;
				
				short int vcc;
				short int rd;
				short int td;
				short int set;
				
				int bRate;
				
				String buffer;
				
				int currentChannel;
				
				//methods
				void _clearhc12(); // clears hc12 buffer
				String _readhc12(); 
				void _starthc12();
				void _stophc12();
				bool _searchInBuffer(); // returns true if msg converted
				bool _isDigit(char c);
				int _stoi(String s); //only positive
				int _pow(int b, int e);
				void _setMessageDefault();
				
public:
				struct Message{
		    		int command;
		     	int emisor;
        int dataLen;
        String data;
     };
				//variables
				bool debugging;
				Message message;
				
				//methods
				void clearBuffer();
				
				void debug(String s, bool line);
				void debug(int i, bool line);
				
				void sleep(int _sleepCont);
				bool changeChannel(int channel);
				bool readMessage(bool clear = true); //set clear to clearbuffer before read. if;no;msg found, sets message to default values
				
				virtual bool twh() = 0;
				
				//constructor and destructors:
				Radio(short int _vcc = VCC, short int _td = TD, short int _rd = RD, short int _set = SET, int bRate = B_RATE);
				Radio();
				~Radio();
};
