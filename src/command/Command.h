#pragma once

#include "ofMain.h"
#include "var/CommandState.h"

namespace command {

	class Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:
		ofEvent<Command&> onComplete;

	protected:

	private:
		CommandState state;
		Command* parent;
		bool deleteOnComplete;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Command();
		virtual ~Command();

		void execute();
		void interrupt();

		CommandState getState();
		Command* getParent();

		bool getDeleteOnComplete();
		void setDeleteOnComplete(bool value);

		void _setParent(Command* parent);

		// Override these
		virtual void _notifyBreak();
		virtual void _notifyReturn();

	protected:
		void notifyComplete();

		// Override these
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);

	private:
	};
	
}




