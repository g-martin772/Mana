#include "manapch.h"
#include "Vec3.h"

namespace Mana {
	Vec3::Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vec3::set(Vec3 other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	Vec3& Vec3::add(Vec3 other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vec3& Vec3::substract(Vec3 other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vec3& Vec3::multiply(Vec3 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vec3& Vec3::divide(Vec3 other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}

	void Vec3::operator=(Vec3& other)
	{
		this->set(other);
	}

	Vec3 Vec3::operator+(Vec3& other)
	{
		return Vec3(this->add(other));
	}

	Vec3 Vec3::operator-(Vec3& other)
	{
		return Vec3(this->substract(other));
	}

	Vec3 Vec3::operator*(Vec3& other)
	{
		return Vec3(this->multiply(other));
	}

	Vec3 Vec3::operator/(Vec3& other)
	{
		return Vec3(this->divide(other));
	}

	void Vec3::operator+=(Vec3& other)
	{
		this->add(other);
	}

	void Vec3::operator-=(Vec3& other)
	{
		this->substract(other);
	}

	void Vec3::operator*=(Vec3& other)
	{
		this->multiply(other);
	}

	void Vec3::operator/=(Vec3& other)
	{
		this->divide(other);
	}
}
