#pragma once
#include "BaseArray.h"
#include <cstring>

template <typename T> class DynamicArray : public BaseArray<T>
{
	unsigned int firstFree{ 0 };

	void Reallocate(unsigned int s)
	{ //copies current array contents into new array of size s
		T* newArr = new T[s];
		std::memcpy(newArr, this->internal, this->size * sizeof(T));
		delete[] this->internal;
		this->internal = newArr;
		this->size = s;
	}

	void Reallocate()
	{ //default reallocate doubles in size
		Reallocate(this->size << 1);
	}

public:
	DynamicArray(unsigned int size) : BaseArray<T>(size)
	{
	}

	DynamicArray() : DynamicArray(8)
	{
	}

	void Add(T item)
	{
		if (firstFree >= this->size)
			Reallocate();
		this->internal[firstFree++] = item;
	}

	bool Set(unsigned int i, T item)
	{
		//Set allows assignment with better guarantees than operator[]
		if (item == nullptr)
			return Remove(i);

		if (i >= this->firstFree)
			return false;
		else if (i == firstFree)
			Add(item);
		else
			this->internal[i] = item;
		return true;
	}

	bool Remove(unsigned int i)
	{
		if (i >= firstFree)
			return false;
		for (int j = i; j < firstFree - 1; j++)
		{
			this->internal[j] = this->internal[j + 1];
		}
		firstFree--;
		return true;
	}

	bool Remove(T instance)
	{
		for (unsigned int i = 0; i < firstFree; i++)
		{
			if (this->internal[i] == instance)
				return Remove(i);
		}
		return false;
	}

	unsigned int GetCurrentSize() const
	{
		return firstFree;
	}

	T* begin() override
	{
		return this->internal;
	}

	T* end() override
	{
		return this->internal + firstFree;
	}
};