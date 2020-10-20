#pragma once

#include "Radio.h"

class Receptor: protected Radio{
private:
				//variables
				
				
				//methods
				
				
public:
				//variables
				
				
				//methods
				
				
				//constructor and destructors:
				
				Receptor();
				~Receptor();
};
#pragma once

#include "Radio.h"

//TODO: posibilidad de anadir un emisor al receptor automaticanente mediante el serial o que el emisor se auto anada al conectarse por un canal especial


#define RECEPTOR_BASE_TIMEOUT 30000 //30 sec

struct EmisorInfo{
				int id;
				int timeOutCounter; //how many times the receptor tried to communicate with;no;response
				Vector<String[COMMAND_LEN]> commands; //an emisor can have multiple sensors
				Vector<String> data; //shares index with commands. ex: command[0] shares with data[0]
				
				EmisorInfo(){
								this->id = -1; //default
				}
				
				EmisorInfo(int _id, Vector<String[COMMAND_LEN]> _commands){
								this->id = _id;
								this->commands = _commands;
				}
				
				~EmisorInfo(){
								commands.clear();
								data.clear();
				}
};


class Receptor: protected Radio{
private:
				//Attributes
				Vector<EmisorInfo> emisorList;
				
				//methods
				int getEmisorIndex(int _id); //-1 if not found
				
public:
				//Attributes
				
				//methods
				bool twh();
				bool receiveData();//call after twh
				void handleData();
				void routine();
				
				EmisorInfo getEmisorInfo(int _id); //Return Null if not found
				bool addEmisor(EmisorInfo _info);// id will be set here. return true if succesful
				bool removeEmisor(int _id);
				
				//constructor and destructors:
				Receptor(int _sensorCount,int _id = RECEPTOR_ID, short int _vcc = VCC, short int _td = TD, short int _rd = RD, short int _set = SET, int bRate = B_RATE);
				~Receptor();
				
};
