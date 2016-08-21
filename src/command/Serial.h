#pragma once

#include "ofMain.h"
#include "command/CommandList.h"

namespace command {

	class Serial : public CommandList {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		Command* currentCommand;
		int position;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Serial();
		Serial(const vector<Command*>& commands);
		~Serial();

		virtual void insert(const vector<Command*>& commands);
		int getPosition();

		void _complete(Command& command);

		virtual void _notifyBreak();
		virtual void _notifyReturn();

	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);

	private:
		void next();
	};
}




