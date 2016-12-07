#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class QuadIn : public Easing {

	public:
		QuadIn() : Easing("easeQuadIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t /= d;
			return c * t * t + b;
		};
	};





	//--------------------------------------------------
	class QuadInOut : public Easing {

	public:
		QuadInOut() : Easing("easeQuadInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if ((t /= d / 2) < 1) return ((c / 2) * (t * t)) + b;
			--t;
			return -c / 2 * (((t - 2) * t) - 1) + b;
		};
	};




	//--------------------------------------------------
	class QuadOut : public Easing {

	public:
		QuadOut() : Easing("easeQuadOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t /= d;
			return -c * t * (t - 2) + b;
		};
	};
}




