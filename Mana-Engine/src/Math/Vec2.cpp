#include "manapch.h"
#include "Vec2.h"

namespace Mana {
	Vec2::Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void Vec2::set(Vec2 other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	Vec2& Vec2::add(Vec2 other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vec2& Vec2::substract(Vec2 other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vec2& Vec2::multiply(Vec2 other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vec2& Vec2::divide(Vec2 other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}

	void Vec2::operator=(Vec2& other)
	{
		this->set(other);
	}

	Vec2 Vec2::operator+(Vec2& other)
	{
		return Vec2(this->add(other));
	}

	Vec2 Vec2::operator-(Vec2& other)
	{
		return Vec2(this->substract(other));
	}

	Vec2 Vec2::operator*(Vec2& other)
	{
		return Vec2(this->multiply(other));
	}

	Vec2 Vec2::operator/(Vec2& other)
	{
		return Vec2(this->divide(other));
	}

	bool Vec2::operator==(const Vec2& other) const
	{
		return this->x == other.x && this->y == other.y;
	}

	bool Vec2::operator!=(const Vec2& other) const
	{
		return !(*this == other);
	}

	void Vec2::operator+=(Vec2& other)
	{
		this->add(other);
	}

	void Vec2::operator-=(Vec2& other)
	{
		this->substract(other);
	}

	void Vec2::operator*=(Vec2& other)
	{
		this->multiply(other);
	}

	void Vec2::operator/=(Vec2& other)
	{
		this->divide(other);
	}
}

