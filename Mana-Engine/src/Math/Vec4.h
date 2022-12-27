#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API Vec4 {
	public:
		Vec4(float x, float y, float z, float w);
		~Vec4() = default;

		void set(Vec4 other);
		Vec4& add(Vec4 other);
		Vec4& substract(Vec4 other);
		Vec4& multiply(Vec4 other);
		Vec4& divide(Vec4 other);

		void operator=(Vec4& other);
		Vec4 operator+(Vec4& other);
		Vec4 operator-(Vec4& other);
		Vec4 operator*(Vec4& other);
		Vec4 operator/(Vec4& other);
		
		bool operator==(const Vec4& other) const;
		bool operator!=(const Vec4& other) const;

		void operator+=(Vec4& other);
		void operator-=(Vec4& other);
		void operator*=(Vec4& other);
		void operator/=(Vec4& other);
	public:
		float x, y, z, w;
		float& r = x;
		float& g = y;
		float& b = z;
		float& a = w;
	};
}
