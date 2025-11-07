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

	FixedArray(const std::initializer_list<T> items) : Array<T>(N)
	{
		int i = 0;
		for (T item : items)
		{
			Array<T>::internal[i] = item;
			if (i++ >= N)
				break;
		}
	}

	FixedArray(FixedArray& other) : Array<T>(N)
	{
		std::copy(other.begin(), other.end(), Array<T>::internal);
	}
};