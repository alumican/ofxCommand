#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

	class CommandList : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		vector<Command*> commands;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		CommandList();
		CommandList(const vector<Command*>& commands);
		virtual ~CommandList();

		CommandList* add(Command* command);
		void add(const vector<Command*>& commands);
		void insert(int index, const vector<Command*>& commands);
		virtual void insert(const vector<Command*>& commands);

		Command* getCommand(int index);
		vector<Command*>& getCommands();
		int getNumCommands();

	protected:
		void setParentToCommands(const vector<Command*>& commands);

		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);

	private:
	};
}




