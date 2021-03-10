#pragma once

#include <iostream>

struct Vector2
{
	float x;
	float y;

	/**
	* Creates a Vector2 with x and 0 equal to 0.
	*/
	Vector2()
	{
		this->x = 0.f;
		this->y = 0.f;
	}

	/**
	* Creates a new Vector2
	* 
	* @param x X value
	* @param y Y value
	*/
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline Vector2 operator+(const Vector2& v2) const
	{
		return Vector2(x + v2.x, y + v2.y);
	}

	inline Vector2 operator-(const Vector2& v2) const
	{
		return Vector2(x - v2.x, y - v2.y);
	}

	inline Vector2 operator*(const Vector2& v2) const
	{
		return Vector2(x * v2.x, y * v2.y);
	}

	inline Vector2 operator/(const Vector2& v2) const
	{
		return Vector2(x / v2.x, y / v2.y);
	}


	inline friend Vector2& operator+=(Vector2& v1, const Vector2& v2)
	{
		v1.x += v2.x;
		v1.y += v2.y;
		return v1;
	}

	inline friend Vector2& operator-=(Vector2& v1, const Vector2& v2)
	{
		v1.x -= v2.x;
		v1.y -= v2.y;

		return v1;
	}

	inline friend Vector2& operator*=(Vector2& v1, const Vector2& v2)
	{
		v1.x *= v2.x;
		v1.y *= v2.y;
		return v1;
	}

	inline friend Vector2& operator/=(Vector2& v1, const Vector2& v2)
	{
		v1.x /= v2.x;
		v1.y /= v2.y;
		return v1;
	}

	inline friend std::ostream& operator<<(std::ostream& stream, const Vector2& v)
	{
		stream << "(" << v.x << "," << v.y << ")";
		return stream;
	}
};