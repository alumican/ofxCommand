#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

	template <class C, void (C::*M)()>
	class Function : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		C* target;
		ofEvent<void>* event;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Function(C* target) {
			this->target = target;
			event = NULL;
		}

		Function(C* target, ofEvent<void>& event) {
			this->target = target;
			this->event = &event;
		}

		~Function() {
			target = NULL;
			if (event != NULL) {
				ofRemoveListener(*event, this, &Function::_eventHandler);
				event = NULL;
			}
			ofLogVerbose() << "Bye Function";
		}

		C* getTarget() {
			return target;
		}

		void setTarget(const C* target) {
			this->target = target;
		}

		ofEvent<void>& getEvent() {
			return event;
		};

		void setEvent(ofEvent<void>& event) {
			this->event = event;
		};

		void _eventHandler() {
			if (event != NULL) {
				ofRemoveListener(*event, this, &Function::_eventHandler);
			}
			notifyComplete();
		}

	protected:
		virtual void executeFunction(Command* command) {
			if (event != NULL) {
				ofAddListener(*event, this, &Function::_eventHandler);
			}
			if (target != NULL) {
				(target->*M)();
			}
			if (event == NULL) {
				notifyComplete();
			}
		}

		virtual void interruptFunction(Command* command) {
			if (event != NULL) {
				ofRemoveListener(*event, this, &Function::_eventHandler);
			}
		}

	private:
	};
}




