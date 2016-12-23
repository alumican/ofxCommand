#pragma once

#include "CommandList.h"

namespace cmd {

	class Parallel : public CommandList {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		int completeCount;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Parallel();
		Parallel(const vector<Command*>& commands);
		~Parallel();

		virtual void insert(const vector<Command*>& commands);
		int getCompleteCount() const;

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




