#pragma once

namespace Containers
{
	template <typename T>
	class SmartArray
	{

	public:
		SmartArray();
		~SmartArray();

		void addAtEnd(T data);
		void addAtIndex(unsigned int index, T data);
		void removeAt(unsigned int index);
		T getAt(unsigned int index);
		unsigned int getSize();
		void clear();
		bool isEmpty();

	private:

		void Grow();

		const unsigned int mInitialSize = 10;

		unsigned int mCapacity = 0;

		//Also the index to add next
		unsigned int mSize = 0;

		T* mData = nullptr;

	};

	template<typename T>
	inline SmartArray<T>::SmartArray()
	{
		mData = new T[mInitialSize];
		mCapacity = mInitialSize;
	}

	template<typename T>
	inline SmartArray<T>::~SmartArray()
	{
		delete[] mData;
	}

	template<typename T>
	inline void SmartArray<T>::addAtEnd(T data)
	{
		if ((mSize + 1) > mCapacity) { Grow(); }

		mData[mSize] = data;
		mSize++;
	}

	template<typename T>
	inline void SmartArray<T>::addAtIndex(unsigned int index, T data)
	{
		if (index >= mSize) { __debugbreak(); }

		mData[index] = data;
	}

	template<typename T>
	inline void SmartArray<T>::removeAt(unsigned int index)
	{
		if (index >= mSize) { return; }

		for (unsigned int i = index; i < mSize - 1; i++)
		{
			mData[i] = mData[i + 1];
		}

		--mSize;
	}

	template<typename T>
	inline T SmartArray<T>::getAt(unsigned int index)
	{
		return mData[index];
	}

	template<typename T>
	inline unsigned int SmartArray<T>::getSize()
	{
		return mSize;
	}

	template<typename T>
	inline void SmartArray<T>::clear()
	{
		delete[] mData;
		mSize = 0;
		mCapacity = mInitialSize;
	}

	template<typename T>
	inline bool SmartArray<T>::isEmpty()
	{
		return mSize == 0;
	}

	template<typename T>
	inline void SmartArray<T>::Grow()
	{
		unsigned int newSize = mCapacity + (mCapacity / 4);

		T* newData = new T[newSize];

		for (int i = 0; i < mCapacity; i++)
		{
			newData[i] = mData[i];
		}

		delete[] mData;

		mData = newData;
		mCapacity = newSize;
	}
}
