#pragma once

template <typename T> class Array
{
	T* internal;
	unsigned int size;

public:
	Array(int size) : size(size)
	{
		internal = new T*[size];
		for (int i = 0; i < size; i++)
		{
			internal[i] = default;
		}
	}

	~Array()
	{
		delete[] internal;
	}

	unsigned int GetSize()
	{
		return size;
	}

	T Free(int i)
	{
		if (internal[i] != nullptr)
		{
			delete internal[i];
		}
	}

	T& operator[](int i)
	{
		return internal[i];
	}

	T operator[](int i) const
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