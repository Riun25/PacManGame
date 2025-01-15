#pragma once
#include <iostream>

// @refactor : ��� �Ϻη� ���� ���ױ� ������ ������ �ȴٸ� ���ľ� ��
#pragma warning (disable : 4251)

template <typename T>
class List
{
public:
	List()
		:mCapacity(2)
	{
		mData = new T[mCapacity];
		memset(mData, 0, sizeof(T) * mCapacity);
	}

	~List()
	{
		if (mData != nullptr)
		{
			delete[] mData;
		}
	}

	void PushBack(const T& value)
	{
		if (mSize == mCapacity)
		{
			ReAllocate(mCapacity * 2);
		}

		mData[mSize] = value;
		mSize++;
	}

	void PushBack(T&& value)
	{
		if (mSize == mCapacity)
		{
			ReAllocate(mCapacity * 2);
		}

		mData[mSize] = std::move(value);
		mSize++;
	}

	void Erase(int _idx)
	{
		// ���� ó��
		if (_idx < 0 || _idx >= mSize)
		{
			__debugbreak();
		}

		// ������ �������� �ε��� ���� ��ġ�� �� ĭ ������ ��� �̵�
		for (int idx = _idx; idx < mSize - 1; idx++)
		{
			mData[idx] = std::move(mData[idx + 1]);
		}

		// ���� �� ũ�� ���̱�
		--mSize;
	}

	int Size() const
	{
		return mSize;
	}

	int Capacity() const
	{
		return mCapacity;
	}

	const T& operator[](int index) const
	{
		if (index >= mSize)
		{
			__debugbreak();
		}

		return mData[index];
	}

	T& operator[](int index)
	{
		if (index >= mSize)
		{
			__debugbreak();
		}

		return mData[index];
	}

	T* begin() const
	{
		return mData;
	}

	T* end() const
	{
		return mData + mSize;
	}
private:
	void ReAllocate(int newCapacity)
	{
		// 1. allocate a new block of memory.
		// 2. copy/move old elements into new block.
		// 3. delete.

		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		if (newCapacity < mSize)
		{
			mSize = newCapacity;
		}

		memcpy(newBlock, mData, sizeof(T) * mCapacity);
		//for (int ix = 0; ix < size; ++ix)
		//{
		//    // newBlock[ix] = data[ix];
		//    newBlock[ix] = std::move(data[ix]);
		//}

		delete[] mData;
		mData = newBlock;
		mCapacity = newCapacity;
	}

private:
	T* mData = nullptr;
	int mSize = 0;
	int mCapacity = 0;
};