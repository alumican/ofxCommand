#pragma once

#include "CommandList.h"

namespace cmd {

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
		int getPosition() const;

		virtual void _notifyBreak();
		virtual void _notifyReturn();

	protected:
		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void next();
		void currentCommandCompleteHandler(Command& command);
	};
}




