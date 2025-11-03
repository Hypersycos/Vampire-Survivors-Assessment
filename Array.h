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
		BaseArray<T>::internal = items;
	}

	T& operator[](unsigned int i)
	{
		return BaseArray<T>::internal[i];
	}
};