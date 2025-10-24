#pragma once
#include <type_traits>

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr> class Vector
{
public:
	T x, y;

	Vector<T>(T x, T y);

	Vector<T>();

	Vector<T>(Vector<T>& b);

	Vector<T>(const Vector<T>& b);

	Vector<T>& operator=(Vector<T>& b);

	Vector<T>& operator=(const Vector<T>& b);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T> operator+(Vector<U> v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T>& operator+=(const Vector<U>& v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T> operator-(Vector<U> v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T>& operator-=(const Vector<U>& v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T> operator*(U v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T>& operator*=(const U& v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T> operator/(U v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	Vector<T>& operator/=(const U& v2);

	template <typename U, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
	operator U() const;

	T magnitude();
};