//#include "Vector.h"
//#include <math.h>
//
//template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>> class Vector
//{
//public:
//	T x, y;
//
//	Vector<T>(T x, T y) : x(x), y(y)
//	{ }
//
//	Vector<T>() : x(0), y(0)
//	{ }
//
//	Vector<T>(Vector<T>& b)
//	{
//		x = b.x;
//		y = b.y;
//	}
//
//	Vector<T>(const Vector<T>& b)
//	{
//		x = b.x;
//		y = b.y;
//	}
//
//	Vector<T>& operator=(Vector<T>& b)
//	{
//		x = b.x;
//		y = b.y;
//		return *this;
//	}
//
//	Vector<T>& operator=(const Vector<T>& b)
//	{
//		x = b.x;
//		y = b.y;
//		return *this;
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T> operator+(Vector<U> v2)
//	{
//		return Vector<T>(x + v2.x, y + v2.y);
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T>& operator+=(const Vector<U>& v2)
//	{
//		x += v2.x;
//		y += v2.y;
//		return *this;
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T> operator-(Vector<U> v2)
//	{
//		return Vector<T>(x - v2.x, y - v2.y);
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T>& operator-=(const Vector<U>& v2)
//	{
//		x -= v2.x;
//		y -= v2.y;
//		return *this;
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T> operator*(U v2)
//	{
//		return Vector<T>(x * v2, y * v2);
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T>& operator*=(const U& v2)
//	{
//		x *= v2;
//		y *= v2;
//		return *this;
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T> operator/(U v2)
//	{
//		return Vector<T>(x / v2, y / v2);
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	Vector<T>& operator/=(const U& v2)
//	{
//		x /= v2;
//		y /= v2;
//		return *this;
//	}
//
//	template <typename U, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
//	explicit operator U() const
//	{
//		return Vector<U>((U)x, (U)y);
//	}
//
//	T magnitude()
//	{
//		return sqrt(x * x + y * y);
//	}
//};