#include "Tween.h"

namespace cmd {

	//--------------------------------------------------------------
	Tween::Tween(string name, float duration, const Easing& easing, bool isFrameBased) : Command(name) {
		setup(duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween::Tween(string name, const TweenParameter& parameter) : Command(name) {
		setup(parameter.getDuration(), parameter.getEasing(), parameter.getIsFrameBased());
	}

	//--------------------------------------------------------------
	Tween::Tween(float duration, const Easing& easing, bool isFrameBased) {
		setup(duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween::Tween(const TweenParameter& parameter) {
		setup(parameter.getDuration(), parameter.getEasing(), parameter.getIsFrameBased());
	}

	//--------------------------------------------------------------
	Tween::~Tween() {
		ofRemoveListener(ofEvents().update, this, &Tween::updateHandler);
		clearAllTweens();
		ofLogVerbose() << "Bye Tween";
	}





	//--------------------------------------------------------------
	float Tween::getDuration() const {
		return duration;
	}

	//--------------------------------------------------------------
	void Tween::setDuration(float duration) {
		this->duration = duration;
	}

	//--------------------------------------------------------------
	const Easing& Tween::getEasing() const {
		return *easing;
	}

	//--------------------------------------------------------------
	void Tween::setEasing(const Easing& easing) {
		this->easing = &easing;
	}

	//--------------------------------------------------------------
	bool Tween::getIsFrameBased() const {
		return isFrameBased;
	}

	//--------------------------------------------------------------
	void Tween::setIsFrameBased(bool isFrameBased) {
		this->isFrameBased = isFrameBased;
	}

	//--------------------------------------------------------------
	Tween::State Tween::getState() const {
		return state;
	}

	//--------------------------------------------------------------
	bool Tween::getIsStarted() const {
		return state == Tween::State::STARTED;
	}

	//--------------------------------------------------------------
	bool Tween::getIsStopped() const {
		return state == Tween::State::STOPPED;
	}

	//--------------------------------------------------------------
	bool Tween::getIsCompleted() const {
		return state == Tween::State::COMPLETED;
	}

	//--------------------------------------------------------------
	float Tween::getTimeRatio() const {
		return timeRatio;
	}

	//--------------------------------------------------------------
	float Tween::getValueRatio() const {
		return valueRatio;
	}

	//--------------------------------------------------------------
	vector<internal::TweenObject*>* Tween::_getTweenObjects() {
		return &objects;
	}

	//--------------------------------------------------------------
	map<string, TweenValue*>* Tween::_getTweenValuesByName() {
		return &valuesByName;
	}





	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const float from, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->from.value = from;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const float from, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->from.value = from;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const TweenValue& from, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->from = from;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const TweenValue& from, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->from = from;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->fromVarV = &target;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(float& target, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetV = &target;
		object->fromVarV = &target;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const float from, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->from.value = from;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const float from, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->from.value = from;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const TweenValue& from, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->from = from;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const TweenValue& from, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->from = from;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const float to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->fromVarP = &target;
		object->to.value = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::animate(ofParameter<float>& target, const TweenValue& to) {
		internal::TweenObject* object = new internal::TweenObject();
		object->targetP = &target;
		object->fromVarP = &target;
		object->to = to;
		return addTweenObject(object);
	}

	//--------------------------------------------------------------
	Tween* Tween::addTweenObject(internal::TweenObject* object) {
		objects.push_back(object);

		if (object->from.getName() != "") {
			valuesByName[object->from.getName()] = &object->from;
		}
		if (object->to.getName() != "") {
			valuesByName[object->to.getName()] = &object->to;
		}

		return this;
	}





	//--------------------------------------------------------------
	Tween* Tween::atStart(const function<void(Tween& tween)>& callback) {
		atStartCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atStop(const function<void(Tween& tween)>& callback) {
		atStopCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atUpdate(const function<void(Tween& tween)>& callback) {
		atUpdateCallback = callback;
		return this;
	}

	//--------------------------------------------------------------
	Tween* Tween::atComplete(const function<void(Tween& tween)>& callback) {
		atCompleteCallback = callback;
		return this;
	}





	//--------------------------------------------------------------
	void Tween::clearAllTweens() {
		clear();

		for (vector<internal::TweenObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			(*it)->clear();
		}
		objects.clear();

		for (map<string, TweenValue*>::iterator it = valuesByName.begin(); it != valuesByName.end(); ++it) {
			it->second->clear();
		}
		valuesByName.clear();
	}





	//--------------------------------------------------------------
	void Tween::setup(float duration, const Easing& easing, bool isFrameBased) {
		this->duration = duration;
		this->easing = &easing;
		this->isFrameBased = isFrameBased;

		isStarted = false;
		state = Tween::State::STOPPED;

		timeRatio = 0;
		valueRatio = 0;
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
		for (vector<internal::TweenObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			internal::TweenObject* object = *it;
			if (object->fromVarV != NULL) {
				object->current = object->from.value = *object->fromVarV;
			} else if (object->fromVarP != NULL) {
				object->current = object->from.value = *object->fromVarP;
			} else {
				object->current = object->from.value;
			}
			if (object->targetV != NULL) {
				*object->targetV = object->current;
			} else if (object->targetP != NULL) {
				*object->targetP = object->current;
			}
			object->diff = object->to.value - object->current;
		}

		// Start
		ofAddListener(ofEvents().update, this, &Tween::updateHandler);
		if (atStartCallback != NULL) atStartCallback(*this);
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
		if (atStopCallback != NULL) atStopCallback(*this);
		ofNotifyEvent(onStop, *this);
	}

	//--------------------------------------------------------------
	void Tween::update() {
		// Update time
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
		valueRatio = easing->calculate(timeRatio, 0, 1, 1);
		for (vector<internal::TweenObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
			internal::TweenObject* object = *it;
			object->current = object->from.value + object->diff * valueRatio;
			if (object->targetV != NULL) {
				*object->targetV = object->current;
			} else if (object->targetP != NULL) {
				*object->targetP = object->current;
			}
		}

		// Apply current value
		apply();

		// onUpdate
		if (state == Tween::State::STARTED) {
			if (atUpdateCallback != NULL) atUpdateCallback(*this);
			ofNotifyEvent(onUpdate, *this);
		}

		// onComplete
		if (state != Tween::State::COMPLETED && timeRatio == 1) {
			state = Tween::State::COMPLETED;
			stop();
			if (atCompleteCallback != NULL) atCompleteCallback(*this);
			notifyComplete();
		}
	}





	//--------------------------------------------------------------
	void Tween::updateHandler(ofEventArgs& event) {
		update();
	}





	//--------------------------------------------------------------
	void Tween::runFunction(Command* command) {
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





	//--------------------------------------------------------------
	Tween* Tween::create(string name, float duration, const Easing& easing, bool isFrameBased) {
		return new Tween(name, duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween* Tween::create(string name, const TweenParameter& parameter) {
		return new Tween(name, parameter);
	}

	//--------------------------------------------------------------
	Tween* Tween::create(float duration, const Easing& easing, bool isFrameBased) {
		return new Tween(duration, easing, isFrameBased);
	}

	//--------------------------------------------------------------
	Tween* Tween::create(const TweenParameter& parameter) {
		return new Tween(parameter);
	}
}
