#pragma once

#include "Command.h"

namespace cmd {

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
		Notify() {
			this->event = NULL;
		};

		Notify(ofEvent<T>& event) {
			this->event = &event;
		};

		Notify(ofEvent<T>& event, T argument) {
			this->event = &event;
			this->argument = argument;
		};

		~Notify() {
			event = NULL;
			ofLogVerbose() << "Bye Notify";
		};

		ofEvent<T>& getEvent() const {
			return event;
		};

		void setEvent(ofEvent<T>& event) {
			this->event = event;
		};

		T getArgument() const {
			return argument;
		};

		void setArgument(T argument) {
			this->argument = argument;
		};
		
	protected:
		virtual void runFunction(Command* command) {
			ofNotifyEvent(*event, argument);
			notifyComplete();
		};

		virtual void interruptFunction(Command* command) {
		};

		virtual void resetFunction(Command* command) {
		};

	private:
	};
	
}




