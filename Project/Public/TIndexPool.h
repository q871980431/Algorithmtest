#ifndef __T_IndexPool_h__
#define __T_IndexPool_h__
#include "MultiSys.h"
#include "THeap.h"
namespace tlib
{

	class IndexNode
	{
	public:
		inline s32 GetIndex() { return _index; };
		inline void SetIndex(s32 index) { _index = index; };
	private:
		s32 _index{-1};
	};

	template<typename T, s32 InitSize=1024>
	class IndexPool
	{
		
		struct Block 
		{
			//Chunk[]
		};
		struct Chunk 
		{
			s32 mark;
			s8 buff[sizeof(T)];
			Block *parent;
		};
	public:
		IndexPool(){
			InitHeapCapacity(InitSize);
		}

		~IndexPool()
		{
			for (auto &node : _nodes)
				free(node);
			DEL _indexHeap;
		}
	
		template<typename ...Args>
		T * Create(Args... args)
		{
			s32 index = 0;
			if (!_indexHeap->Delete(index))
			{
				s32 capacity = _indexHeap->GetCapacity();
				ExpandCapacity(capacity + InitSize);
				if (!_indexHeap->Delete(index))
					return nullptr;
			}
			ASSERT(_nodes[index] != nullptr, "error");
			T *ret = new(_nodes[index]) T(args...);
			ret->SetIndex(index);
			return ret;
		}

		T * Find(s32 index)
		{
			if (index < 0 || index >(s32)_nodes.size())
				return nullptr;
			return (T*)_nodes[index];
		}

		void Recover(T *t)
		{
			s32 index = t->GetIndex();
			t->~T();
			_indexHeap->Insert(index);
		}

	private:
		void ExpandCapacity(s32 expaCount)
		{
			s32 oldSize = _nodes.size();
			if (expaCount > _indexHeap->GetCapacity())
			{
				s32 tmp = ((expaCount % InitSize) == 0) ? 0 : 1;
				expaCount = ((expaCount / InitSize) + tmp) * InitSize;
				HeapExpaCapacity(expaCount);
			}
			s32 add = expaCount - oldSize;
			for (s32 i = 0; i < add; i++)
			{
				T *temp = (T*)malloc(sizeof(T));
				if (temp != nullptr)
				{
					_nodes[oldSize] = temp;
					_indexHeap->Insert(oldSize);
					oldSize++;
				}
			}
		}

		void HeapExpaCapacity(s32 expaCount)
		{
			s32 capacity = _indexHeap->GetCapacity();
			s32 add = expaCount - capacity;
			for (s32 i = 0; i < add; i++)
				_nodes.push_back(nullptr);

			THeap<s32> *tempHeap = NEW THeap<s32>(expaCount);
			s32 unuseIndex;
			while (_indexHeap->Delete(unuseIndex))
				tempHeap->Insert(unuseIndex);
			DEL _indexHeap;
			_indexHeap = tempHeap;
		}

		void InitHeapCapacity(s32 capacity)
		{
			_indexHeap = NEW THeap<s32>(capacity);
			for (s32 i = 0; i < capacity; i++)
			{
				T *temp = (T*)malloc(sizeof(T));
				if (temp != nullptr)
				{
					_nodes.push_back(temp);
					_indexHeap->Insert(i);
				}
			}
		}

	private:
		std::vector<T*>	_nodes;
		THeap<s32>	*_indexHeap;
	};
}
#endif