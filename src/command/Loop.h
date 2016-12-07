#pragma once

#include "ofMain.h"
#include "Command.h"

namespace cmd {

	class Loop : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		Command* target;
		int currentCount;
		int loopCount;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Loop(Command* target = NULL, int loopCount = -1);
		~Loop();

		int getCurrentCount();

		Command* getTarget();
		void setTarget(Command* command);

		int getLoopCount();
		void setLoopCount(int loopCount);

	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void checkComplete();
		void completeHandler(Command& command);
	};
}




