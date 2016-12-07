#include "Parallel.h"

namespace cmd {

	//--------------------------------------------------------------
	Parallel::Parallel() {
		completeCount = 0;
	}

	//--------------------------------------------------------------
	Parallel::Parallel(const vector<Command*>& commands) : CommandList(commands) {
		Parallel();
	}

	//--------------------------------------------------------------
	Parallel::~Parallel() {
		vector<Command*>* commands = &getCommands();
		for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
			ofRemoveListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
		}
		//destroy();
		ofLogVerbose() << "Bye Parallel";
	}





	//--------------------------------------------------------------
	void Parallel::insert(const vector<Command*>& commands) {
		CommandList::add(commands);
	}





	//--------------------------------------------------------------
	int Parallel::getCompleteCount() {
		return completeCount;
	}





	//--------------------------------------------------------------
	void Parallel::currentCommandCompleteHandler(Command& command) {
		ofRemoveListener(command.onComplete, this, &Parallel::currentCommandCompleteHandler);
		if (++completeCount >= getNumCommands()) {
			notifyComplete();
		}
	}





	//--------------------------------------------------------------
	void Parallel::_notifyBreak() {
		vector<Command*>* commands = &getCommands();
		for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
			ofRemoveListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
			(*it)->interrupt();
		}
		CommandList::_notifyBreak();
	}

	//--------------------------------------------------------------
	void Parallel::_notifyReturn() {
		vector<Command*>* commands = &getCommands();
		for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
			ofRemoveListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
			(*it)->interrupt();
		}
		CommandList::_notifyReturn();
	}





	//--------------------------------------------------------------
	void Parallel::executeFunction(Command* command) {
		completeCount = 0;
		if (getNumCommands() > 0) {
			vector<Command*>* commands = &getCommands();
			for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
				ofAddListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
				(*it)->execute();
			}
		} else {
			notifyComplete();
		}
	}

	//--------------------------------------------------------------
	void Parallel::interruptFunction(Command* command) {
		vector<Command*>* commands = &getCommands();
		for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
			ofRemoveListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
			(*it)->interrupt();
		}
		CommandList::interruptFunction(command);
	}

	//--------------------------------------------------------------
	void Parallel::resetFunction(Command* command) {
		vector<Command*>* commands = &getCommands();
		for (vector<Command*>::iterator it = commands->begin(); it!= commands->end(); ++it) {
			ofRemoveListener((*it)->onComplete, this, &Parallel::currentCommandCompleteHandler);
			(*it)->reset();
		}
		completeCount = 0;
		CommandList::resetFunction(command);
	}
}




