#pragma once

#include "Core/Core.h"

namespace Mana {
	template<class T>
	struct MANA_API Vec4 {
		T x, y, z, w;
		T& r = x;
		T& g = y;
		T& b = z;

		Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
		~Vec4() = default;

		void set(Vec4 other) {
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
			this->w = other.w;
		}

		Vec4& add(Vec4 other) {
			x += other.x;
			y += other.y;
			z += other.z;
			w += other.w;
			return *this;
		}

		Vec4& substract(Vec4 other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			w -= other.w;
			return *this;
		}

		Vec4& multiply(Vec4 other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			w *= other.w;
			return *this;
		}

		Vec4& divide(Vec4 other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			w /= other.w;
			return *this;
		}

		void operator=(Vec4& other) {
			this->set(other);
		}

		Vec4 operator+(Vec4& other) {
			return Vec4(this->add(other));
		}

		Vec4 operator-(Vec4& other) {
			return Vec4(this->substract(other));
		}

		Vec4 operator*(Vec4& other) {
			return Vec4(this->multiply(other));
		}

		Vec4 operator/(Vec4& other) {
			return Vec4(this->divide(other));
		}

		bool operator==(const Vec4& other) const {
			return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
		}

		bool operator!=(const Vec4& other) const {
			return !(*this == other);
		}


		void operator+=(Vec4& other) {
			this->add(other);
		}

		void operator-=(Vec4& other) {
			this->substract(other);
		}

		void operator*=(Vec4& other) {
			this->multiply(other);
		}

		void operator/=(Vec4& other) {
			this->divide(other);
		}
	};

	using vec4 = Vec4<float>;
	using vec4f = Vec4<float>;
	using vec4d = Vec4<double>;
	using vec4i = Vec4<uint32_t>;
	using vec4l = Vec4<uint64_t>;
	using vec4c = Vec4<char>;
}
