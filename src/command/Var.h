#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

	template<class T>
	class Var : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		T* target;
		T value;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Var(T* target, T value) {
			this->target = target;
			this->value = value;
		};

		~Var() {
			ofLogVerbose() << "Bye Var";
		};

		T* getTarget() {
			return target;
		};

		void setTarget(T* target) {
			this->target = target;
		};

		T getValue() {
			return value;
		};

		void setValue(T value) {
			this->value = value;
		};

	protected:
		virtual void executeFunction(Command* command) {
			if (target != NULL) {
				*target = value;
			}
			notifyComplete();
		};

		virtual void interruptFunction(Command* command) {
		};
		
	private:
	};
	
}




