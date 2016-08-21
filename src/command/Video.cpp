#include "command/Video.h"

using namespace command;

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
ofVideoPlayer* Video::getVideoPlayer() {
	return videoPlayer;
}





//--------------------------------------------------------------
void Video::setVideoPlayer(ofVideoPlayer* videoPlayer) {
	this->videoPlayer = videoPlayer;
}





//--------------------------------------------------------------
bool Video::getWaitForComplete() {
	return waitForComplete;
}





//--------------------------------------------------------------
void Video::setWaitForComplete(bool value) {
	this->waitForComplete = value;
}





//--------------------------------------------------------------
bool Video::getCloseOnComplete() {
	return closeOnComplete;
}





//--------------------------------------------------------------
void Video::setCloseOnComplete(bool value) {
	this->closeOnComplete = value;
}





//--------------------------------------------------------------
void Video::executeFunction(Command* command) {
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
void Video::update(ofEventArgs& event) {
	videoPlayer->update();
	if (videoPlayer->getIsMovieDone()) {
		ofRemoveListener(ofEvents().update, this, &Video::update);
		if (waitForComplete) {
			notifyComplete();
		}
	}
}




