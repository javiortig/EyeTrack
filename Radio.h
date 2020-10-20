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
				#pragma once

/*Routing Library n emisors talking to 1 receptor. emisors id should start from 1 with a 1 step up(1, 2, 3..). Receptor should have id 00*/

#include "SoftwareSerial.h"
#include "LowPower.h"
#include "vector.h"

#define COMMAND_LEN 2
#define EMISOR_LEN 2
#define DATALEN_LEN 2

// ((unsigned long)(currentMillis - previousMillis) >= interval). used for avoiding rollover of millis()

//default values
#define VCC 2
#define RD 4
#define TD 3
#define SET 5
#define B_RATE 9600
#define START_C '/'
#define END_C ';'

#define RECEPTOR_ID 99

#define ACK_COUNTER 4

//TWH values
#define TWH_COMMAND 0
#define TWH_LENVALUE 3
#define TWH_SYN "000"
#define TWH_SYNACK "001"
#define TWH_ACK "002"

//other commands
#define SETUP_COMMAND 99
#define BOOLEAN_COMMAND 1 //used for boolean sensors

struct Message{
			 int command;
		  int emisor;
     int dataLen;
     String data;
				
				Message(){
								this->command = -1;
								this->emisor = -1;
								this->dataLen = -1;
								this->data = "";
				}
};

class Radio{
protected:
				//Attributes
				int sensorCount; //Nunber of sensors(Receptor not included) in the system
				SoftwareSerial* hc12;
				
				short int vcc;
				short int rd;
				short int td;
				short int set;
				
				int bRate;
				int id; // from 0 to 99. Use 99 only on Receptor
				
				String buffer;
				
				int currentChannel;
				
				unsigned long timeOut; // Longer for Emisors, Shorter for Receptor, in seconds. TODO: increase in Emisor for every other emisor
				
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
				//Attributes
				bool debugging;
				Message message; //used for sending messages of type twh
				
				//methods
				void clearBuffer();
				
				void debug(String s, bool line);
				void debug(int i, bool line);
				
				bool changeChannel(int channel);
				bool readMessage(bool clear = true); //set clear to clearbuffer before read. if;no;msg found, sets message to default values
				bool messageCmp(Message m, bool _anyCommand = false, bool _anyEmisor = false, bool _anyData = false); //compares values between class Message and parameter
				void sendMessage(Message m);
				
				virtual bool twh() = 0; //router tries to syn, emisor answers with synack and router finnaly with ack and waits for data
				virtual void routine() = 0;//called in arduinos loop
				
				//constructor and destructors:
				Radio(int _id,short int _vcc = VCC, short int _td = TD, short int _rd = RD, short int _set = SET, int bRate = B_RATE);
				
				~Radio();
};
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
