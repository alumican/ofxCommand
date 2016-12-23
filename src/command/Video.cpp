#include "Video.h"

namespace cmd {

	//--------------------------------------------------------------
	Video::Video(ofVideoPlayer* videoPlayer, bool waitForComplete, bool closeOnComplete) {
		this->videoPlayer = videoPlayer;
		this->waitForComplete = waitForComplete;
		this->closeOnComplete = closeOnComplete;
	}

	//--------------------------------------------------------------
	Video::~Video() {
		if (videoPlayer != NULL) {
			ofRemoveListener(ofEvents().update, this, &Video::update);
			videoPlayer->stop();
			if (closeOnComplete) {
				videoPlayer->close();
			}
			videoPlayer = NULL;
		}
		ofLogVerbose() << "Bye Video";
	}





	//--------------------------------------------------------------
	ofVideoPlayer* Video::getVideoPlayer() const {
		return videoPlayer;
	}

	//--------------------------------------------------------------
	void Video::setVideoPlayer(ofVideoPlayer* videoPlayer) {
		this->videoPlayer = videoPlayer;
	}

	//--------------------------------------------------------------
	bool Video::getWaitForComplete() const {
		return waitForComplete;
	}

	//--------------------------------------------------------------
	void Video::setWaitForComplete(bool value) {
		this->waitForComplete = value;
	}

	//--------------------------------------------------------------
	bool Video::getCloseOnComplete() const {
		return closeOnComplete;
	}

	//--------------------------------------------------------------
	void Video::setCloseOnComplete(bool value) {
		this->closeOnComplete = value;
	}





	//--------------------------------------------------------------
	void Video::runFunction(Command* command) {
		if (videoPlayer != NULL) {
			ofAddListener(ofEvents().update, this, &Video::update);
			videoPlayer->setFrame(0);
			videoPlayer->play();
			if (!waitForComplete) {
				notifyComplete();
			}
		}
	}

	//--------------------------------------------------------------
	void Video::interruptFunction(Command* command) {
		ofRemoveListener(ofEvents().update, this, &Video::update);
		if (videoPlayer != NULL) {
			videoPlayer->stop();
		}
	}

	//--------------------------------------------------------------
	void Video::resetFunction(Command* command) {
		interruptFunction(command);
		if (videoPlayer != NULL) {
			videoPlayer->setFrame(0);
		}
	}





	//--------------------------------------------------------------
	void Video::update(ofEventArgs& event) {
		videoPlayer->update();
		if (videoPlayer->getIsMovieDone()) {
			ofRemoveListener(ofEvents().update, this, &Video::update);
			if (waitForComplete) {
				notifyComplete();
			}
		}
	}
}




