#include "Loop.h"

namespace cmd {

	//--------------------------------------------------------------
	Loop::Loop(Command* target, int loopCount) {
		this->target = target;
		this->loopCount = loopCount;
		currentCount = 0;
	}

	//--------------------------------------------------------------
	Loop::~Loop() {
		if (this->target != NULL) {
			this->target = NULL;
		}
		ofLogVerbose() << "Bye Loop";
	}





	//--------------------------------------------------------------
	int Loop::getCurrentCount() {
		return currentCount;
	}

	//--------------------------------------------------------------
	Command* Loop::getTarget() {
		return target;
	}

	//--------------------------------------------------------------
	void Loop::setTarget(Command* target) {
		this->target = target;
	}

	//--------------------------------------------------------------
	int Loop::getLoopCount() {
		return loopCount;
	}

	//--------------------------------------------------------------
	void Loop::setLoopCount(int loopCount) {
		this->loopCount = loopCount;
	}





	//--------------------------------------------------------------
	void Loop::executeFunction(Command* command) {
		currentCount = 0;
		if (target != NULL) {
			ofAddListener(target->onComplete, this, &Loop::completeHandler);
			checkComplete();
		} else {
			notifyComplete();
		}
	}

	//--------------------------------------------------------------
	void Loop::interruptFunction(Command* command) {
		if (target != NULL) {
			ofRemoveListener(target->onComplete, this, &Loop::completeHandler);
			target->interrupt();
		}
	}

	//--------------------------------------------------------------
	void Loop::resetFunction(Command* command) {
		currentCount = 0;
		if (target != NULL) {
			ofRemoveListener(target->onComplete, this, &Loop::completeHandler);
			target->reset();
		}
	}





	//--------------------------------------------------------------
	void Loop::checkComplete() {
		if (loopCount >= 0 && currentCount >= loopCount) {
			ofRemoveListener(target->onComplete, this, &Loop::completeHandler);
			notifyComplete();
		} else {
			if (currentCount > 0) {
				target->reset();
			}
			target->execute();
		}
	}

	//--------------------------------------------------------------
	void Loop::completeHandler(Command& command) {
		++currentCount;
		checkComplete();
	}
}




