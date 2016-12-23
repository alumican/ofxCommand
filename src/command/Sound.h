#pragma once

#include "Command.h"

namespace cmd {

	class Sound : public Command {

		// ----------------------------------------
		//
		// MEMBER
		//
		// ----------------------------------------

	public:

	protected:

	private:
		ofSoundPlayer* soundPlayer;
		bool waitForComplete;
		bool unloadOnComplete;
		float prevPosition;





		// ----------------------------------------
		//
		// METHOD
		//
		// ----------------------------------------

	public:
		Sound(ofSoundPlayer* soundPlayer = NULL, bool waitForComplete = false, bool unloadOnComplete = false);
		~Sound();

		ofSoundPlayer* getSoundPlayer() const;
		void setSoundPlayer(ofSoundPlayer* soundPlayer);

		bool getWaitForComplete() const;
		void setWaitForComplete(bool value);

		bool getUnloadOnComplete() const;
		void setUnloadOnComplete(bool value);

	protected:
		virtual void runFunction(Command* command);
		virtual void interruptFunction(Command* command);
		virtual void resetFunction(Command* command);

	private:
		void update(ofEventArgs& event);
	};
	
}




