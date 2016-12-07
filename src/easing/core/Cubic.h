#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class CubicIn : public Easing {

	public:
		CubicIn() : Easing("easeCubicIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t /= d;
			return c * t * t * t + b;
		};
	};





	//--------------------------------------------------
	class CubicInOut : public Easing {

	public:
		CubicInOut() : Easing("easeCubicInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if ((t /= d / 2) < 1) return c / 2 * t * t * t + b;
			t -= 2;
			return c / 2 * (t * t * t + 2) + b;
		};
	};




	//--------------------------------------------------
	class CubicOut : public Easing {

	public:
		CubicOut() : Easing("easeCubicOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t = t / d - 1;
			return c * (t * t * t + 1) + b;
		};
	};
}




