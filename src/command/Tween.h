#pragma once

#include "ofMain.h"
#include "command/Command.h"

namespace command {

	class Tween : public Command {

		// ----------------------------------------
		//
		// ENUM
		//
		// ----------------------------------------

	public:
		enum State {
			STOPPED,
			STARTED,
			COMPLETED,
		};

		enum EventType {
			STOP,
			START,
			CHANGE,
			COMPLETE,
		};





		// ----------------------------------------
		//
		// EASING
		//
		// ----------------------------------------

	public:
		typedef float (*Easing)(float, float, float, float);

		static float easeNone(float t, float b, float c, float d);
		static float easeInBack(float t, float b, float c, float d);
		static float easeOutBack(float t, float b, float c, float d);
		static float easeInOutBack(float t, float b, float c, float d);
		static float easeInBounce(float t, float b, float c, float d);
		static float easeOutBounce(float t, float b, float c, float d);
		static float easeInOutBounce(float t, float b, float c, float d);
		static float easeInCirc(float t, float b, float c, float d);
		static float easeOutCirc(float t, float b, float c, float d);
		static float easeInOutCirc(float t, float b, float c, float d);
		static float easeInCubic(float t, float b, float c, float d);
		static float easeOutCubic(float t, float b, float c, float d);
		static float easeInOutCubic(float t, float b, float c, float d);
		static float easeInElastic(float t, float b, float c, float d);
		static float easeOutElastic(float t, float b, float c, float d);
		static float easeInOutElastic(float t, float b, float c, float d);
		static float easeInExpo(float t, float b, float c, float d);
		static float easeOutExpo(float t, float b, float c, float d);
		static float easeInOutExpo(float t, float b, float c, float d);
		static float easeInQuad(float t, float b, float c, float d);
		static float easeOutQuad(float t, float b, float c, float d);
		static float easeInOutQuad(float t, float b, float c, float d);
		static float easeInQuart(float t, float b, float c, float d);
		static float easeOutQuart(float t, float b, float c, float d);
		static float easeInOutQuart(float t, float b, float c, float d);
		static float easeInQuint(float t, float b, float c, float d);
		static float easeOutQuint(float t, float b, float c, float d);
		static float easeInOutQuint(float t, float b, float c, float d);
		static float easeInSine(float t, float b, float c, float d);
		static float easeOutSine(float t, float b, float c, float d);
		static float easeInOutSine(float t, float b, float c, float d);
		static float easeInBreathe(float t, float b, float c, float d);
		static float easeOutBreathe(float t, float b, float c, float d);
		static float easeInOutBreathe(float t, float b, float c, float d);





		// ----------------------------------------
		//
		// INTERNAL CLASS
		//
		// ----------------------------------------

	private:
		class TweenObject {
		public:
			float* target;
			const float* fromVar = NULL;
			float from;
			float to;
			float diff;
			float current;

			TweenObject() {
				target = NULL;
				from = to = diff = current = 0;
			};
		};





		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:
		ofEvent<command::Command&> onStop;
		ofEvent<command::Command&> onStart;
		ofEvent<command::Command&> onChange;

	protected:

	private:
		vector<TweenObject> objects;

		float duration;
		Easing easing;
		bool isFrameBased;

		Tween::State state;
		bool isStarted;
		float startTime;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Tween(float duration = 1, Tween::Easing easing = NULL, bool isFrameBased = false);
		~Tween();

		// Tween parameter
		float getDuration();
		void setDuration(float duration);

		Tween::Easing getEasing();
		void setEasing(Tween::Easing easing);

		bool getIsFrameBased();
		void setIsFrameBased(bool isFrameBased);

		// Tween value
		float getValue(int index = 0);
		void clearAllTweens();

		// Tween state
		Tween::State getState();
		bool getIsStopped();
		bool getIsStarted();
		bool getIsCompleted();

	protected:
		// Tween value
		int addTween(const float from, const float to);
		int addTween(const float* from, const float to);
		int addTween(float* target, const float from, const float to);
		int addTween(float* target, const float* from, const float to);

		virtual void apply() = 0;
		virtual void clear() = 0;

		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		
	private:
		void start();
		void stop();
		void update();
		void updateHandler(ofEventArgs& event);
	};
}





namespace command {

	//--------------------------------------------------------------
	class NumericTween : public Tween {
	public:
		NumericTween(float duration = 1, Tween::Easing easing = NULL, bool isFrameBased = false) : Tween(duration, easing, isFrameBased) {
		}
		~NumericTween() {
		}
		virtual void apply() {
		};
		virtual void clear() {
		};
		int addTween(const float from, const float to) {
			return Tween::addTween(from, to);
		};
		int addTween(const float* from, const float to) {
			return Tween::addTween(from, to);
		};
		int addTween(float* target, const float from, const float to) {
			return Tween::addTween(target, from, to);
		};
		int addTween(float* target, const float* from, const float to) {
			return Tween::addTween(target, from, to);
		};
	private:
	};

	//--------------------------------------------------------------
	class ParameterTween : public Tween {
	public:
		ParameterTween(float duration = 1, Tween::Easing easing = NULL, bool isFrameBased = false) : Tween(duration, easing, isFrameBased) {
		}
		~ParameterTween() {
		}
		virtual void apply() {
			int numParameters = parameters.size();
			for (int i = 0; i < numParameters; ++i) {
				*parameters[i] = *values[i];
			}
		};
		virtual void clear() {
			parameters.clear();
			values.clear();
		};
		int addTween(ofParameter<float>* target, float from, float to) {
			parameters.push_back(target);
			float value = from;
			values.push_back(&value);
			return Tween::addTween(&value, from, to);
		};
		int addTween(ofParameter<float>* target, float to) {
			return addTween(target, *target, to);
		};
	private:
		vector<float*> values;
		vector<ofParameter<float>*> parameters;
	};

	//--------------------------------------------------------------
	class MeshTween : public Tween {
	public:
		MeshTween(float duration = 1, Tween::Easing easing = NULL, bool isFrameBased = false) : Tween(duration, easing, isFrameBased) {
		}
		~MeshTween() {
		}
		virtual void apply() {
			ofVec3f position;
			int tweenIndex = 0;
			for (vector<ofIndexType>::iterator vertexIt = vertexIndices.begin(); vertexIt != vertexIndices.end(); ++vertexIt) {
				ofIndexType vertexIndex = *vertexIt;
				position.set(getValue(tweenIndex), getValue(tweenIndex + 1), getValue(tweenIndex + 2));
				for (vector<ofMesh*>::iterator meshIt = meshes.begin(); meshIt != meshes.end(); ++meshIt) {
					(*meshIt)->setVertex(vertexIndex, position);
				}
				tweenIndex += 3;
			}
		};
		virtual void clear() {
			meshes.clear();
			vertexIndices.clear();
		};
		void addMesh(ofMesh* mesh) {
			vector<ofMesh*>::iterator it = find(meshes.begin(), meshes.end(), mesh);
			if (it == meshes.end()) {
				meshes.push_back(mesh);
			}
		};
		void addTween(ofIndexType vertexIndex, const ofVec3f& from, const ofVec3f& to) {
			Tween::addTween(from.x, to.x);
			Tween::addTween(from.y, to.y);
			Tween::addTween(from.z, to.z);
			vertexIndices.push_back(vertexIndex);
		};
		void addTween(ofIndexType vertexIndex, const ofVec3f* from, const ofVec3f& to) {
			Tween::addTween(&from->x, to.x);
			Tween::addTween(&from->y, to.y);
			Tween::addTween(&from->z, to.z);
			vertexIndices.push_back(vertexIndex);
		};
	private:
		vector<ofMesh*> meshes;
		vector<ofIndexType> vertexIndices;
	};
}




