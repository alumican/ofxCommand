#include "Log.h"

namespace cmd {

	//--------------------------------------------------------------
	Log::Log(const string& message, ofLogLevel level) {
		this->message = message;
		this->level = level;
	}

	//--------------------------------------------------------------
	Log::~Log() {
		ofLogVerbose() << "Bye Log";
	}





	//--------------------------------------------------------------
	const string& Log::getMessage() {
		return message;
	}

	//--------------------------------------------------------------
	void Log::setMessage(const string& message) {
		this->message = message;
	}

	//--------------------------------------------------------------
	ofLogLevel Log::getLevel() {
		return level;
	}

	//--------------------------------------------------------------
	void Log::setLevel(ofLogLevel level) {
		this->level = level;
	}





	//--------------------------------------------------------------
	void Log::executeFunction(Command* command) {
		ofLog(level) << message;
		notifyComplete();
	}

	//--------------------------------------------------------------
	void Log::interruptFunction(Command* command) {
	}

	//--------------------------------------------------------------
	void Log::resetFunction(Command* command) {
	}
}




