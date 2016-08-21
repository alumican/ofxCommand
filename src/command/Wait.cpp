#include "command/Wait.h"

using namespace command;

//--------------------------------------------------------------
Wait::Wait(float duration, bool isFrameBased) {
	this->duration = duration;
	this->isFrameBased = isFrameBased;
}





//--------------------------------------------------------------
Wait::~Wait() {
	ofLogVerbose() << "Bye Wait";
}





//--------------------------------------------------------------
float Wait::getDuration() {
	return duration;
}





//--------------------------------------------------------------
void Wait::setDuration(float duration) {
	this->duration = duration;
}





//--------------------------------------------------------------
bool Wait::getIsFrameBased() {
	return isFrameBased;
}





//--------------------------------------------------------------
void Wait::setIsFrameBased(bool isFrameBased) {
	this->isFrameBased = isFrameBased;
}





//--------------------------------------------------------------
void Wait::executeFunction(Command* command) {
	if (isFrameBased) {
		startTime = ofGetFrameNum();
	} else {
		startTime = ofGetElapsedTimef();
	}
	ofAddListener(ofEvents().update, this, &Wait::update);
}





//--------------------------------------------------------------
void Wait::interruptFunction(Command* command) {
	ofRemoveListener(ofEvents().update, this, &Wait::update);
}





//--------------------------------------------------------------
void Wait::update(ofEventArgs& event) {
	bool isCompleted = false;
	if (isFrameBased) {
		if (ofGetFrameNum() >= startTime + duration) {
			isCompleted = true;
		}
	} else {
		if (ofGetElapsedTimef() >= startTime + duration) {
			isCompleted = true;
		}
	}
	if (isCompleted) {
		ofRemoveListener(ofEvents().update, this, &Wait::update);
		notifyComplete();
	}
}




