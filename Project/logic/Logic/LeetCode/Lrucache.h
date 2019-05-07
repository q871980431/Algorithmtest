/*
 * File:	LeetCode.h
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#ifndef __Lrucache_h__
#define __Lrucache_h__
#include "ILeetCode.h"
#include <vector>
#include <unordered_map>

namespace leetcode
{
	class ILinkNode 
	{
	public:
		ILinkNode() :_pre(nullptr), _next(nullptr) {};

		ILinkNode *_pre;
		ILinkNode *_next;
	};

	class ILinkList
	{
	public:
		ILinkList() :_head(nullptr), _tail(nullptr){}

		bool InsertHead(ILinkNode *node)
		{
			node->_next = _head;
			if (_head == nullptr)
			{
				_tail = node;
				_tail->_next = nullptr;
			}
			else
				_head->_pre = node;
			_head = node;
			_head->_pre = nullptr;
			return true;
		}

		void RemoveNode(ILinkNode *node)
		{
			if (node->_pre)
				node->_pre->_next = node->_next;
			if (node->_next)
				node->_next->_pre = node->_pre;
			if (node == _head)
				_head = node->_next;
			if (node == _tail)
				_tail = node->_pre;
		}

		ILinkNode * RemoveTail()
		{
			if (_tail != nullptr)
			{
				ILinkNode *tmp = _tail;
				_tail = _tail->_pre;
				if (_tail == nullptr)
					_head = nullptr;
				else
					_tail->_next = nullptr;
				return tmp;
			}

			return nullptr;
		}
	protected:
	private:
		ILinkNode *_head;
		ILinkNode *_tail;
	};

	class Lrunode : public ILinkNode
	{
	public:
		s32 key;
		s32 val;
	};

	class Lrucache : public ILeetCodeTest
	{
	public:
		Lrucache() {};
		virtual ~Lrucache() {};

		virtual void StartTest(core::IKernel *kernel);

	protected:
	private:
		s32 get(s32 key);
		void put(s32 key, s32 value);
	private:
		ILinkList _linkList;
		s32 _capacity;
		std::unordered_map<s32, Lrunode *> _nodes;
		s32 _size;
	};
}

#endif