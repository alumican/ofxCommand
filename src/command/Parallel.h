#pragma once

#include "ofMain.h"
#include "command/CommandList.h"

namespace command {

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
		int getCompleteCount();

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




