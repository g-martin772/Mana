#pragma once

#include "Core/Core.h"

namespace Mana {
	class MANA_API Vec2 {
	public:
		Vec2(float x, float y);
		~Vec2() = default;

		void set(Vec2 other);
		Vec2& add(Vec2 other);
		Vec2& substract(Vec2 other);
		Vec2& multiply(Vec2 other);
		Vec2& divide(Vec2 other);

		void operator=(Vec2& other);
		Vec2 operator+(Vec2& other);
		Vec2 operator-(Vec2& other);
		Vec2 operator*(Vec2& other);
		Vec2 operator/(Vec2& other);

		void operator+=(Vec2& other);
		void operator-=(Vec2& other);
		void operator*=(Vec2& other);
		void operator/=(Vec2& other);
	public:
		float x;
		float y;
	};
}