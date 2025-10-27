#include <math.h>

#pragma once

template <typename T> class Vector
{
public:
	T x, y;

	Vector<T>(T x, T y) : x(x), y(y)
	{ }

	Vector<T>() : x(0), y(0)
	{ }

	Vector<T>(Vector<T>& b)
	{
		x = b.x;
		y = b.y;
	}

	Vector<T>(const Vector<T>& b)
	{
		x = b.x;
		y = b.y;
	}

	Vector<T>& operator=(Vector<T>& b)
	{
		x = b.x;
		y = b.y;
		return *this;
	}

	Vector<T>& operator=(const Vector<T>& b)
	{
		x = b.x;
		y = b.y;
		return *this;
	}

	Vector<T> operator+(Vector<T> v2)
	{
		return Vector<T>(x + v2.x, y + v2.y);
	}

	Vector<T>& operator+=(const Vector<T>& v2)
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}

	Vector<T> operator-(Vector<T> v2)
	{
		return Vector<T>(x - v2.x, y - v2.y);
	}

	Vector<T>& operator-=(const Vector<T>& v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}

	Vector<T> operator*(double v2)
	{
		return Vector<T>(x * v2, y * v2);
	}

	Vector<T>& operator*=(const double& v2)
	{
		x *= v2;
		y *= v2;
		return *this;
	}

	Vector<T> operator/(double v2)
	{
		return Vector<T>(x / v2, y / v2);
	}

	Vector<T>& operator/=(const double& v2)
	{
		x /= v2;
		y /= v2;
		return *this;
	}

	T magnitude()
	{
		return sqrt(x * x + y * y);
	}

	T sqrMagnitude()
	{
		return x * x + y * y;
	}
};