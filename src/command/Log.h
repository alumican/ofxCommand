#pragma once

#include "ofMain.h"
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

		const string& getMessage();
		void setMessage(const string& message);

		ofLogLevel getLevel();
		void setLevel(ofLogLevel level);
		
	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
	};
	
}




