#include "command/Tween.h"

using namespace command;

//--------------------------------------------------------------
Tween::Tween(float duration, Tween::Easing easing, bool isFrameBased) {
	this->duration = duration;
	this->easing = easing != NULL ? easing : Tween::easeNone;
	this->isFrameBased = isFrameBased;

	isStarted = false;
	state = Tween::State::STOPPED;
}





//--------------------------------------------------------------
Tween::~Tween() {
	ofRemoveListener(ofEvents().update, this, &Tween::updateHandler);
	clearAllTweens();
	easing = NULL;
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
Tween::Easing Tween::getEasing() {
	return easing;
}





//--------------------------------------------------------------
void Tween::setEasing(Tween::Easing easing) {
	this->easing = easing;
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
bool Tween::getIsStopped() {
	return state == Tween::State::STOPPED;
}





//--------------------------------------------------------------
bool Tween::getIsStarted() {
	return state == Tween::State::STARTED;
}





//--------------------------------------------------------------
bool Tween::getIsCompleted() {
	return state == Tween::State::COMPLETED;
}





//--------------------------------------------------------------
int Tween::addTween(const float from, const float to) {
	TweenObject object;
	object.target = NULL;
	object.fromVar = NULL;
	object.from = from;
	object.to = to;
	objects.push_back(object);
	return objects.size() - 1;
}





//--------------------------------------------------------------
int Tween::addTween(const float* from, const float to) {
	TweenObject object;
	object.target = NULL;
	object.fromVar = from;
	object.from = 0;
	object.to = to;
	objects.push_back(object);
	return objects.size() - 1;
}





//--------------------------------------------------------------
int Tween::addTween(float* target, const float from, const float to) {
	TweenObject object;
	object.target = target;
	object.fromVar = NULL;
	object.from = from;
	object.to = to;
	objects.push_back(object);
	return objects.size() - 1;
}





//--------------------------------------------------------------
int Tween::addTween(float* target, const float* from, const float to) {
	TweenObject object;
	object.target = target;
	object.fromVar = from;
	object.from = 0;
	object.to = to;
	objects.push_back(object);
	return objects.size() - 1;
}





//--------------------------------------------------------------
void Tween::clearAllTweens() {
	clear();
	objects.clear();
}





//--------------------------------------------------------------
float Tween::getValue(int index) {
	return objects[index].current;
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
			object->current = *object->fromVar;
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
	ofNotifyEvent(onStop, *this);
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
	float valueRatio = (*easing)(timeRatio, 0, 1, 1);
	for (vector<TweenObject>::iterator it = objects.begin(); it != objects.end(); ++it) {
		TweenObject* object = &(*it);
		object->current = object->from + object->diff * valueRatio;
		if (object->target != NULL) {
			*object->target = object->current;
		}
	}

	// Apply current value
	apply();

	// onChange
	if (state == Tween::State::STARTED) {
		ofNotifyEvent(onChange, *this);
	}

	// onComplete
	if (state != Tween::State::COMPLETED && timeRatio == 1) {
		state = Tween::State::COMPLETED;
		stop();
		notifyComplete();
	}
}





//--------------------------------------------------------------
void Tween::updateHandler(ofEventArgs& event) {
	update();
}





//--------------------------------------------------------------
float Tween::easeInBack(float t, float b, float c, float d) {
	float s = 1.70158f;
	float postFix = t /= d;
	return c * (postFix)*t * ((s + 1) * t - s) + b;
}

float Tween::easeOutBack(float t, float b, float c, float d) {
	float s = 1.70158f;
	t = t / d - 1;
	return c * (t * t * ((s + 1) * t + s) + 1) + b;
}

float Tween::easeInOutBack(float t, float b, float c, float d) {
	float s = 1.70158f;
	if ((t /= d / 2) < 1) {
		s *= 1.525f;
		return c / 2 * (t * t * ((s + 1) * t - s)) + b;
	}
	float postFix = t -= 2;
	s *= 1.525f;
	return c / 2 * ((postFix)*t * ((s + 1) * t + s) + 2) + b;
}

float Tween::easeInBounce(float t, float b, float c, float d) {
	return c - easeOutBounce(d - t, 0, c, d) + b;
}

float Tween::easeOutBounce(float t, float b, float c, float d) {
	if ((t /= d) < (1 / 2.75f)) {
		return c * (7.5625f * t * t) + b;
	} else if (t < (2 / 2.75f)) {
		float postFix = t -= (1.5f / 2.75f);
		return c * (7.5625f * (postFix)*t + .75f) + b;
	} else if (t < (2.5 / 2.75)) {
		float postFix = t -= (2.25f / 2.75f);
		return c * (7.5625f * (postFix)*t + .9375f) + b;
	} else {
		float postFix = t -= (2.625f / 2.75f);
		return c * (7.5625f * (postFix)*t + .984375f) + b;
	}
}

float Tween::easeInOutBounce(float t, float b, float c, float d) {
	if (t < d / 2)
		return easeInBounce(t * 2, 0, c, d) * .5f + b;
	else
		return easeOutBounce(t * 2 - d, 0, c, d) * .5f + c * .5f + b;
}

float Tween::easeInCirc(float t, float b, float c, float d) {
	t /= d;
	return -c * (sqrt(1 - t * t) - 1) + b;
}

float Tween::easeOutCirc(float t, float b, float c, float d) {
	t = t / d - 1;
	return c * sqrt(1 - t * t) + b;
}

float Tween::easeInOutCirc(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
	t -= 2;
	return c / 2 * (sqrt(1 - t * t) + 1) + b;
}

float Tween::easeInCubic(float t, float b, float c, float d) {
	t /= d;
	return c * t * t * t + b;
}

float Tween::easeOutCubic(float t, float b, float c, float d) {
	t = t / d - 1;
	return c * (t * t * t + 1) + b;
}

float Tween::easeInOutCubic(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
	t -= 2;
	return c / 2 * (t * t * t + 2) + b;
}

float Tween::easeInElastic(float t, float b, float c, float d) {
	if (t == 0) return b;
	if ((t /= d) == 1) return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	float postFix = a * pow(2, 10 * (t -= 1));	// this is a fix, again, with post-increment operators
	return -(postFix * sin((t * d - s) * (2 * M_PI) / p)) + b;
}

float Tween::easeOutElastic(float t, float b, float c, float d) {
	if (t == 0) return b;
	if ((t /= d) == 1) return b + c;
	float p = d * .3f;
	float a = c;
	float s = p / 4;
	return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * M_PI) / p) + c + b);
}

float Tween::easeInOutElastic(float t, float b, float c, float d) {
	if (t == 0) return b;
	if ((t /= d / 2) == 2) return b + c;
	float p = d * (.3f * 1.5f);
	float a = c;
	float s = p / 4;

	if (t < 1) {
		float postFix = a * pow(2, 10 * (t -= 1));	// postIncrement is evil
		return -.5f * (postFix * sin((t * d - s) * (2 * M_PI) / p)) + b;
	}
	float postFix = a * pow(2, -10 * (t -= 1));	// postIncrement is evil
	return postFix * sin((t * d - s) * (2 * M_PI) / p) * .5f + c + b;
}

float Tween::easeInExpo(float t, float b, float c, float d) {
	return (t == 0) ? b : c * pow(2, 10 * (t / d - 1)) + b;
}

float Tween::easeOutExpo(float t, float b, float c, float d) {
	return (t == d) ? b + c : c * (-pow(2, -10 * t / d) + 1) + b;
}

float Tween::easeInOutExpo(float t, float b, float c, float d) {
	if (t == 0) return b;
	if (t == d) return b + c;
	if ((t /= d / 2) < 1) return c / 2 * pow(2, 10 * (t - 1)) + b;
	return c / 2 * (-pow(2, -10 * --t) + 2) + b;
}

float Tween::easeNone(float t, float b, float c, float d) {
	return c * t / d + b;
}

float Tween::easeInQuad(float t, float b, float c, float d) {
	t /= d;
	return c * t * t + b;
}

float Tween::easeOutQuad(float t, float b, float c, float d) {
	t /= d;
	return -c * t * (t - 2) + b;
}

float Tween::easeInOutQuad(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return ((c / 2) * (t * t)) + b;
	--t;
	return -c / 2 * (((t - 2) * t) - 1) + b;
}

float Tween::easeInQuart(float t, float b, float c, float d) {
	t /= d;
	return c * t * t * t * t + b;
}

float Tween::easeOutQuart(float t, float b, float c, float d) {
	t = t / d - 1;
	return -c * (t * t * t * t - 1) + b;
}

float Tween::easeInOutQuart(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
	t -= 2;
	return -c / 2 * (t * t * t * t - 2) + b;
}

float Tween::easeInQuint(float t, float b, float c, float d) {
	t /= d;
	return c * t * t * t * t * t + b;
}

float Tween::easeOutQuint(float t, float b, float c, float d) {
	t = t / d - 1;
	return c * (t * t * t * t * t + 1) + b;
}

float Tween::easeInOutQuint(float t, float b, float c, float d) {
	if ((t /= d / 2) < 1) return c / 2 * t * t * t * t * t + b;
	t -= 2;
	return c / 2 * (t * t * t * t * t + 2) + b;
}

float Tween::easeInSine(float t, float b, float c, float d) {
	return -c * cos(t / d * (M_PI / 2)) + c + b;
}

float Tween::easeOutSine(float t, float b, float c, float d) {
	return c * sin(t / d * (M_PI / 2)) + b;
}

float Tween::easeInOutSine(float t, float b, float c, float d) {
	return -c / 2 * (cos(t / d * M_PI) - 1) + b;
}

// breathe
// f(x) = (exp(sin(x)) - 1/e ) * 255 / (e - 1/e)
// min 0 at x = -œÄ/2 + 2nœÄ
// max 255 at x = œÄ/2 + 2nœÄ
float Tween::easeInBreathe(float t, float b, float c, float d) {
	return -c * (exp(cos(t / d * M_PI)) - 0.36787944) / 2.35040238 + c + b;
}
float Tween::easeOutBreathe(float t, float b, float c, float d) {
	return c * (exp(sin(t / d * M_PI - M_PI / 2)) - 0.36787944) / 2.35040238 + b;
}
float Tween::easeInOutBreathe(float t, float b, float c, float d) {
	return -c / 2 * ((exp(cos(t / d * 2 * M_PI)) - 0.36787944) / 2.35040238 - 1) + b;
}




