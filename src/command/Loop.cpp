#include "Loop.h"

namespace cmd {

	//--------------------------------------------------------------
	Loop::Loop(string name, int loopCount, Command* target) : Command(name) {
		setup(loopCount, target);
	}

	//--------------------------------------------------------------
	Loop::Loop(int loopCount, Command* target) {
		setup(loopCount, target);
	}

	//--------------------------------------------------------------
	Loop::Loop(Command* target) {
		setup(-1, target);
	}

	//--------------------------------------------------------------
	Loop::~Loop() {
		if (this->target != NULL) {
			this->target = NULL;
		}
		ofLogVerbose() << "Bye Loop";
	}





	//--------------------------------------------------------------
	void Loop::setup(int loopCount, Command* target) {
		this->loopCount = loopCount;
		this->target = target;
		currentCount = 0;
	}





	//--------------------------------------------------------------
	int Loop::getCurrentCount() const {
		return currentCount;
	}

	//--------------------------------------------------------------
	Command* Loop::getTarget() const {
		return target;
	}

	//--------------------------------------------------------------
	void Loop::setTarget(Command* target) {
		this->target = target;
	}

	//--------------------------------------------------------------
	int Loop::getLoopCount() const {
		return loopCount;
	}

	//--------------------------------------------------------------
	void Loop::setLoopCount(int loopCount) {
		this->loopCount = loopCount;
	}





	//--------------------------------------------------------------
	void Loop::runFunction(Command* command) {
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
			target->run();
		}
	}

	//--------------------------------------------------------------
	void Loop::completeHandler(Command& command) {
		++currentCount;
		checkComplete();
	}
}




