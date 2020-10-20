#include <Emisor.h>

Emisor::Emisor(){
				
}

Emisor::~Emisor(){
				
}
#include "Emisor.h"

Message Emisor::getData(){
				return this->data;
}

void Emisor::routine(){
				this->data = this->dataCollector();
				
				if (this->twh()){
								this->sendData(this->data);
				}
				
				if (this->sleepTime > 8){
								this->sleep(this->sleepTime);
				}
}

void Emisor::sleep(unsigned long _sleepTime){
				int sleepCont;
				sleepCont = (int)(_sleepTime/(8 +WAKEUP_OFFSET_TIME));
				
			_stophc12();
			if (debugging){
								digitalWrite(LED_BUILTIN, LOW);
				}
				
     for(int i=0; i< sleepCont;i++){
								LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
				}
				
				if (debugging){
								digitalWrite(LED_BUILTIN, HIGH);
				}
				_starthc12();
}#include "Emisor.h"

Message Emisor::getData(){
				return this->data;
}

void Emisor::routine(){
				this->data = this->dataCollector();
				
				if (this->twh()){
								this->sendData(this->data);
				}
				
				if (this->sleepTime > 8){
								this->sleep(this->sleepTime);
				}
}

void Emisor::sleep(unsigned long _sleepTime){
				int sleepCont;
				sleepCont = (int)(_sleepTime/(8 +WAKEUP_OFFSET_TIME));
				
			_stophc12();
			if (debugging){
								digitalWrite(LED_BUILTIN, LOW);
				}
				
     for(int i=0; i< sleepCont;i++){
								LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
				}
				
				if (debugging){
								digitalWrite(LED_BUILTIN, HIGH);
				}
				_starthc12();
}

bool Emisor::sendData(Message m){
				bool answered = false;
				unsigned long stime, dtime;
				Message ack;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				while (!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								this->sendMessage(m);
								
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
								
								dtime = millis();
				}
				if (!answered){
								return false;
				}
								
    return true;
}

bool Emisor::twh(){
				Message syn, synack, ack;
				bool answered = false;
				int i;
				unsigned long stime, dtime;
				
				syn.command = TWH_COMMAND;
				syn.emisor = RECEPTOR_ID;
				syn.dataLen = TWH_LENVALUE;
				syn.data = TWH_SYN;
				
				synack.command = TWH_COMMAND;
				synack.emisor = this->id;
				synack.dataLen = TWH_LENVALUE;
				synack.data = TWH_SYNACK;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								delay(4000);
								if (this->readMessage()){
												// syn received
												if(this->messageCmp(synack)){
																answered = true;
																break;
												}
								}
								
								
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				
				answered = false;
				stime = millis();
				dtime = millis();
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								//send synack
								this->sendMessage(synack);
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
							
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				return true;
}

Emisor::Emisor(int _id, Message (*_dataCollector)(), unsigned long _sleepTime, short int _vcc, short int _td, short int _rd, short int _set, int _bRate) : Radio(_id, _vcc,  _td, _rd, _set, _bRate){
				
				this->timeOut = EMISOR_BASE_TIMEOUT;
				this->dataCollector = _dataCollector;
				this->sleepTime = _sleepTime;
}

Emisor::~Emisor(){
				
}



bool Emisor::sendData(Message m){
				bool answered = false;
				unsigned long stime, dtime;
				Message ack;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;#include "Emisor.h"

Message Emisor::getData(){
				return this->data;
}

void Emisor::routine(){
				this->data = this->dataCollector();
				
				if (this->twh()){
								this->sendData(this->data);
				}
				
				if (this->sleepTime > 8){
								this->sleep(this->sleepTime);
				}
}

void Emisor::sleep(unsigned long _sleepTime){
				int sleepCont;
				sleepCont = (int)(_sleepTime/(8 +WAKEUP_OFFSET_TIME));
				
			_stophc12();
			if (debugging){
								digitalWrite(LED_BUILTIN, LOW);
				}
				
     for(int i=0; i< sleepCont;i++){
								LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
				}
				
				if (debugging){
								digitalWrite(LED_BUILTIN, HIGH);
				}
				_starthc12();
}

bool Emisor::sendData(Message m){
				bool answered = false;
				unsigned long stime, dtime;
				Message ack;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				while (!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								this->sendMessage(m);
								
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
								
								dtime = millis();
				}
				if (!answered){
								return false;
				}
								
    return true;
}

bool Emisor::twh(){
				Message syn, synack, ack;
				bool answered = false;
				int i;
				unsigned long stime, dtime;
				
				syn.command = TWH_COMMAND;
				syn.emisor = RECEPTOR_ID;
				syn.dataLen = TWH_LENVALUE;
				syn.data = TWH_SYN;
				
				synack.command = TWH_COMMAND;
				synack.emisor = this->id;
				synack.dataLen = TWH_LENVALUE;
				synack.data = TWH_SYNACK;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								delay(4000);
								if (this->readMessage()){
												// syn received
												if(this->messageCmp(synack)){
																answered = true;
																break;
												}
								}
								
								
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				
				answered = false;
				stime = millis();
				dtime = millis();
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								//send synack
								this->sendMessage(synack);
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
							
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				return true;
}

Emisor::Emisor(int _id, Message (*_dataCollector)(), unsigned long _sleepTime, short int _vcc, short int _td, short int _rd, short int _set, int _bRate) : Radio(_id, _vcc,  _td, _rd, _set, _bRate){
				
				this->timeOut = EMISOR_BASE_TIMEOUT;
				this->dataCollector = _dataCollector;
				this->sleepTime = _sleepTime;
}

Emisor::~Emisor(){
				
}


				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				while (!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								this->sendMessage(m);
								
								delay(4000);
								if (this->readMessage()){#include "Emisor.h"

Message Emisor::getData(){
				return this->data;
}

void Emisor::routine(){
				this->data = this->dataCollector();
				
				if (this->twh()){
								this->sendData(this->data);
				}
				
				if (this->sleepTime > 8){
								this->sleep(this->sleepTime);
				}
}

void Emisor::sleep(unsigned long _sleepTime){
				int sleepCont;
				sleepCont = (int)(_sleepTime/(8 +WAKEUP_OFFSET_TIME));
				
			_stophc12();
			if (debugging){
								digitalWrite(LED_BUILTIN, LOW);
				}
				
     for(int i=0; i< sleepCont;i++){
								LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
				}
				
				if (debugging){
								digitalWrite(LED_BUILTIN, HIGH);
				}
				_starthc12();
}

bool Emisor::sendData(Message m){
				bool answered = false;
				unsigned long stime, dtime;
				Message ack;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				while (!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								this->sendMessage(m);
								
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
								
								dtime = millis();
				}
				if (!answered){
								return false;
				}
								
    return true;
}

bool Emisor::twh(){
				Message syn, synack, ack;
				bool answered = false;
				int i;
				unsigned long stime, dtime;
				
				syn.command = TWH_COMMAND;
				syn.emisor = RECEPTOR_ID;
				syn.dataLen = TWH_LENVALUE;
				syn.data = TWH_SYN;
				
				synack.command = TWH_COMMAND;
				synack.emisor = this->id;
				synack.dataLen = TWH_LENVALUE;
				synack.data = TWH_SYNACK;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								delay(4000);
								if (this->readMessage()){
												// syn received
												if(this->messageCmp(synack)){
																answered = true;
																break;
												}
								}
								
								
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				
				answered = false;
				stime = millis();
				dtime = millis();
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								//send synack
								this->sendMessage(synack);
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
							
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				return true;
}

Emisor::Emisor(int _id, Message (*_dataCollector)(), unsigned long _sleepTime, short int _vcc, short int _td, short int _rd, short int _set, int _bRate) : Radio(_id, _vcc,  _td, _rd, _set, _bRate){
				
				this->timeOut = EMISOR_BASE_TIMEOUT;
				this->dataCollector = _dataCollector;
				this->sleepTime = _sleepTime;
}

Emisor::~Emisor(){
				
}


												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
								
								dtime = millis();
				}
				if (!answered){
								return false;
				}
								
    return true;
}

bool Emisor::twh(){
				Message syn, synack, ack;
				bool answered = false;
				int i;
				unsigned long stime, dtime;
				
				syn.command = TWH_COMMAND;
				syn.emisor = RECEPTOR_ID;
				syn.dataLen = TWH_LENVALUE;
				syn.data = TWH_SYN;
				
				synack.command = TWH_COMMAND;
				synack.emisor = this->id;
				synack.dataLen = TWH_LENVALUE;
				synack.data = TWH_SYNACK;
				
				ack.command = TWH_COMMAND;
				ack.emisor = RECEPTOR_ID;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = stime;
				
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								delay(4000);
								if (this->readMessage()){
												// syn received
												if(this->messageCmp(synack)){
																answered = true;
																break;
												}
								}
								
								
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				
				answered = false;
				stime = millis();
				dtime = millis();
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								//send synack
								this->sendMessage(synack);
								delay(4000);
								if (this->readMessage()){
												// ack received
												if(this->messageCmp(ack)){
																answered = true;
																break;
												}
								}
							
								dtime = millis();
				}
				if(!answered){
								return false;
				}
				
				return true;
}

Emisor::Emisor(int _id, Message (*_dataCollector)(), unsigned long _sleepTime, short int _vcc, short int _td, short int _rd, short int _set, int _bRate) : Radio(_id, _vcc,  _td, _rd, _set, _bRate){
				
				this->timeOut = EMISOR_BASE_TIMEOUT;
				this->dataCollector = _dataCollector;
				this->sleepTime = _sleepTime;
}

Emisor::~Emisor(){
				
}

