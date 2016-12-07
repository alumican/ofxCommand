#pragma once

#include "ofMain.h"
#include "Command.h"

namespace cmd {

	class Wait : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		float duration;
		bool isFrameBased;
		float startTime;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Wait(float duration = 1, bool isFrameBased = false);
		~Wait();

		float getDuration();
		void setDuration(float duration);

		bool getIsFrameBased();
		void setIsFrameBased(bool isFrameBased);

	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void update(ofEventArgs& event);
		void checkComplete();
	};
	
}




