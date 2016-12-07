#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class ElasticIn : public Easing {

	public:
		ElasticIn(float a = 1, float p = 1) : Easing("easeElasticIn") {
			this->a = a;
			this->p = p;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if (t == 0) return b;
			if ((t /= d) == 1) return b + c;
			float p = this->p * d * .3f;
			float a = this->a * c;
			float s = p / 4;
			float postFix = a * pow(2, 10 * (t -= 1));	// this is a fix, again, with post-increment operators
			return -(postFix * sin((t * d - s) * (2 * M_PI) / p)) + b;
		};

		float a;
		float p;
	};





	//--------------------------------------------------
	class ElasticInOut : public Easing {

	public:
		ElasticInOut(float a = 1, float p = 1) : Easing("easeElasticInOut") {
			this->a = a;
			this->p = p;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if (t == 0) return b;
			if ((t /= d / 2) == 2) return b + c;
			float p = this->p * d * (.3f * 1.5f);
			float a = this->a * c;
			float s = p / 4;

			if (t < 1) {
				float postFix = a * pow(2, 10 * (t -= 1));	// postIncrement is evil
				return -.5f * (postFix * sin((t * d - s) * (2 * M_PI) / p)) + b;
			}
			float postFix = a * pow(2, -10 * (t -= 1));	// postIncrement is evil
			return postFix * sin((t * d - s) * (2 * M_PI) / p) * .5f + c + b;
		};

		float a;
		float p;
	};




	//--------------------------------------------------
	class ElasticOut : public Easing {

	public:
		ElasticOut(float a = 1, float p = 1) : Easing("easeElasticOut") {
			this->a = a;
			this->p = p;
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if (t == 0) return b;
			if ((t /= d) == 1) return b + c;
			float p = this->p * d * .3f;
			float a = this->a * c;
			float s = p / 4;
			return (a * pow(2, -10 * t) * sin((t * d - s) * (2 * M_PI) / p) + c + b);
		};

		float a;
		float p;
	};
}




