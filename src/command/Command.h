#pragma once

#include "ofMain.h"

namespace cmd {

	enum class CommandState : int {
		SLEEPING     = 0,
		EXECUTING    = 1,
		INTERRUPTING = 2,
	};





	class Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:
		ofEvent<Command&> onComplete;

	protected:

	private:
		static map<string, Command*> commandsByName;

		string name;
		CommandState state;
		Command* parent;
		bool deleteOnComplete;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		static Command* getCommandByName(string name);

		Command(string name = "");
		virtual ~Command();

		void execute();
		void interrupt();
		void reset();

		CommandState getState();
		Command* getParent();

		string getName();
		void setName(string name);

		bool getDeleteOnComplete();
		void setDeleteOnComplete(bool value);

		void _setParent(Command* parent);

		// Override these
		virtual void _notifyBreak();
		virtual void _notifyReturn();

	protected:
		void notifyComplete();

		// Override these
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		static void registerCommandByName(string name, Command* command);
		static void removeCommandByName(string name);
	};
}




