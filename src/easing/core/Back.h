#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class BackIn : public Easing {

	public:
		BackIn(float s = 1.70158) : Easing("easeBackIn") {
			this->s = s;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			float postFix = t /= d;
			return c * (postFix)*t * ((s + 1) * t - s) + b;
		};

		float s;
	};





	//--------------------------------------------------
	class BackInOut : public Easing {

	public:
		BackInOut(float s = 1.70158) : Easing("easeBackInOut") {
			this->s = s;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			float s2 = s * 1.525f;
			if ((t /= d / 2) < 1) {
				return c / 2 * (t * t * ((s2 + 1) * t - s2)) + b;
			}
			float postFix = t -= 2;
			return c / 2 * ((postFix)*t * ((s2 + 1) * t + s2) + 2) + b;
		};

		float s;
	};




	//--------------------------------------------------
	class BackOut : public Easing {

	public:
		BackOut(float s = 1.70158) : Easing("easeBackOut") {
			this->s = s;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t = t / d - 1;
			return c * (t * t * ((s + 1) * t + s) + 1) + b;
		};

		float s;
	};
}




