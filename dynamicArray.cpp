#pragma once
#include "array.cpp"
#include <cstring>

#define internal Array<T*>::internal
#define size Array<T*>::size

template <typename T> class DynamicArray : public Array<T*>
{
	unsigned int firstGap;

	void Reallocate(unsigned int newSize)
	{
		T** temp = internal;
		internal = new T * [newSize];
		std::memcpy(internal, temp, size);
		size = newSize;
		delete[] temp;
	}

	void Reallocate()
	{
		Reallocate(size << 1);
	}

public:
	DynamicArray(unsigned int Size) : Array<T*>(Size)
	{
		firstGap = 0;
	}

	DynamicArray() : DynamicArray(8)
	{
	}

	bool Add(T* item)
	{
		if (firstGap > size)
			Reallocate();
		internal[firstGap] = item;
		while (++firstGap < size && internal[firstGap] != nullptr)
		{

		}
	}

	void Set(unsigned int i, T* item)
	{
		if (item == nullptr)
			return Remove(i);

		if (i < size)
		{
			if (internal[i] == nullptr)
			{
				internal[i] = item;
				if (i == firstGap)
				{
					while (++firstGap < size && internal[firstGap] != nullptr)
					{
					}
				}
			}
			else
			{
				internal[i] = item;
			}
		}
		else
		{
			unsigned int newSize = size << 1;
			while (newSize < i)
			{
				newSize <<= 1;
			}
			Reallocate(newSize);

			internal[i] = item;
			if (i == firstGap)
			{
				while (++firstGap < size && internal[firstGap] != nullptr)
				{
				}
			}
		}
	}

	bool RemoveAndFree(unsigned int i)
	{
		if (internal[i] != nullptr)
		{
			delete internal[i];
			internal[i] = nullptr;
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
		if (internal[i] != nullptr)
		{
			internal[i] = nullptr;
			if (firstGap > i)
				firstGap = i;
			return true;
		}
		else
		{
			return false;
		}
	}

	T*& operator[](unsigned int i) = delete;
};

#undef internal
#undef size