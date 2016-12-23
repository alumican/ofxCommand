#include "Sound.h"

namespace cmd {

	//--------------------------------------------------------------
	Sound::Sound(ofSoundPlayer* soundPlayer, bool waitForComplete, bool unloadOnComplete) {
		this->soundPlayer = soundPlayer;
		this->waitForComplete = waitForComplete;
		this->unloadOnComplete = unloadOnComplete;
	}

	//--------------------------------------------------------------
	Sound::~Sound() {
		if (soundPlayer != NULL) {
			ofRemoveListener(ofEvents().update, this, &Sound::update);
			soundPlayer->stop();
			if (unloadOnComplete) {
				soundPlayer->unload();
			}
			soundPlayer = NULL;
		}
		ofLogVerbose() << "Bye Sound";
	}





	//--------------------------------------------------------------
	ofSoundPlayer* Sound::getSoundPlayer() const {
		return soundPlayer;
	}

	//--------------------------------------------------------------
	void Sound::setSoundPlayer(ofSoundPlayer* soundPlayer) {
		this->soundPlayer = soundPlayer;
	}

	//--------------------------------------------------------------
	bool Sound::getWaitForComplete() const {
		return waitForComplete;
	}

	//--------------------------------------------------------------
	void Sound::setWaitForComplete(bool value) {
		this->waitForComplete = value;
	}

	//--------------------------------------------------------------
	bool Sound::getUnloadOnComplete() const {
		return unloadOnComplete;
	}

	//--------------------------------------------------------------
	void Sound::setUnloadOnComplete(bool value) {
		this->unloadOnComplete = value;
	}





	//--------------------------------------------------------------
	void Sound::runFunction(Command* command) {
		if (soundPlayer != NULL) {
			soundPlayer->setPosition(0);
			soundPlayer->play();
			if (waitForComplete) {
				prevPosition = 0;
				ofAddListener(ofEvents().update, this, &Sound::update);
			} else {
				notifyComplete();
			}
		}
	}

	//--------------------------------------------------------------
	void Sound::interruptFunction(Command* command) {
		ofRemoveListener(ofEvents().update, this, &Sound::update);
		if (soundPlayer != NULL) {
			soundPlayer->stop();
		}
	}

	//--------------------------------------------------------------
	void Sound::resetFunction(Command* command) {
		interruptFunction(command);
		if (soundPlayer != NULL) {
			soundPlayer->setPosition(0);
		}
	}





	//--------------------------------------------------------------
	void Sound::update(ofEventArgs& event) {
		float position = soundPlayer->getPosition();
		if (prevPosition > 0 && position == 0) {
			ofRemoveListener(ofEvents().update, this, &Sound::update);
			notifyComplete();
		}
		prevPosition = position;
	}
}




