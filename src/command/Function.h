#pragma once

#include <functional>
#include "ofMain.h"
#include "Command.h"

namespace cmd {

	class Function : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		function<void()> f;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Function(const function<void()>& f);
		~Function();

		function<void()> getFunction();
		void setFunction(const function<void()>& f);

	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
	};
}




