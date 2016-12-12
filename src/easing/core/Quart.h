#pragma once

#include "../Easing.h"

namespace cmd {

	namespace easing_internal {

		//--------------------------------------------------
		class QuartIn : public Easing {

		public:
			QuartIn() : Easing("QuartIn") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				t /= d;
				return c * t * t * t * t + b;
			};
		};





		//--------------------------------------------------
		class QuartInOut : public Easing {

		public:
			QuartInOut() : Easing("QuartInOut") {
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
			QuartOut() : Easing("QuartOut") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				t = t / d - 1;
				return -c * (t * t * t * t - 1) + b;
			};
		};
	}
}




