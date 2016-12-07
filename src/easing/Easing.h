#pragma once

#include "ofMain.h"

#define _USE_MATH_DEFINES
#include <math.h>

namespace cmd {

	class Easing {
	public:
		Easing(string name) {
			this->name = name;
		};

		string getName() const {
			return name;
		}

		virtual float calculate(float t, float b, float c, float d) const {
			return c * t / d + b;
		};

	private:
		string name;
	};
}




