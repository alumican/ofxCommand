#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class SineIn : public Easing {

	public:
		SineIn() : Easing("easeSineIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			return -c * cos(t / d * (M_PI / 2)) + c + b;
		};
	};





	//--------------------------------------------------
	class SineInOut : public Easing {

	public:
		SineInOut() : Easing("easeSineInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			return -c / 2 * (cos(t / d * M_PI) - 1) + b;
		};
	};




	//--------------------------------------------------
	class SineOut : public Easing {

	public:
		SineOut() : Easing("easeSineOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			return c * sin(t / d * (M_PI / 2)) + b;
		};
	};}




