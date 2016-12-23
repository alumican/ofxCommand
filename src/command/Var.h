#pragma once

#include "Command.h"

namespace cmd {

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
		Var() {
			this->target = NULL;
		};

		Var(T& target) {
			this->target = &target;
		};

		Var(T& target, T value) {
			this->target = &target;
			this->value = value;
		};

		~Var() {
			ofLogVerbose() << "Bye Var";
		};

		T* getTarget() const {
			return target;
		};

		void setTarget(T* target) {
			this->target = target;
		};

		T getValue() const {
			return value;
		};

		void setValue(T value) {
			this->value = value;
		};

	protected:
		virtual void runFunction(Command* command) {
			if (target != NULL) {
				*target = value;
			}
			notifyComplete();
		};

		virtual void interruptFunction(Command* command) {
		};

		virtual void resetFunction(Command* command) {
		}

	private:
	};
	
}




