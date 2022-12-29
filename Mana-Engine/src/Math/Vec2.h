#pragma once

#include "Core/Core.h"
#include "Vec3.h"

namespace Mana {
	template<class T>
	struct MANA_API Vec2 {
		T x, y;

		Vec2() {}
		Vec2(T x, T y) : x(x), y(y) { }
		~Vec2() = default;

		void set(Vec2& other) {
			this->x = other.x;
			this->y = other.y;
		}

		void set(Vec3<T>& other) {
			this->x = other.x;
			this->y = other.y;
		}

		void set(Vec4<T>& other) {
			this->x = other.x;
			this->y = other.y;
		}

		Vec2& add(Vec2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}

		Vec2& substract(Vec2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}

		Vec2& multiply(Vec2& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}

		Vec2& divide(Vec2& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}

		T operator[](int i) {
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			default: return 0;
			}
		}

		const T& operator[](int i) const {
			switch (i)
			{
			case 0: return x;
			case 1: return y;
			default: return 0;
			}
		}

		void operator=(Vec2& other) {
			this->set(other);
		}

		void operator=(Vec3<T>& other) {
			this->set(other);
		}

		void operator=(Vec4<T>& other) {
			this->set(other);
		}

		Vec2 operator+(Vec2& other) {
			return Vec2(this->add(other));
		}

		Vec2 operator-(Vec2& other) {
			return Vec2(this->substract(other));
		}

		Vec2 operator*(Vec2& other) {
			return Vec2(this->multiply(other));
		}

		Vec2 operator/(Vec2& other) {
			return Vec2(this->divide(other));
		}

		bool operator==(const Vec2& other) const {
			return this->x == other.x && this->y == other.y;
		}

		bool operator!=(const Vec2& other) const {
			return !(*this == other);
		}


		void operator+=(Vec2& other) {
			this->add(other);
		}

		void operator-=(Vec2& other) {
			this->substract(other);
		}

		void operator*=(Vec2& other) {
			this->multiply(other);
		}

		void operator/=(Vec2& other) {
			this->divide(other);
		}
	};

	using vec2  = Vec2<float>;
	using vec2f = Vec2<float>;
	using vec2d = Vec2<double>;
	using vec2i = Vec2<uint32_t>;
	using vec2l = Vec2<uint64_t>;
	using vec2c = Vec2<char>;
}
