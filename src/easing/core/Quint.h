#pragma once

#include "../Easing.h"

namespace cmd {

	namespace easing_internal {

		//--------------------------------------------------
		class QuintIn : public Easing {

		public:
			QuintIn() : Easing("QuintIn") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				t /= d;
				return c * t * t * t * t * t + b;
			};
		};





		//--------------------------------------------------
		class QuintInOut : public Easing {

		public:
			QuintInOut() : Easing("QuintInOut") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				if ((t /= d / 2) < 1) return c / 2 * t * t * t * t * t + b;
				t -= 2;
				return c / 2 * (t * t * t * t * t + 2) + b;
			};
		};




		//--------------------------------------------------
		class QuintOut : public Easing {

		public:
			QuintOut() : Easing("QuintOut") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				t = t / d - 1;
				return c * (t * t * t * t * t + 1) + b;
			};
		};
	}
}




