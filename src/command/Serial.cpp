#include "command/Serial.h"

using namespace command;

//--------------------------------------------------------------
Serial::Serial() {
	currentCommand = NULL;
	position = 0;
}




//--------------------------------------------------------------
Serial::Serial(const vector<Command*>& commands) : CommandList(commands) {
	Serial();
}





//--------------------------------------------------------------
Serial::~Serial() {
	if (currentCommand != NULL) {
		ofRemoveListener(currentCommand->onComplete, this, &Serial::_complete);
		currentCommand = NULL;
	}
	ofLogVerbose() << "Bye Serial";
}





//--------------------------------------------------------------
void Serial::insert(const vector<Command*>& commands) {
	CommandList::insert(position + 1, commands);
}





//--------------------------------------------------------------
int Serial::getPosition() {
	return position;
}





//--------------------------------------------------------------
void Serial::next() {
	currentCommand = getCommand(position);
	ofAddListener(currentCommand->onComplete, this, &Serial::_complete);
	currentCommand->execute();
}





//--------------------------------------------------------------
void Serial::_complete(Command& command) {
	ofRemoveListener(currentCommand->onComplete, this, &Serial::_complete);
	currentCommand = NULL;
	if (++position >= getNumCommands()) {
		notifyComplete();
	} else {
		next();
	}
}





//--------------------------------------------------------------
void Serial::_notifyBreak() {
	if (currentCommand != NULL && currentCommand->getState() == CommandState::EXECUTING) {
		ofRemoveListener(currentCommand->onComplete, this, &Serial::_complete);
		currentCommand->interrupt();
	}
	CommandList::_notifyBreak();
}





//--------------------------------------------------------------
void Serial::_notifyReturn() {
	if (currentCommand != NULL && currentCommand->getState() == CommandState::EXECUTING) {
		ofRemoveListener(currentCommand->onComplete, this, &Serial::_complete);
		currentCommand->interrupt();
	}
	CommandList::_notifyReturn();
}





//--------------------------------------------------------------
void Serial::executeFunction(Command* command) {
	position = 0;
	if (getNumCommands() > 0) {
		next();
	} else {
		notifyComplete();
	}
}





//--------------------------------------------------------------
void Serial::interruptFunction(Command* command) {
	if (currentCommand != NULL) {
		ofRemoveListener(currentCommand->onComplete, this, &Serial::_complete);
		currentCommand->interrupt();
		currentCommand = NULL;
	}
	position = 0;
	CommandList::interruptFunction(command);
}




