#pragma once

namespace command {

	enum CommandState {
		SLEEPING     = 0,
		EXECUTING    = 1,
		INTERRUPTING = 2
	};	
}