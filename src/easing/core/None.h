#pragma once

#include "../Easing.h"

namespace cmd {

	namespace easing_internal {

		//--------------------------------------------------
		class None : public Easing {

		public:
			None() : Easing("Linear") {
			};

			virtual float calculate(float t, float b, float c, float d) const {
				return c * t / d + b;
			};
		};
	}
}




