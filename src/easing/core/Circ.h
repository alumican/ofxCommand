#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class CircIn : public Easing {

	public:
		CircIn() : Easing("easeCircIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t /= d;
			return -c * (sqrt(1 - t * t) - 1) + b;
		};
	};





	//--------------------------------------------------
	class CircInOut : public Easing {

	public:
		CircInOut() : Easing("easeCircInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if ((t /= d / 2) < 1) return -c / 2 * (sqrt(1 - t * t) - 1) + b;
			t -= 2;
			return c / 2 * (sqrt(1 - t * t) + 1) + b;
		};
	};




	//--------------------------------------------------
	class CircOut : public Easing {

	public:
		CircOut() : Easing("easeCircOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t = t / d - 1;
			return c * sqrt(1 - t * t) + b;
		};
	};
}




