#ifndef __THeap_h__
#define __THeap_h__
#include "MultiSys.h"
template<typename T>
class THeap
{
public:
	THeap(s32 size) {
		_size = size;
		_items = NEW T[_size]();
		_heapSize = 0;
		_new = true;
	};

	THeap(T *items, s32 size) :_items(items), _size(size), _heapSize(size), _new(false)
	{
		HeapFromat();
	}

	~THeap() 
	{
		if (_new)
		{
			DEL[] _items;
		}
	}

	bool Insert(T &item)
	{
		if (_heapSize == _size)
			return false;
		_items[_heapSize] = item;
		FileterUp(_heapSize);
		_heapSize++;
		return true;
	}

	bool Delete(T &item)
	{
		if (_heapSize == 0)
			return false;
		item = _items[0];
		_items[0] = _items[_heapSize - 1];
		FileterDown(0);
		_heapSize--;
		return true;
	}

	const T * GetHeap(s32 &size) { size = _heapSize; return _items; };
	void HeapSort() {
		T del;
		s32 size = _heapSize;
		while (Delete(del))
		{
			_items[_heapSize] = del;
		}
		_heapSize = size;
	};

private:
	void FileterUp(s32 i) 
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

	void FileterDown(s32 i)
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

	void HeapFromat()
	{
		s32 parentPos = _size - 2 / 2;
		while (parentPos >= 0)
		{
			FileterDown(parentPos);
			parentPos--;
		}
	}
private:
	s32 _size;
	T *	_items;
	s32 _heapSize;
	bool _new;
};

#endif
