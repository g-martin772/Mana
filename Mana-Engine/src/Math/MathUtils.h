#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Mana {
	float toRadians(float degrees)
	{
		return degrees * (M_PI / 180.0f);
	}
}
