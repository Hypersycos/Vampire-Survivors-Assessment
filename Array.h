#pragma once
#include "BaseArray.h"

template <typename T> class Array : public BaseArray<T>
{
public:
	Array(unsigned int Size) : BaseArray<T>(Size)
	{
	}

	Array(T* items, unsigned int Size) : BaseArray<T>(items, Size)
	{
	}

	Array(const std::initializer_list<T> items) : BaseArray<T>(items)
	{

	}

	T& operator[](unsigned int i)
	{ //allows assignment
		return BaseArray<T>::internal[i];
	}
};