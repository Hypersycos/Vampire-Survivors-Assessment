#pragma once
#include "Array.h"

template <typename T, int N> class FixedArray : public Array<T>
{
public:
	FixedArray() : Array<T>(N)
	{
	}

	FixedArray(T* items) : Array<T>(items, N)
	{
	}
};