#pragma once
#include "BaseArray.h"
#include <cstring>

template <typename T> class DynamicArray : public BaseArray<T*>
{
	unsigned int firstGap;

	void Reallocate(unsigned int size)
	{
		T** temp = BaseArray<T*>::internal;
		BaseArray<T*>::internal = new T* [size];
		std::memcpy(BaseArray<T*>::internal, temp, size);
		BaseArray<T*>::size = size;
		delete[] temp;
	}

	void Reallocate()
	{
		Reallocate(BaseArray<T*>::size << 1);
	}

public:
	DynamicArray(unsigned int size) : BaseArray<T*>(size)
	{
		firstGap = 0;
	}

	DynamicArray() : DynamicArray(8)
	{
	}

	DynamicArray(const DynamicArray& obj) : BaseArray<T*>(obj)
	{
		firstGap = obj.firstGap;
	}

	DynamicArray(DynamicArray&& obj) noexcept : BaseArray<T*>(obj)
	{
		firstGap = obj.firstGap;
	}

	DynamicArray& operator=(const DynamicArray& other)
	{
		DynamicArray& temp = BaseArray<T*>::operator=(other);
		temp.firstGap = other.firstGap;
	}

	DynamicArray& operator=(DynamicArray&& other) noexcept
	{
		DynamicArray& temp = BaseArray<T*>::operator=(other);
		temp.firstGap = other.firstGap;
	}

	bool Add(T* item)
	{
		if (firstGap > BaseArray<T*>::size)
			Reallocate();
		BaseArray<T*>::internal[firstGap] = item;
		while (++firstGap < BaseArray<T*>::size && BaseArray<T*>::internal[firstGap] != nullptr)
		{

		}
	}

	void Set(unsigned int i, T* item)
	{
		if (item == nullptr)
			return Remove(i);

		if (i < BaseArray<T*>::size)
		{
			if (BaseArray<T*>::internal[i] == nullptr)
			{
				BaseArray<T*>::internal[i] = item;
				if (i == firstGap)
				{
					while (++firstGap < BaseArray<T*>::size && BaseArray<T*>::internal[firstGap] != nullptr)
					{
					}
				}
			}
			else
			{
				BaseArray<T*>::internal[i] = item;
			}
		}
		else
		{
			unsigned int newSize = BaseArray<T*>::size << 1;
			while (newSize < i)
			{
				newSize <<= 1;
			}
			Reallocate(newSize);

			BaseArray<T*>::internal[i] = item;
			if (i == firstGap)
			{
				while (++firstGap < BaseArray<T*>::size && BaseArray<T*>::internal[firstGap] != nullptr)
				{
				}
			}
		}
	}

	bool RemoveAndFree(unsigned int i)
	{
		if (BaseArray<T*>::internal[i] != nullptr)
		{
			delete BaseArray<T*>::internal[i];
			BaseArray<T*>::internal[i] = nullptr;
			if (firstGap > i)
				firstGap = i;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Remove(unsigned int i)
	{
		if (BaseArray<T*>::internal[i] != nullptr)
		{
			BaseArray<T*>::internal[i] = nullptr;
			if (firstGap > i)
				firstGap = i;
			return true;
		}
		else
		{
			return false;
		}
	}
};