#pragma once

#include "Command.h"

namespace cmd {

	class Log : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		string message;
		ofLogLevel level;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Log(const string& message = "", ofLogLevel level = OF_LOG_NOTICE);
		~Log();

		const string& getMessage() const;
		void setMessage(const string& message);

		ofLogLevel getLevel() const;
		void setLevel(ofLogLevel level);
		
	protected:
		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
	};
	
}




