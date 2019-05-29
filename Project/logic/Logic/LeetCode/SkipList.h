/*
 * File:	LeetCode.h
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#ifndef __SkipList_h__
#define __SkipList_h__

#include "ILeetCode.h"
#include <vector>
#include <unordered_map>

namespace leetcode
{
	class IRankNode;
	struct RankLevel 
	{
		IRankNode *_next;
		u16 span;
	};

	class IRankNode
	{
	public:
		s32 _score;
		IRankNode *_pre;
		RankLevel *_level;
		s32 _id;
	};
		
	class IRankList
	{
	public:
		const static s32 RANK_MAX_LEVEL = 32;
		const static  u32 SKIPLIST_P = (0.25 * 0xFFFF);

		IRankList(s32 level = RANK_MAX_LEVEL);
		~IRankList() { Clean(); };

		IRankNode * Insert(s32 score, s32 id);
		bool		Delete(s32 score, s32 id);
		IRankNode * GetRankNodeByRank(u32 rank);
		s32			GetRank(s32 score, s32 id);
		void		Printf();
	protected:

	private:
		IRankNode * CreateNode(s32 level, s32 score);
		void Clean();
		void ReleaseNode(IRankNode *node);
		s32 RandomLevel();
		void DeleteNode(IRankNode *x, IRankNode **update);

	private:
		IRankNode *_header;
		IRankNode *_tail;
		s32	_length;
		s32	_level;
		s32 _maxLevel;
	};

	class SkipListTest : public ILeetCodeTest
	{
	public:
		SkipListTest() {};

		virtual void StartTest(core::IKernel *kernel);
	protected:
	private:
	};

}

#endif