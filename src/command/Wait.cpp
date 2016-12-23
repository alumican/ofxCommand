#include "Wait.h"

namespace cmd {

	//--------------------------------------------------------------
	Wait::Wait(string name, float duration, bool isFrameBased) : Command(name) {
		setup(duration, isFrameBased);
	}

	//--------------------------------------------------------------
	Wait::Wait(float duration, bool isFrameBased) {
		setup(duration, isFrameBased);
	}

	//--------------------------------------------------------------
	Wait::~Wait() {
		ofLogVerbose() << "Bye Wait";
	}





	//--------------------------------------------------------------
	float Wait::getDuration() const {
		return duration;
	}

	//--------------------------------------------------------------
	void Wait::setDuration(float duration) {
		this->duration = duration;
	}

	//--------------------------------------------------------------
	bool Wait::getIsFrameBased() const {
		return isFrameBased;
	}

	//--------------------------------------------------------------
	void Wait::setIsFrameBased(bool isFrameBased) {
		this->isFrameBased = isFrameBased;
	}





	//--------------------------------------------------------------
	void Wait::runFunction(Command* command) {
		if (isFrameBased) {
			startTime = ofGetFrameNum();
		} else {
			startTime = ofGetElapsedTimef();
		}
		ofAddListener(ofEvents().update, this, &Wait::update);
		checkComplete();
	}

	//--------------------------------------------------------------
	void Wait::interruptFunction(Command* command) {
		ofRemoveListener(ofEvents().update, this, &Wait::update);
	}

	//--------------------------------------------------------------
	void Wait::resetFunction(Command* command) {
		interruptFunction(command);
	}





	//--------------------------------------------------------------
	void Wait::setup(float duration, bool isFrameBased) {
		this->duration = duration;
		this->isFrameBased = isFrameBased;
	}

	//--------------------------------------------------------------
	void Wait::update(ofEventArgs& event) {
		checkComplete();
	}





	//--------------------------------------------------------------
	void Wait::checkComplete() {
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
}




