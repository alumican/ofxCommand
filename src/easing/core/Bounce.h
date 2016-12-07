#pragma once

#include "../Easing.h"

namespace cmd {

	//--------------------------------------------------
	class BounceIn : public Easing {

	public:
		BounceIn() : Easing("easeBounceIn") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			t = d - t;
			if ((t /= d) < (1 / 2.75f)) {
				return c - c * (7.5625f * t * t) + b;
			} else if (t < (2 / 2.75f)) {
				float postFix = t -= (1.5f / 2.75f);
				return c - c * (7.5625f * (postFix)*t + .75f) + b;
			} else if (t < (2.5 / 2.75)) {
				float postFix = t -= (2.25f / 2.75f);
				return c - c * (7.5625f * (postFix)*t + .9375f) + b;
			} else {
				float postFix = t -= (2.625f / 2.75f);
				return c - c * (7.5625f * (postFix)*t + .984375f) + b;
			}
		};
	};





	//--------------------------------------------------
	class BounceInOut : public Easing {

	public:
		BounceInOut() : Easing("easeBounceInOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if (t < d / 2) {
				t = d - t * 2;
				if ((t /= d) < (1 / 2.75f)) {
					return (c - c * (7.5625f * t * t)) * 0.5f + b;
				} else if (t < (2 / 2.75f)) {
					float postFix = t -= (1.5f / 2.75f);
					return (c - c * (7.5625f * (postFix)*t + .75f)) * 0.5f + b;
				} else if (t < (2.5 / 2.75)) {
					float postFix = t -= (2.25f / 2.75f);
					return (c - c * (7.5625f * (postFix)*t + .9375f)) * 0.5f + b;
				} else {
					float postFix = t -= (2.625f / 2.75f);
					return (c - c * (7.5625f * (postFix)*t + .984375f)) * 0.5f + b;
				}
			} else {
				t = t * 2 - d;
				if ((t /= d) < (1 / 2.75f)) {
					return (c * (7.5625f * t * t)) * 0.5f + c * 0.5f + b;
				} else if (t < (2 / 2.75f)) {
					float postFix = t -= (1.5f / 2.75f);
					return (c * (7.5625f * (postFix)*t + .75f)) * 0.5f + c * 0.5f + b;
				} else if (t < (2.5 / 2.75)) {
					float postFix = t -= (2.25f / 2.75f);
					return (c * (7.5625f * (postFix)*t + .9375f)) * 0.5f + c * 0.5f + b;
				} else {
					float postFix = t -= (2.625f / 2.75f);
					return (c * (7.5625f * (postFix)*t + .984375f)) * 0.5f + c * 0.5f + b;
				}
			}
		};
	};





	//--------------------------------------------------
	class BounceOut : public Easing {

	public:
		BounceOut() : Easing("easeBounceOut") {
		};

		virtual float calculate(float t, float b, float c, float d) const {
			if ((t /= d) < (1 / 2.75f)) {
				return c * (7.5625f * t * t) + b;
			} else if (t < (2 / 2.75f)) {
				float postFix = t -= (1.5f / 2.75f);
				return c * (7.5625f * (postFix)*t + .75f) + b;
			} else if (t < (2.5 / 2.75)) {
				float postFix = t -= (2.25f / 2.75f);
				return c * (7.5625f * (postFix)*t + .9375f) + b;
			} else {
				float postFix = t -= (2.625f / 2.75f);
				return c * (7.5625f * (postFix)*t + .984375f) + b;
			}
		};
	};
}




