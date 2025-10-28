#pragma once

template <typename T> class Array
{
protected:
	T* internal;
	unsigned int size;

public:
	Array(unsigned int size) : size(size)
	{
		internal = new T[size] {};
	}

	Array(T* items, unsigned int size) : size(size)
	{
		internal = items;
	}

	~Array()
	{
		delete[] internal;
	}

	unsigned int GetSize()
	{
		return size;
	}

	T& operator[](unsigned int i)
	{
		return internal[i];
	}

	T& operator[](unsigned int i) const
	{
		return internal[i];
	}

	T* begin()
	{
		return internal;
	}

	T* end()
	{
		return internal + size;
	}
};