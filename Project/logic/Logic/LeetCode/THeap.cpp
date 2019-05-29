#include "THeap.h"

template<typename T>
void THeap<T>::FileterUp(s32 i)
{
	s32 currentPos, parentPos;
	T target;
	currentPos = i;
	parentPos = (i - 1) / 2;
	target = _items[i];
	while (currentPos != 0)
	{
		if (_items[parentPos] <= target)
			break;
		else
		{
			_items[currentPos] = _items[parentPos];
			currentPos = parentPos;
			parentPos = (currentPos - 1) / 2;
		}
	}
	if (i != currentPos)
		_items[currentPos] = target;
}

template<typename T>
void THeap<T>::FileterDown(s32 i)
{
	s32 currentPos, childPos;
	currentPos = i;
	childPos = currentPos * 2 + 1;
	T target = _items[i];
	while (childPos < _heapSize)
	{
		if ((childPos + 1 < _heapSize) && (_items[childPos + 1] < _items[childPos]))
			childPos = childPos + 1;
		if (target <= _items[childPos])
			break;
		else
		{
			_items[currentPos] = _items[childPos];
			currentPos = childPos;
			childPos = currentPos * 2 + 1;
		}
	}
	if (i != currentPos)
		_items[currentPos] = target;
}

template< typename T>
void THeap<T>::HeapFromat()
{
	s32 parentPos = _size - 2 / 2;
	while (parentPos >= 0)
	{
		FileterDown(parentPos);
		parentPos--;
	}
}

template<typename T>
void THeap<T>::HeapSort()
{
	T del;
	while (Delete(del))
	{
		_items[_heapSize] = del;
	}
}