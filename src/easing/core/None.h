#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class None : public Easing {

	public:
		None() : Easing("linear") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			return c * t / d + b;
		};
	};
}




