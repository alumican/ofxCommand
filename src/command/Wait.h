#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

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

	private:
		void update(ofEventArgs& event);
	};
	
}




