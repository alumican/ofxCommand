#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

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
			ofRemoveListener(event, this, &Listen::_complete);
			event = NULL;
		};

		ofEvent<T>& getEvent() {
			return event;
		};

		void setEvent(ofEvent<T>& event) {
			this->event = event;
		};

		void _complete(Command& command) {
			ofRemoveListener(event, this, &Listen::_complete);
			notifyComplete();
		}


	protected:
		virtual void executeFunction(Command* command) {
			ofAddListener(event, this, &Listen::_complete);
		};

		virtual void interruptFunction(Command* command) {
			ofRemoveListener(event, this, &Listen::_complete);
		};
		
	private:
	};
	
}




