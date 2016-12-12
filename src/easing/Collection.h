#pragma once

#include "Easing.h"
#include "core/None.h"
#include "core/Back.h"
#include "core/Bounce.h"
#include "core/Circ.h"
#include "core/Cubic.h"
#include "core/Elastic.h"
#include "core/Expo.h"
#include "core/Quad.h"
#include "core/Quart.h"
#include "core/Quint.h"
#include "core/Sine.h"

namespace cmd {

	class Linear {
	public:
		static const easing_internal::None None;
	};

	class Back {
	public:
		static const easing_internal::BackIn In;
		//static const easing_internal::BackIn InWith(float s = 1.70158) { return BackIn(s); };
		static const easing_internal::BackOut Out;
		//static const easing_internal::BackOut OutWith(float s = 1.70158) { return BackOut(s); };
		static const easing_internal::BackInOut InOut;
		//static const easing_internal::BackInOut InOutWith(float s = 1.70158) { return BackInOut(s); };
	};

	class Bounce {
	public:
		static const easing_internal::BounceIn In;
		static const easing_internal::BounceOut Out;
		static const easing_internal::BounceInOut InOut;
	};

	class Circ {
	public:
		static const easing_internal::CircIn In;
		static const easing_internal::CircOut Out;
		static const easing_internal::CircInOut InOut;
	};

	class Cubic {
	public:
		static const easing_internal::CubicIn In;
		static const easing_internal::CubicOut Out;
		static const easing_internal::CubicInOut InOut;
	};

	class Elastic {
	public:
		static const easing_internal::ElasticIn In;
		//static const easing_internal::ElasticIn InWith(float a = 1, float p = 1) { return ElasticIn(a, p); };
		static const easing_internal::ElasticOut Out;
		//static const easing_internal::ElasticOut OutWith(float a = 1, float p = 1) { return ElasticOut(a, p); };
		static const easing_internal::ElasticInOut InOut;
		//static const easing_internal::ElasticInOut InOutWith(float a = 1, float p = 1) { return ElasticInOut(a, p); };
	};

	class Expo {
	public:
		static const easing_internal::ExpoIn In;
		static const easing_internal::ExpoOut Out;
		static const easing_internal::ExpoInOut InOut;
	};

	class Quad {
	public:
		static const easing_internal::QuadIn In;
		static const easing_internal::QuadOut Out;
		static const easing_internal::QuadInOut InOut;
	};

	class Quart {
	public:
		static const easing_internal::QuartIn In;
		static const easing_internal::QuartOut Out;
		static const easing_internal::QuartInOut InOut;
	};

	class Quint {
	public:
		static const easing_internal::QuintIn In;
		static const easing_internal::QuintOut Out;
		static const easing_internal::QuintInOut InOut;
	};

	class Sine {
	public:
		static const easing_internal::SineIn In;
		static const easing_internal::SineOut Out;
		static const easing_internal::SineInOut InOut;
	};





	// ----------------------------------------
	//
	// Static
	//
	// ----------------------------------------

	namespace easing_internal {

		static vector<const Easing*> easings;
		static map<string, const Easing*> easingsByName;
		static bool isInitialized = false;

		static void initialize() {
			if (isInitialized) return;
			isInitialized = true;

			easings = {
				&Linear::None,

				&Sine::In,
				&Sine::Out,
				&Sine::InOut,

				&Quad::In,
				&Quad::Out,
				&Quad::InOut,

				&Cubic::In,
				&Cubic::Out,
				&Cubic::InOut,

				&Quart::In,
				&Quart::Out,
				&Quart::InOut,

				&Quint::In,
				&Quint::Out,
				&Quint::InOut,

				&Expo::In,
				&Expo::Out,
				&Expo::InOut,

				&Circ::In,
				&Circ::Out,
				&Circ::InOut,

				&Back::In,
				&Back::Out,
				&Back::InOut,

				&Elastic::In,
				&Elastic::Out,
				&Elastic::InOut,

				&Bounce::In,
				&Bounce::Out,
				&Bounce::InOut,
			};

			for (vector<const Easing*>::iterator it = easings.begin(); it != easings.end(); ++it) {
				const Easing* easing = *it;
				easingsByName[easing->getName()] = easing;
			}
		};
	}
	
	static const vector<const Easing*>& getEasings() {
		easing_internal::initialize();
		return easing_internal::easings;
	};

	static const Easing& getEasingByName(string name) {
		easing_internal::initialize();
		return easing_internal::easingsByName.count(name) > 0 ? *easing_internal::easingsByName[name] : Linear::None;
	};
}




