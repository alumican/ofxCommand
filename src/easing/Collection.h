#pragma once

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
		static None None;
	};

	class Back {
	public:
		static const BackIn In;
		//static const BackIn InWith(float s = 1.70158) { return BackIn(s); };
		static const BackOut Out;
		//static const BackOut OutWith(float s = 1.70158) { return BackOut(s); };
		static const BackInOut InOut;
		//static const BackInOut InOutWith(float s = 1.70158) { return BackInOut(s); };
	};

	class Bounce {
	public:
		static const BounceIn In;
		static const BounceOut Out;
		static const BounceInOut InOut;
	};

	class Circ {
	public:
		static const CircIn In;
		static const CircOut Out;
		static const CircInOut InOut;
	};

	class Cubic {
	public:
		static const CubicIn In;
		static const CubicOut Out;
		static const CubicInOut InOut;
	};

	class Elastic {
	public:
		static const ElasticIn In;
		//static const ElasticIn InWith(float a = 1, float p = 1) { return ElasticIn(a, p); };
		static const ElasticOut Out;
		//static const ElasticOut OutWith(float a = 1, float p = 1) { return ElasticOut(a, p); };
		static const ElasticInOut InOut;
		//static const ElasticInOut InOutWith(float a = 1, float p = 1) { return ElasticInOut(a, p); };
	};

	class Expo {
	public:
		static const ExpoIn In;
		static const ExpoOut Out;
		static const ExpoInOut InOut;
	};

	class Quad {
	public:
		static const QuadIn In;
		static const QuadOut Out;
		static const QuadInOut InOut;
	};

	class Quart {
	public:
		static const QuartIn In;
		static const QuartOut Out;
		static const QuartInOut InOut;
	};

	class Quint {
	public:
		static const QuintIn In;
		static const QuintOut Out;
		static const QuintInOut InOut;
	};

	class Sine {
	public:
		static const SineIn In;
		static const SineOut Out;
		static const SineInOut InOut;
	};
}




