/*
 * File:	LeetCode.h
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#ifndef __AddingTwoNumber_h__
#define __AddingTwoNumber_h__
#include "LeetCode.h"
namespace leetcode
{
	struct ListNode {
		int val;
		ListNode *next;
		ListNode(int x) : val(x), next(nullptr) {}
	};
	class AddingTwoNumber  : public ILeetCodeTest
	{
	public:
		virtual ~AddingTwoNumber() {};

		virtual void StartTest(core::IKernel *kernel);
		int Test(int A, int B);
		int TestFun3(int A, int B);
		void Print(ListNode *list);

	protected:
		int GetListNum(ListNode *node);
		ListNode * CreateListNode(int val);
		ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

	private:
		ListNode * AddTwoNumbersFun2(ListNode *l1, ListNode *l2);
		ListNode * AddTwoNumbersFun3(ListNode *l1, ListNode *l2);
		ListNode * AddTwoNumbersFunInner(ListNode *l1, ListNode *l2, int carry, ListNode *feeHead);
		ListNode * AddTwoNumbersFunInner1(ListNode *l1, ListNode *l2, int carry, ListNode *feeHead);
		ListNode * AddTwoNumbersFun4(ListNode *l1, ListNode *l2);

	private:
		static AddingTwoNumber     * s_self;
	};
}
#endif