#include "Command.h"

namespace cmd {

	map<string, Command*> Command::commandsByName;





	//--------------------------------------------------------------
	Command::Command(string name) {
		state = CommandState::SLEEPING;
		parent = NULL;
		deleteOnComplete = false;

		this->name = "";
		setName(name);
	}

	//--------------------------------------------------------------
	Command::~Command() {
		parent = NULL;
		removeCommandByName(name);
	}





	//--------------------------------------------------------------
	void Command::execute() {
		if (state > CommandState::SLEEPING) {
			ofLogError() << "Command is already executing.";
		} else {
			state = CommandState::EXECUTING;
			executeFunction(this);
		}
	}

	//--------------------------------------------------------------
	void Command::interrupt() {
		if (state == CommandState::EXECUTING) {
			state = CommandState::INTERRUPTING;
			interruptFunction(this);
		}
	}

	//--------------------------------------------------------------
	void Command::reset() {
		if (state > CommandState::SLEEPING) {
			state = CommandState::SLEEPING;
			resetFunction(this);
		}
	}





	//--------------------------------------------------------------
	void Command::notifyComplete() {
		//ofLog() << "notifyComplete : state = " << state << ", deleteOnComplete = " << deleteOnComplete;
		switch (state) {
			case CommandState::SLEEPING:
				break;
			case CommandState::EXECUTING:
			case CommandState::INTERRUPTING:
				ofNotifyEvent(onComplete, *this);
				//TODO: FIX (Why deleteOnComplete is true automatically ???)
				//if (deleteOnComplete) {
				//	delete this;
				//}
				break;
		}
	}





	//--------------------------------------------------------------
	string Command::getName() {
		return name;
	}

	//--------------------------------------------------------------
	void Command::setName(string name) {
		if (name == this->name) return;
		removeCommandByName(this->name);
		registerCommandByName(name, this);
		this->name = name;
	}

	//--------------------------------------------------------------
	CommandState Command::getState() {
		return state;
	}

	//--------------------------------------------------------------
	Command* Command::getParent() {
		return parent;
	}

	//--------------------------------------------------------------
	bool Command::getDeleteOnComplete() {
		return deleteOnComplete;
	}

	//--------------------------------------------------------------
	void Command::setDeleteOnComplete(bool value) {
		deleteOnComplete = value;
	}

	//--------------------------------------------------------------
	void Command::_setParent(Command* parent) {
		this->parent = parent;
	}





	//--------------------------------------------------------------
	void Command::executeFunction(Command* command) {
		notifyComplete();
	}

	//--------------------------------------------------------------
	void Command::interruptFunction(Command* command) {
	}

	//--------------------------------------------------------------
	void Command::resetFunction(Command* command) {
	}




	//--------------------------------------------------------------
	void Command::_notifyBreak() {
		notifyComplete();
	}

	//--------------------------------------------------------------
	void Command::_notifyReturn() {
		Command* parent = getParent();
		if (parent != NULL) {
			parent->_notifyReturn();
		} else {
			notifyComplete();
		}
	}




	//--------------------------------------------------------------
	Command* Command::getCommandByName(string name) {
		return commandsByName.count(name) > 0 ? commandsByName[name] : NULL;
	}

	//--------------------------------------------------------------
	void Command::registerCommandByName(string name, Command* command) {
		if (name == "") return;
		if (commandsByName.count(name) == 0) {
			commandsByName[name] = command;
		} else {
			ofLogError() << "Command name is duplicated : name = " << name;
		}
	}

	//--------------------------------------------------------------
	void Command::removeCommandByName(string name) {
		if (name == "") return;
		commandsByName.erase(name);
	}
}




