#include "command/CommandList.h"

using namespace command;

//--------------------------------------------------------------
CommandList::CommandList() {
}





//--------------------------------------------------------------
CommandList::CommandList(const vector<Command*>& commands) {
	this->commands = commands;
}





//--------------------------------------------------------------
CommandList::~CommandList() {
	/*
	while(commands.size() > 0) {
		Command* command = *commands.erase(commands.begin());
		delete command;
	}
	*/

	/*
	for (vector<Command*>::iterator it = commands.begin(); it!= commands.end();) {
		Command* command = *it;
		it = commands.erase(it);
		//delete command;
	}
	*/

	commands.clear();
}





//--------------------------------------------------------------
void CommandList::add(const vector<Command*>& commands) {
	if (commands.size() > 0) {
		setParentToCommands(commands);
		copy(commands.begin(), commands.end(), back_inserter(this->commands));
	}
}





//--------------------------------------------------------------
void CommandList::insert(const vector<Command*>& commands) {
}





//--------------------------------------------------------------
void CommandList::insert(int index, const vector<Command*>& commands) {
	if (commands.size() > 0) {
		setParentToCommands(commands);
		copy(commands.begin(), commands.end(), inserter(this->commands, this->commands.begin() + index));
	}
}





//--------------------------------------------------------------
CommandList* CommandList::add(Command* command) {
	command->_setParent(this);
	commands.push_back(command);
	return this;
}





//--------------------------------------------------------------
Command* CommandList::getCommand(int index) {
	return commands[index];
}





//--------------------------------------------------------------
vector<Command*>& CommandList::getCommands() {
	return commands;
}





//--------------------------------------------------------------
int CommandList::getNumCommands() {
	return commands.size();
}





//--------------------------------------------------------------
void CommandList::setParentToCommands(const vector<Command*>& commands) {
	for (vector<Command*>::const_iterator it = commands.begin(); it!= commands.end(); ++it) {
		(*it)->_setParent(this);
	}
}





//--------------------------------------------------------------
void CommandList::executeFunction(Command* command) {
	notifyComplete();
}





//--------------------------------------------------------------
void CommandList::interruptFunction(Command* command) {
}




