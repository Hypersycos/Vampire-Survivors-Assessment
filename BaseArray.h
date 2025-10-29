#pragma once

template <typename T> class BaseArray
{
protected:
	T* internal;
	unsigned int size;

public:
	BaseArray(unsigned int size) : size(size)
	{
		internal = new T[size]{};
	}

	BaseArray(T* items, unsigned int size) : size(size)
	{
		internal = items;
	}

	BaseArray(const BaseArray& obj)
	{
		size = obj.size;
		internal = new T[size]();
		memcpy(internal, obj.internal, size * sizeof(T));
	}

	BaseArray(BaseArray&& obj) noexcept
	{
		size = obj.size;
		internal = obj.internal;
		
		obj.internal = nullptr;
	}

	BaseArray& operator=(const BaseArray& other)
	{
		if (this != &other)
		{
			unsigned int newSize = other.size;
			T* newArr = new T[newSize]();
			memcpy(internal, other->internal, newSize * sizeof(T));

			delete[] internal;
			size = newSize;
			internal = newArr;
		}
		return this;
	}

	BaseArray& operator=(BaseArray&& obj) noexcept
	{
		size = obj->size;
		internal = obj->internal;

		obj->internal = nullptr;
		return this;
	}

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

	T* begin()
	{
		return internal;
	}

	T* end()
	{
		return internal + size;
	}
};