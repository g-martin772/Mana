#pragma once

#include "Core/Core.h"

namespace Mana {
	template<class T>
	struct MANA_API Vec3 {
		T x, y, z;
		T& r = x;
		T& g = y;
		T& b = z;

		Vec3(T x, T y, T z) : x(x), y(y), z(z) { }
		~Vec3() = default;

		void set(Vec3 other) {
			this->x = other.x;
			this->y = other.y;
			this->z = other.z;
		}

		Vec3& add(Vec3 other) {
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		Vec3& substract(Vec3 other) {
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		Vec3& multiply(Vec3 other) {
			x *= other.x;
			y *= other.y;
			z *= other.z;
			return *this;
		}

		Vec3& divide(Vec3 other) {
			x /= other.x;
			y /= other.y;
			z /= other.z;
			return *this;
		}

		void operator=(Vec3& other) {
			this->set(other);
		}

		Vec3 operator+(Vec3& other) {
			return Vec3(this->add(other));
		}

		Vec3 operator-(Vec3& other) {
			return Vec3(this->substract(other));
		}

		Vec3 operator*(Vec3& other) {
			return Vec3(this->multiply(other));
		}

		Vec3 operator/(Vec3& other) {
			return Vec3(this->divide(other));
		}

		bool operator==(const Vec3& other) const {
			return this->x == other.x && this->y == other.y && this->z == other.z;
		}

		bool operator!=(const Vec3& other) const {
			return !(*this == other);
		}


		void operator+=(Vec3& other) {
			this->add(other);
		}

		void operator-=(Vec3& other) {
			this->substract(other);
		}

		void operator*=(Vec3& other) {
			this->multiply(other);
		}

		void operator/=(Vec3& other) {
			this->divide(other);
		}
	};

	using vec3 = Vec3<float>;
	using vec3f = Vec3<float>;
	using vec3d = Vec3<double>;
	using vec3i = Vec3<uint32_t>;
	using vec3l = Vec3<uint64_t>;
	using vec3c = Vec3<char>;
}
