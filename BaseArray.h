#pragma once

template <typename T> class BaseArray
{
protected:
	T* internal;
	unsigned int size;

public:
	BaseArray(unsigned int size) : size(size)
	{
		internal = new T[size];
	}

	BaseArray(T* items, unsigned int size) : size(size)
	{
		internal = items;
	}

	BaseArray(const BaseArray&) = delete;
	BaseArray& operator= (const BaseArray&) = delete;

	~BaseArray()
	{
		if (internal != nullptr)
			delete[] internal;
	}

	unsigned int GetSize()
	{
		return size;
	}

	T& operator[](unsigned int i) const
	{
		return internal[i];
	}

	virtual T* begin()
	{
		return internal;
	}

	virtual T* end()
	{
		return internal + size;
	}
};