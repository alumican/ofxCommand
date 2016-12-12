#include "Tween.h"

namespace cmd {

	//--------------------------------------------------------------
	Tween::Tween(string name, float duration, const cmd::Easing& easing, bool isFrameBased) : Command(name) {
		setup(duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween::Tween(float duration, const cmd::Easing& easing, bool isFrameBased) {
		setup(duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween::~Tween() {
		ofRemoveListener(ofEvents().update, this, &Tween::updateHandler);
		clearAllTweens();
		ofLogVerbose() << "Bye Tween";
	}





	//--------------------------------------------------------------
	float Tween::getDuration() {
		return duration;
	}

	//--------------------------------------------------------------
	void Tween::setDuration(float duration) {
		this->duration = duration;
	}

	//--------------------------------------------------------------
	const cmd::Easing& Tween::getEasing() {
		return *easing;
	}

	//--------------------------------------------------------------
	void Tween::setEasing(const cmd::Easing& easing) {
		this->easing = &easing;
	}

	//--------------------------------------------------------------
	bool Tween::getIsFrameBased() {
		return isFrameBased;
	}

	//--------------------------------------------------------------
	void Tween::setIsFrameBased(bool isFrameBased) {
		this->isFrameBased = isFrameBased;
	}

	//--------------------------------------------------------------
	Tween::State Tween::getState() {
		return state;
	}

	//--------------------------------------------------------------
	bool Tween::getIsStarted() {
		return state == Tween::State::STARTED;
	}

	//--------------------------------------------------------------
	bool Tween::getIsStopped() {
		return state == Tween::State::STOPPED;
	}

	//--------------------------------------------------------------
	bool Tween::getIsCompleted() {
		return state == Tween::State::COMPLETED;
	}





	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const float from, const float to) {
		TweenObject object;
		object.target = &target;
		object.fromVar = NULL;
		object.from = from;
		object.to = to;
		objects.push_back(object);
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const float to) {
		TweenObject object;
		object.target = &target;
		object.fromVar = &target;
		object.from = 0;
		object.to = to;
		objects.push_back(object);
		return this;
	}





	//--------------------------------------------------------------
	Tween* Tween::atStart(const function<void()>& callback) {
		atStartCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atStop(const function<void()>& callback) {
		atStopCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atUpdate(const function<void()>& callback) {
		atUpdateCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atComplete(const function<void()>& callback) {
		atCompleteCallback = callback;
		return this;
	}





	//--------------------------------------------------------------
	void Tween::clearAllTweens() {
		clear();
		objects.clear();
	}





	//--------------------------------------------------------------
	void Tween::setup(float duration, const Easing& easing, bool isFrameBased) {
		this->duration = duration;
		this->easing = &easing;
		this->isFrameBased = isFrameBased;

		isStarted = false;
		state = Tween::State::STOPPED;
	}

	//--------------------------------------------------------------
	void Tween::start() {
		if (isStarted) return;
		isStarted = true;
		state = Tween::State::STARTED;

		// Time base
		if (isFrameBased) {
			startTime = ofGetFrameNum();
		} else {
			startTime = ofGetElapsedTimef();
		}

		// Set init value
		for (vector<TweenObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			TweenObject* object = &(*it);
			if (object->fromVar != NULL) {
				object->current = object->from = *object->fromVar;
			} else {
				object->current = object->from;
			}
			if (object->target != NULL) {
				*object->target = object->current;
			}
			object->diff = object->to - object->current;
		}

		// Start
		ofAddListener(ofEvents().update, this, &Tween::updateHandler);
		if (atStartCallback != NULL) atStartCallback();
		ofNotifyEvent(onStart, *this);
		update();
	}

	//--------------------------------------------------------------
	void Tween::stop() {
		if (!isStarted) return;
		isStarted = false;
		state = Tween::State::STOPPED;

		// Stop
		ofRemoveListener(ofEvents().update, this, &Tween::updateHandler);
		if (atStopCallback != NULL) atStopCallback();
		ofNotifyEvent(onStop, *this);
	}

	//--------------------------------------------------------------
	void Tween::update() {
		// Update time
		float timeRatio;
		if (duration > 0) {
			if (isFrameBased) {
				timeRatio = (ofGetFrameNum() - startTime) / duration;
			} else {
				timeRatio = (ofGetElapsedTimef() - startTime) / duration;
			}
			if (timeRatio > 1) {
				timeRatio = 1;
			}
		} else {
			timeRatio = 1;
		}

		// Update value
		float valueRatio = easing->calculate(timeRatio, 0, 1, 1);
		for (vector<TweenObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
			TweenObject* object = &(*it);
			object->current = object->from + object->diff * valueRatio;
			if (object->target != NULL) {
				*object->target = object->current;
			}
		}

		// Apply current value
		apply();

		// onUpdate
		if (state == Tween::State::STARTED) {
			if (atUpdateCallback != NULL) atUpdateCallback();
			ofNotifyEvent(onUpdate, *this);
		}

		// onComplete
		if (state != Tween::State::COMPLETED && timeRatio == 1) {
			state = Tween::State::COMPLETED;
			stop();
			if (atCompleteCallback != NULL) atCompleteCallback();
			notifyComplete();
		}
	}





	//--------------------------------------------------------------
	void Tween::updateHandler(ofEventArgs& event) {
		update();
	}





	//--------------------------------------------------------------
	void Tween::executeFunction(Command* command) {
		start();
	}

	//--------------------------------------------------------------
	void Tween::interruptFunction(Command* command) {
		stop();
	}

	//--------------------------------------------------------------
	void Tween::resetFunction(Command* command) {
		interruptFunction(command);
	}





	//--------------------------------------------------------------
	void Tween::apply() {
	}

	//--------------------------------------------------------------
	void Tween::clear() {
	}
}
