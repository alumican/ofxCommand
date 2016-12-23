#pragma once

#include "Command.h"

namespace cmd {

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
		void insert(int index, Command* command);
		void insert(int index, const vector<Command*>& commands);
		void insert(Command* command);
		virtual void insert(const vector<Command*>& commands);

		Command* getCommand(int index) const;
		vector<Command*>& getCommands();
		int getNumCommands() const;

	protected:
		void setParentToCommands(const vector<Command*>& commands);

		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
	};
}




