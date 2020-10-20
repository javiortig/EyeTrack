#include <Receptor.h>

Receptor::Receptor(){
				
}

Receptor::~Receptor(){
				
}

#include "Receptor.h"

void Receptor::routine(){
				if (this->twh()){
				    if(receiveData()){
												handleData();
				    }
				}
				
}

void Receptor::handleData(){
			switch(this->message.command){
								case TWH_COMMAND:
								
								break;
								case
				}
}

int Receptor::getEmisorIndex(int _id){
				int size = this->emisorList.size();
				
				//try fast search(will work if arrenged)
				if (size > _id && this->emisorList[_id].id == _id){
								return _id;
				}
				
				//else go for slow search
     for(int i=0; i<size; i++){
								if (this->emisorList[_id].id == _id){
												return i;
								}
				}
				
				return -1;
}

EmisorInfo Receptor::getEmisorInfo(int _id){
				int i;
				
				i = getEmisorIndex(_id);
				//TODO: comprpbar que se copia el;objeto y se destruye y tambien que al copiarse en;el main se cree un vector nuevo
				if(i == -1){
								return EmisorInfo(); //returns default EmisorInfo
				}
				else{
								return this->emisorList[i];
				}
}

bool Receptor::removeEmisor(int _id){
				int i;
				
				i = getEmisorIndex(_id);
				if(i == -1){
								return false;
				}
				else{
								this->emisorList.remove(i);
								return true;
				}
}

//TODO: optimize
bool Receptor::addEmisor(EmisorInfo _info){
				//search for a new id
				int i, size;
				int newId = -1;
				size = this->emisorList.size();			
				if (size > EMISOR_LEN -1){ //we are full
								return false;
				}
				
				//search for a free id
				for(i = 0; i < size; i++){
								newId = getEmisorIndex(i);
								if (newId == -1){ //free id found
												_info.id = newId;
												//aTODO: insert instead of push back
												this->emisorList.push_back(_info);
												return true;
								}
				}
				
				return false;
}

bool Receptor::receiveData(){
				unsigned long stime, dtime;
				bool answered = false;
				Message ack;
				
				ack.command = TWH_COMMAND;
				ack.emisor = this->id;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				_setMessageDefault();
				stime = millis();
				dtime = stime;
				while ((!answered) && (unsigned long)(dtime - stime) >= this->timeOut){
								delay(4000);
								readMessage();
								if (message.emisor == currentChannel && message.command != TWH_COMMAND){
												answered = true;
								}
								else{
												_setMessageDefault();
								}
								
								dtime = millis();
				}
				if (!answered){
								return false;
				}
				
				//send ACK
				for (int i=0; i<ACK_COUNTER; i++){
								this->sendMessage(ack);
								delay(4000);
				}
				
				return true;
}

bool Receptor::twh(){
				Message syn, synack, ack;
				bool answered = false;
				int i;
				unsigned long stime, dtime;
				
				syn.command = TWH_COMMAND;
				syn.emisor = this->id;
				syn.dataLen = TWH_LENVALUE;
				syn.data = TWH_SYN;
				
				synack.command = TWH_COMMAND;
				synack.emisor = this->currentChannel;
				synack.dataLen = TWH_LENVALUE;
				synack.data = TWH_SYNACK;
				
				ack.command = TWH_COMMAND;
				ack.emisor = this->id;
				ack.dataLen = TWH_LENVALUE;
				ack.data = TWH_ACK;
				
				stime = millis();
				dtime = millis();
				
				while(!answered && ((unsigned long)(dtime - stime) >= this->timeOut)){
								//send syn
								this->sendMessage(syn);
								delay(4000);
								if (this->readMessage()){
												// synack received
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
				
				//send ACK
				for (i=0; i<ACK_COUNTER; i++){
								this->sendMessage(ack);
								delay(4000);
				}
				
				return true;
}


Receptor::Receptor(int _sensorCount, int _id, short int _vcc, short int _td, short int _rd, short int _set, int _bRate) : Radio(_id, _vcc,  _td, _rd, _set, _bRate){
				
				this->timeOut = RECEPTOR_BASE_TIMEOUT;
				this->sensorCount = _sensorCount;
}

Receptor::~Receptor(){
				
}

