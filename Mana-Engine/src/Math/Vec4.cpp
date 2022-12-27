#include "manapch.h"
#include "Vec4.h"

namespace Mana {
	Vec4::Vec4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vec4::set(Vec4 other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	Vec4& Vec4::add(Vec4 other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vec4& Vec4::substract(Vec4 other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vec4& Vec4::multiply(Vec4 other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vec4& Vec4::divide(Vec4 other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}

	void Vec4::operator=(Vec4& other)
	{
		this->set(other);
	}

	Vec4 Vec4::operator+(Vec4& other)
	{
		return Vec4(this->add(other));
	}

	Vec4 Vec4::operator-(Vec4& other)
	{
		return Vec4(this->substract(other));
	}

	Vec4 Vec4::operator*(Vec4& other)
	{
		return Vec4(this->multiply(other));
	}

	Vec4 Vec4::operator/(Vec4& other)
	{
		return Vec4(this->divide(other));
	}

	bool Vec4::operator==(const Vec4& other) const
	{
		return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
	}

	bool Vec4::operator!=(const Vec4& other) const
	{
		return !(*this == other);
	}

	void Vec4::operator+=(Vec4& other)
	{
		this->add(other);
	}

	void Vec4::operator-=(Vec4& other)
	{
		this->substract(other);
	}

	void Vec4::operator*=(Vec4& other)
	{
		this->multiply(other);
	}

	void Vec4::operator/=(Vec4& other)
	{
		this->divide(other);
	}
}
