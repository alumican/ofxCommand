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
		Loop(string name, int loopCount = -1, Command* target = NULL);
		Loop(int loopCount = -1, Command* target = NULL);
		Loop(Command* target);
		~Loop();

		int getCurrentCount() const;

		Command* getTarget() const;
		void setTarget(Command* command);

		int getLoopCount() const;
		void setLoopCount(int loopCount);

	protected:
		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void setup(int loopCount, Command* target);

		void checkComplete();
		void completeHandler(Command& command);
	};
}




