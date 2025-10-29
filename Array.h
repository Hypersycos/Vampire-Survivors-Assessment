#pragma once
#include "BaseArray.h"

#define internal BaseArray<T>::internal
#define size BaseArray<T>::size

template <typename T> class Array : public BaseArray<T>
{
public:
	Array(unsigned int Size) : BaseArray<T>(Size)
	{
	}

	Array(T* items, unsigned int Size) : BaseArray<T>(items, Size)
	{
		internal = items;
	}

	T& operator[](unsigned int i)
	{
		return internal[i];
	}
};

#undef internal
#undef size