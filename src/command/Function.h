#pragma once

#include <functional>
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
		Function();
		Function(const function<void()>& f);
		~Function();

		function<void()> getFunction() const;
		void setFunction(const function<void()>& f);

	protected:
		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
	};
}




