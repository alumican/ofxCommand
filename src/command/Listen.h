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
		Listen() {
			this->event = NULL;
		};

		Listen(ofEvent<T>& event) {
			this->event = &event;
		};

		~Listen() {
			ofRemoveListener(*event, this, &Listen::_complete);
			event = NULL;
			ofLogVerbose() << "Bye Listen";
		};

		ofEvent<T>* getEvent() const {
			return event;
		};

		void setEvent(ofEvent<T>* event) {
			this->event = event;
		};


	protected:
		virtual void runFunction(Command* command) {
			ofAddListener(*event, this, &Listen::_complete);
		};

		virtual void interruptFunction(Command* command) {
			ofRemoveListener(*event, this, &Listen::_complete);
		};

		virtual void resetFunction(Command* command) {
			interruptFunction(command);
		}

	private:

		void _complete(T& args) {
			ofRemoveListener(*event, this, &Listen::_complete);
			notifyComplete();
		}
	};
}





namespace cmd {

	template<> class Listen<void> : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		ofEvent<void>* event;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Listen() {
			this->event = NULL;
		};

		Listen(ofEvent<void>& event) {
			this->event = &event;
		};

		~Listen() {
			ofRemoveListener(*event, this, &Listen::_complete);
			event = NULL;
			ofLogVerbose() << "Bye Listen";
		};

		ofEvent<void>* getEvent() const {
			return event;
		};

		void setEvent(ofEvent<void>* event) {
			this->event = event;
		};


	protected:
		virtual void runFunction(Command* command) {
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




