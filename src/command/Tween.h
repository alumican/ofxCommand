#pragma once

#include "Command.h"
#include "../easing/Easing.h"
#include "../easing/Collection.h"

namespace cmd {

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
		ofEvent<Command&> onStart;
		ofEvent<Command&> onStop;
		ofEvent<Command&> onUpdate;

	protected:

	private:
		vector<TweenObject> objects;

		float duration;
		const cmd::Easing* easing;
		bool isFrameBased;

		Tween::State state;
		bool isStarted;
		float startTime;

		function<void()> atStartCallback;
		function<void()> atStopCallback;
		function<void()> atUpdateCallback;
		function<void()> atCompleteCallback;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Tween(string name, float duration = 1, const cmd::Easing& easing = cmd::Linear::None, bool isFrameBased = false);
		Tween(float duration = 1, const cmd::Easing& easing = cmd::Linear::None, bool isFrameBased = false);
		~Tween();

		// Set tween value
		Tween* animate(float& target, const float from, const float to);
		Tween* animate(float& target, const float to);

		// Set callback
		Tween* atStart(const function<void()>& callback);
		Tween* atStop(const function<void()>& callback);
		Tween* atUpdate(const function<void()>& callback);
		Tween* atComplete(const function<void()>& callback);

		// Clear tween value
		void clearAllTweens();

		// Tween parameter
		float getDuration();
		void setDuration(float duration);

		const cmd::Easing& getEasing();
		void setEasing(const cmd::Easing& easing);

		bool getIsFrameBased();
		void setIsFrameBased(bool isFrameBased);

		// Tween state
		Tween::State getState();

		bool getIsStopped();
		bool getIsStarted();
		bool getIsCompleted();

	protected:

		virtual void apply();
		virtual void clear();

		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void setup(float duration, const cmd::Easing& easing, bool isFrameBased);
		void start();
		void stop();
		void update();
		void updateHandler(ofEventArgs& event);
	};
}





/*
namespace cmd {

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
*/




