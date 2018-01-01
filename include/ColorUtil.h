#ifndef _COLOR_UTIL_
#define _COLOR_UTIL_

#include "libtcod.hpp"
#include "globals.h"

namespace ColorUtil
{
	class Color {
	public:
		float r, g, b;

		Color() { r = 1; g = 1; b = 1; }
		Color(float fr, float fg, float fb) { r = fr; g = fg; b = fb; }
		~Color() {}

		bool ColorUtil::Color::operator==(ColorUtil::Color rhs) {
			if (this->r == rhs.r && this->g == rhs.g && this->b == rhs.b)
				return true;
			else
				return false;
		}

		bool ColorUtil::Color::operator!=(ColorUtil::Color rhs) {
			if (*this == rhs)
				return false;
			else
				return true;
		}

		// returns the color converted to TCODColor format
		TCODColor ColorUtil::Color::toTCODColor() {
			return TCODColor((int)(r * 255), (int)(g * 255), (int)(b * 255));
		}

		void ColorUtil::Color::interpolateColor(ColorUtil::Color dest)
		{

			float factor = (float)FRAMES_PER_SECOND * 4;
			float r = (float)(dest.r - this->r) / factor;
			float g = (float)(dest.g - this->g) / factor;
			float b = (float)(dest.b - this->b) / factor;

			//std::cout << "r = " << r << '\n';
			if (r > -0.0005 && r < 0.0005) { this->r = dest.r; }
			else {
				//if (r < 0) { r = MIN(r, -1); }
				//else if (r > 0) { r = MAX(r, 1); }
				this->r += r;
			}

			//std::cout << "g = " << g << '\n';
			if (g > -0.0005 && g < 0.0005) { this->g = dest.g; }
			else {
				this->g += g;
			}

			//std::cout << "b = " << b << '\n';
			if (b > -0.0005 && b < 0.0005) { this->b = dest.b; }
			else {
				this->b += b;
			}
		}
	};

	//TCODColor floatTo255(float r, float g, float b)
	//{
	//	TCODColor result;
	//	result = TCODColor((int)(r*255), (int)(g*255), (int)(b*255));
	//	return result;
	//}
};

#endif