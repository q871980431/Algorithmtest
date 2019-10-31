/*
 * File:	LeetCode.cpp
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */
#include "Lrucache.h"
#include "LeetCode.h"
namespace leetcode {
	LeetCodeRegister<Lrucache> lrucacheTest;

	void Lrucache::StartTest(core::IKernel *kernel)
	{
		_capacity = 2;
		_size = 0;
		put(1, 1);
		if (get(1) != 1)
		{
			ASSERT(false, "error");
		}
		put(2, 2);
		if (get(1) != 1)
		{
			ASSERT(false, "error");
		}
		put(1, 2);
		put(3, 3);
		if (get(2) != -1)
		{
			ASSERT(false, "error");
		}
		put(4, 4);
		if (get(1) != -1)
		{
			ASSERT(false, "error");
		}
		if (get(3) != 3)
		{
			ASSERT(false, "error");
		}
		if (get(4) != 4)
		{
			ASSERT(false, "error");
		}
		TRACE_LOG("OK");
	}

	s32 Lrucache::get(s32 key)
	{
		auto iter = _nodes.find(key);
		if (iter != _nodes.end())
		{
			_linkList.RemoveNode(iter->second);
			_linkList.InsertHead(iter->second);
			return iter->second->val;
		}
		return -1;
	}

	void Lrucache::put(s32 key, s32 value)
	{
		auto iter = _nodes.find(key);
		if (iter == _nodes.end())
		{
			Lrunode *node = nullptr;
			if (_size == _capacity)
			{
				node = (Lrunode *)_linkList.RemoveTail();
				if (node != nullptr )
				{
					node->val = value;
					_nodes.erase(node->key);
					node->key = key;
				}
			}
			else
			{
				node = new Lrunode();
				node->key = key;
				node->val = value;
				_size++;
			}
			_nodes.emplace(node->key, node);
			_linkList.InsertHead(node);
		}
		else
		{
			iter->second->val = value;
			_linkList.RemoveNode(iter->second);
			_linkList.InsertHead(iter->second);
		}
	}
}
