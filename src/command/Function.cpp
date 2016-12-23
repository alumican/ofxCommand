#include "Function.h"

namespace cmd {

	//--------------------------------------------------------------
	Function::Function() {
		this->f = NULL;
	}

	//--------------------------------------------------------------
	Function::Function(const function<void()>& f) {
		this->f = f;
	}

	//--------------------------------------------------------------
	Function::~Function() {
		f = NULL;
		ofLogVerbose() << "Bye Function";
	}





	//--------------------------------------------------------------
	function<void()> Function::getFunction() const {
		return f;
	}

	//--------------------------------------------------------------
	void Function::setFunction(const function<void()>& f) {
		this->f = f;
	}





	//--------------------------------------------------------------
	void Function::runFunction(Command* command) {
		if (f != NULL) {
			f();
		}
		notifyComplete();
	}

	//--------------------------------------------------------------
	void Function::interruptFunction(Command* command) {
	}


	//--------------------------------------------------------------
	void Function::resetFunction(Command* command) {
	}
}




