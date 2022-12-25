#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API Vec3 {
	public:
		Vec3(float x, float y, float z);
		~Vec3() = default;

		void set(Vec3 other);
		Vec3& add(Vec3 other);
		Vec3& substract(Vec3 other);
		Vec3& multiply(Vec3 other);
		Vec3& divide(Vec3 other);

		void operator=(Vec3& other);
		Vec3 operator+(Vec3& other);
		Vec3 operator-(Vec3& other);
		Vec3 operator*(Vec3& other);
		Vec3 operator/(Vec3& other);

		void operator+=(Vec3& other);
		void operator-=(Vec3& other);
		void operator*=(Vec3& other);
		void operator/=(Vec3& other);
	public:
		float x, y, z;
		float& r = x;
		float& g = y;
		float& b = z;
	};
}
