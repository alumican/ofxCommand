#pragma once

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
		Loop(string name, Command* target = NULL, int loopCount = -1);
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
		void setup(Command* target, int loopCount);

		void checkComplete();
		void completeHandler(Command& command);
	};
}




