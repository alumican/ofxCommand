#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class QuartIn : public Easing {

	public:
		QuartIn() : Easing("easeQuartIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t /= d;
			return c * t * t * t * t + b;
		};
	};





	//--------------------------------------------------
	class QuartInOut : public Easing {

	public:
		QuartInOut() : Easing("easeQuartInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if ((t /= d / 2) < 1) return c / 2 * t * t * t * t + b;
			t -= 2;
			return -c / 2 * (t * t * t * t - 2) + b;
		};
	};




	//--------------------------------------------------
	class QuartOut : public Easing {

	public:
		QuartOut() : Easing("easeQuartOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t = t / d - 1;
			return -c * (t * t * t * t - 1) + b;
		};
	};
}




