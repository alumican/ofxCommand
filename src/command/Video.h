#pragma once

#include "ofMain.h"
#include "Command.h"

namespace cmd {

	class Video : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		ofVideoPlayer* videoPlayer;
		bool waitForComplete;
		bool closeOnComplete;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Video(ofVideoPlayer* videoPlayer = NULL, bool waitForComplete = false, bool closeOnComplete = false);
		~Video();

		ofVideoPlayer* getVideoPlayer();
		void setVideoPlayer(ofVideoPlayer* videoPlayer);

		bool getWaitForComplete();
		void setWaitForComplete(bool value);

		bool getCloseOnComplete();
		void setCloseOnComplete(bool value);

	protected:
		virtual void executeFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void update(ofEventArgs& event);
	};
	
}




