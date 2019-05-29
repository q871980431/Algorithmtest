/*
 * File:	LeetCode.cpp
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */
#include "SkipList.h"
#include "LeetCode.h"
#include "Tools.h"
#include <set>
namespace leetcode {

	IRankList::IRankList(s32 level /* = RANK_LEVEL */)
	{
		_maxLevel = level > RANK_MAX_LEVEL ? RANK_MAX_LEVEL : level;
		_level = 1;
		_length = 0;
		_header = CreateNode(_maxLevel, 0);
		for (s32 i = 0; i < _maxLevel; i++)
		{
			_header->_level[i]._next = nullptr;
			_header->_level[i].span = 0;
		}
		_header->_pre = nullptr;
		_tail = nullptr;
	}

	IRankNode * IRankList::Insert(s32 score, s32 id)
	{
		IRankNode *update[RANK_MAX_LEVEL];
		u32 rank[RANK_MAX_LEVEL];
		IRankNode *x = _header;
		s32 i, level;
		for (i = _level-1; i >= 0; i--)
		{
			rank[i] = (i == (_level - 1)) ? 0 : rank[i + 1];
			while (x->_level[i]._next && 
				(x->_level[i]._next->_score < score || 
					(x->_level[i]._next->_score == score && x->_level[i]._next->_id < id)
					)
				)
			{
				rank[i] += x->_level[i].span;
				x = x->_level[i]._next;
			}
			update[i] = x;
		}

		level = RandomLevel();
		if (level > _level)
		{
			for (i = _level; i < level; i++)
			{
				rank[i] = 0;
				update[i] = _header;
				update[i]->_level[i].span = _length;
			}
			_level = level;
		}

		x = CreateNode(level, score);
		x->_id = id;
		for (i = 0; i < level; i++)
		{
			x->_level[i]._next = update[i]->_level[i]._next;
			update[i]->_level[i]._next = x;

			x->_level[i].span = update[i]->_level[i].span - (rank[0] - rank[i]);
			update[i]->_level[i].span = (rank[0] - rank[i]) + 1;
		}

		for (i = level; i < _level; i++)
		{
			update[i]->_level[i].span++;
		}

		x->_pre = (update[0] == _header) ? nullptr : update[0];
		if (x->_level[0]._next)
			x->_level[0]._next->_pre = x;
		else
			_tail = x;

		_length++;
		return x;
	}

	bool IRankList::Delete(s32 score, s32 id)
	{
		IRankNode *update[RANK_MAX_LEVEL];
		IRankNode *x = _header;
		s32 i = 0;
		for (i = _level - 1; i >= 0; i--)
		{
			while (x->_level[i]._next &&
				(x->_level[i]._next->_score < score ||
				(x->_level[i]._next->_score == score && x->_level[i]._next->_id < id)
					)
				)
				x = x->_level[i]._next;
			update[i] = x;
		}
		x = x->_level[0]._next;	
		if (x && score == x->_score && id == x->_id)
		{
			DeleteNode(x, update);
			return true;
		}
		return false;
	}

	IRankNode * IRankList::GetRankNodeByRank(u32 rank)
	{
		IRankNode *x = _header;
		u32 traversed = 0;
		s32 i = 0;
		for ( i = _level - 1; i >= 0; i--)
		{
			while (x->_level[i]._next && traversed + x->_level[i].span <= rank)
			{
				traversed += x->_level[i].span;
				x = x->_level[i]._next;
			}
			if (traversed == rank)
				return x;
		}

		return nullptr;
	}

	s32 IRankList::GetRank(s32 score, s32 id)
	{
		IRankNode *x = _header;
		u32 rank[RANK_MAX_LEVEL];
		s32 i = 0;
		for (i = _level -1; i >= 0; i--)
		{
			rank[i] = (i == _level - 1) ? 0 : rank[i + 1];
			while (x->_level[i]._next && x->_level[i]._next->_score <= score)
			{
				rank[i] += x->_level[i].span;
				if (x->_level[i]._next->_score == score && x->_level[i]._next->_id == id)
					return rank[i];

				x = x->_level[i]._next;
			}
		}

		return 0;
	}

	void IRankList::Printf()
	{
		ECHO("-------Printf----------");
		s32 i = 0;
		for ( i = _level - 1; i >= 0; i--)
		{
			ECHO("Level = %d *******, Head Span:%d", i, _header->_level[i].span);
			IRankNode * x = _header;
			while (x->_level[i]._next)
			{
				ECHO("Node[%d], score:%d, span:%d", x->_level[i]._next->_id, x->_level[i]._next->_score, x->_level[i]._next->_level[i].span);
				x = x->_level[i]._next;
			}
		}
	}

	IRankNode * IRankList::CreateNode(s32 level, s32 score)
	{
		IRankNode *node = NEW IRankNode();
		node->_level = (RankLevel *)malloc(sizeof(RankLevel) * level);
		tools::SafeMemset(node->_level, sizeof(RankLevel) * level, 0, sizeof(RankLevel) * level);
		node->_score = score;
		return node;
	}

	void IRankList::Clean()
	{
		if (_header)
		{
			IRankNode *node = _header->_level[0]._next;
			IRankNode *next;
			ReleaseNode(_header);
			_header = nullptr;
			while (node)
			{
				next = node->_level[0]._next;
				ReleaseNode(node);
				node = next;
			}
		}
	}

	void IRankList::ReleaseNode(IRankNode *node)
	{
		free(node->_level);
		DEL node;
	}

	s32 IRankList::RandomLevel()
	{
		s32 level = 1;
		while ((tools::Random() & 0xFFFF) < SKIPLIST_P)
			level++;
		return level < _maxLevel ? level : _maxLevel;
	}

	void IRankList::DeleteNode(IRankNode *x, IRankNode **update)
	{
		s32 i = 0;
		for (i = 0; i < _level; i++)
		{
			if (update[i]->_level[i]._next == x)
			{
				update[i]->_level[i].span += x->_level[i].span - 1;
				update[i]->_level[i]._next = x->_level[i]._next;
			}
			else
			{
				update[i]->_level[i].span -= 1;
			}
		}
		
		if (x->_level[0]._next)
			x->_level[0]._next->_pre = x->_pre;
		else
			_tail = x->_pre;

		while (_level > 1 && _header->_level[_level - 1]._next == nullptr)
			_level--;

		_length--;
	}

	LeetCodeRegister<SkipListTest> test;
	void SkipListTest::StartTest(core::IKernel *kernel)
	{
		IRankList rankList;
		for (s32 i = 0; i < 10; i++)
		{
			rankList.Insert(i, i);
		}
		rankList.Insert(3, 4);
		rankList.Printf();
		IRankNode *node = rankList.GetRankNodeByRank(1);
		std::set<s32> ids;
		s32 i = 0;
		while (node&& i < 3)
		{
			ids.insert(node->_id);
			node = node->_level->_next;
			i++;
		}

		rankList.Delete(3, 3);
		rankList.Printf();
		s32 rank = rankList.GetRank(3, 4);
		rankList.Delete(3, 4);
		s32 rank2 = rankList.GetRank(3, 4);
		rankList.Printf();
	}
}
