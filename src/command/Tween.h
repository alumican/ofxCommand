#pragma once

#include "Command.h"
#include "../easing/Easing.h"
#include "../easing/Collection.h"

namespace cmd {

	// ----------------------------------------
	//
	// TweenParameter
	//
	// ----------------------------------------
	class TweenParameter {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	private:
		float duration;
		const Easing* easing;
		bool isFrameBased;

		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		TweenParameter(float duration = 1, const Easing& easing = Linear::None, bool isFrameBased = false) {
			this->duration = duration;
			this->easing = &easing;
			this->isFrameBased = isFrameBased;
		};

		inline float getDuration() const {
			return duration;
		};

		void setDuration(float duration) {
			this->duration = duration;
		};

		inline const Easing& getEasing() const {
			return *easing;
		};

		void setEasing(const Easing& easing) {
			this->easing = &easing;
		};

		inline bool getIsFrameBased() const {
			return isFrameBased;
		};

		void setIsFrameBased(bool isFrameBased) {
			this->isFrameBased = isFrameBased;
		};
	};





	// ----------------------------------------
	//
	// TweenValue
	//
	// ----------------------------------------
	class TweenValue {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------
	public:
		float value;

	private:
		string name;
		float min;
		float max;
		float step;

		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		TweenValue(string name = "", float value = 0, float min = 0, float max = 1, float step = 0.1) {
			this->name = name;
			this->value = value;
			this->min = min;
			this->max = max;
			this->step = step;
		};

		TweenValue(const TweenValue& v){
			name = v.name;
			value = v.value;
			min = v.min;
			max = v.max;
			step = v.step;
		};

		~TweenValue() {
			clear();
		};

		TweenValue& operator = (const TweenValue &v) {
			name = v.name;
			value = v.value;
			min = v.min;
			max = v.max;
			step = v.step;
			return *this;
		}

		void clear() {
		};

		inline string getName() const {
			return name;
		};

		void setName(string name) {
			this->name = name;
		};

		inline float getMin() const {
			return min;
		};

		void setMin(float min) {
			this->min = min;
		};

		inline float getMax() const {
			return max;
		};

		void setMax(float max) {
			this->max = max;
		};

		inline float getStep() const {
			return step;
		};

		void setStep(float step) {
			this->step = step;
		};
	};





	// ----------------------------------------
	//
	// INTERNAL CLASS
	//
	// ----------------------------------------
	namespace internal {

		class TweenObject {
		public:
			ofParameter<float>* targetP;
			float* targetV;
			const ofParameter<float>* fromVarP;
			const float* fromVarV;
			TweenValue from;
			TweenValue to;
			float diff;
			float current;

			TweenObject() {
				clear();
			};

			TweenObject(const TweenObject& v){
				targetP = v.targetP;
				targetV = v.targetV;
				fromVarP = v.fromVarP;
				fromVarV = v.fromVarV;
				from = v.from;
				to = v.to;
				diff = v.diff;
				current = v.current;
			};

			~TweenObject() {
				clear();
			};

			TweenObject& operator = (const TweenObject &v) {
				targetP = v.targetP;
				targetV = v.targetV;
				fromVarP = v.fromVarP;
				fromVarV = v.fromVarV;
				from = v.from;
				to = v.to;
				diff = v.diff;
				current = v.current;
				return *this;
			}

			void clear() {
				targetP = NULL;
				targetV = NULL;
				fromVarP = NULL;
				fromVarV = NULL;
				from.clear();
				to.clear();
				diff = current = 0;
			};
		};
	}





	// ----------------------------------------
	//
	// Tween
	//
	// ----------------------------------------

	class Tween : public Command {

		// ----------------------------------------
		//
		// ENUM
		//
		// ----------------------------------------

	public:
		enum class State {
			STOPPED,
			STARTED,
			COMPLETED,
		};

		enum class EventType {
			STOP,
			START,
			UPDATE,
			COMPLETE,
		};





		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:
		ofEvent<Command&> onStart;
		ofEvent<Command&> onStop;
		ofEvent<Command&> onUpdate;

	protected:

	private:
		vector<internal::TweenObject*> objects;
		map<string, TweenValue*> valuesByName;

		float duration;
		const Easing* easing;
		bool isFrameBased;

		Tween::State state;
		bool isStarted;
		float startTime;

		float timeRatio;
		float valueRatio;

		function<void(Tween& tween)> atStartCallback;
		function<void(Tween& tween)> atStopCallback;
		function<void(Tween& tween)> atUpdateCallback;
		function<void(Tween& tween)> atCompleteCallback;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Tween(string name, float duration = 1, const Easing& easing = Linear::None, bool isFrameBased = false);
		Tween(string name, const TweenParameter& parameter);
		Tween(float duration = 1, const Easing& easing = Linear::None, bool isFrameBased = false);
		Tween(const TweenParameter& parameter);
		~Tween();

		// Set tween value
		Tween* animate(float& target, const float from, const float to);
		Tween* animate(float& target, const float from, const TweenValue& to);
		Tween* animate(float& target, const TweenValue& from, const float to);
		Tween* animate(float& target, const TweenValue& from, const TweenValue& to);

		Tween* animate(float& target, const float to);
		Tween* animate(float& target, const TweenValue& to);

		Tween* animate(ofParameter<float>& target, const float from, const float to);
		Tween* animate(ofParameter<float>& target, const float from, const TweenValue& to);
		Tween* animate(ofParameter<float>& target, const TweenValue& from, const float to);
		Tween* animate(ofParameter<float>& target, const TweenValue& from, const TweenValue& to);

		Tween* animate(ofParameter<float>& target, const float to);
		Tween* animate(ofParameter<float>& target, const TweenValue& to);

		// Set callback
		Tween* atStart(const function<void(Tween& tween)>& callback);
		Tween* atStop(const function<void(Tween& tween)>& callback);
		Tween* atUpdate(const function<void(Tween& tween)>& callback);
		Tween* atComplete(const function<void(Tween& tween)>& callback);

		// Clear tween value
		void clearAllTweens();

		// Tween parameter
		float getDuration() const;
		void setDuration(float duration);

		const Easing& getEasing() const;
		void setEasing(const Easing& easing);

		bool getIsFrameBased() const;
		void setIsFrameBased(bool isFrameBased);

		// Tween state
		State getState() const;

		bool getIsStopped() const;
		bool getIsStarted() const;
		bool getIsCompleted() const;

		float getValueRatio() const;
		float getTimeRatio() const;

		vector<internal::TweenObject*>* _getTweenObjects();
		map<string, TweenValue*>* _getTweenValuesByName();

		// Static method
		static Tween* create(string name, float duration = 1, const Easing& easing = Linear::None, bool isFrameBased = false);
		static Tween* create(string name, const TweenParameter& parameter);
		static Tween* create(float duration = 1, const Easing& easing = Linear::None, bool isFrameBased = false);
		static Tween* create(const TweenParameter& parameter);

	protected:
		virtual void apply();
		virtual void clear();

		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void setup(float duration, const Easing& easing, bool isFrameBased);
		void start();
		void stop();
		void update();
		void updateHandler(ofEventArgs& event);
		Tween* addTweenObject(internal::TweenObject* object);
	};
}




