#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

	template<class T>
	class Notify : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		ofEvent<T>* event;
		T argument;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Notify(ofEvent<T>& event, T argument) {
			this->event = &event;
			this->argument = argument;
		};

		~Notify() {
			event = NULL;
			ofLogVerbose() << "Bye Notify";
		};

		ofEvent<T>& getEvent() {
			return event;
		};

		void setEvent(ofEvent<T>& event) {
			this->event = event;
		};

		T getArgument() {
			return argument;
		};

		void getArgument(T argument) {
			this->argument = argument;
		};
		
	protected:
		virtual void executeFunction(Command* command) {
			ofNotifyEvent(*event, argument);
			notifyComplete();
		};

		virtual void interruptFunction(Command* command) {
		};

	private:
	};
	
}




