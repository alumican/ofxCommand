#pragma once

#include "Command.h"

namespace cmd {

	template<class T>
	class Listen : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		ofEvent<T>* event;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Listen(ofEvent<T>& event) {
			this->event = &event;
		};

		~Listen() {
			ofRemoveListener(*event, this, &Listen::_complete);
			event = NULL;
			ofLogVerbose() << "Bye Listen";
		};

		ofEvent<T>* getEvent() {
			return event;
		};

		void setEvent(ofEvent<T>* event) {
			this->event = event;
		};


	protected:
		virtual void executeFunction(Command* command) {
			ofAddListener(*event, this, &Listen::_complete);
		};

		virtual void interruptFunction(Command* command) {
			ofRemoveListener(*event, this, &Listen::_complete);
		};

		virtual void resetFunction(Command* command) {
			interruptFunction(command);
		}

	private:
		void _complete() {
			ofRemoveListener(*event, this, &Listen::_complete);
			notifyComplete();
		}
	};
}




