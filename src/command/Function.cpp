#include "Function.h"

namespace cmd {

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
	function<void()> Function::getFunction() {
		return f;
	}

	//--------------------------------------------------------------
	void Function::setFunction(const function<void()>& f) {
		this->f = f;
	}





	//--------------------------------------------------------------
	void Function::executeFunction(Command* command) {
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




