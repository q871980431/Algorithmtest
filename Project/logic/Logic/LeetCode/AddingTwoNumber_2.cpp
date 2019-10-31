/*
 * File:	LeetCode.cpp
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */
#include "AddingTwoNumber_2.h"
namespace leetcode
{
	AddingTwoNumber * AddingTwoNumber::s_self = nullptr;

	LeetCodeRegister<AddingTwoNumber> addingTwoNumbertest;

	void AddingTwoNumber::StartTest(core::IKernel *kernel)
	{
		TRACE_LOG("This Start Test");
		Test(0, 619);
		int test3 = TestFun3(99, 9);
		ASSERT(test3 == 801, "error");
	}

	int AddingTwoNumber::Test(int A, int B)
	{
		ListNode *lA = CreateListNode(A);
		ListNode *lB = CreateListNode(B);
		Print(lA);
		Print(lB);
		ListNode *lC = addTwoNumbers(lA, lB);
		Print(lC);
		int C = GetListNum(lC);
		ListNode *lD = AddTwoNumbersFun2(lA, lB);
		int D = GetListNum(lD);
		return D;
	}

	int AddingTwoNumber::TestFun3(int A, int B)
	{
		ListNode *lA = CreateListNode(A);
		ListNode *lB = CreateListNode(B);
		ListNode *lD = AddTwoNumbersFun4(lA, lB);
		int D = GetListNum(lD);
		return D;
	}

	void AddingTwoNumber::Print(ListNode *list)
	{
		ListNode *tmp = list;
		while (tmp != nullptr)
		{
			ECHO("%d->", tmp->val);
			tmp = tmp->next;
		}
	}

	ListNode* AddingTwoNumber::addTwoNumbers(ListNode* l1, ListNode* l2)
	{

		int lA = GetListNum(l1);
		int lB = GetListNum(l2);
		return CreateListNode(lA + lB);
	}

	int AddingTwoNumber::GetListNum(ListNode *node)
	{
		int ret = 0;
		ListNode *temp = node;
		while (temp)
		{
			ret *= 10;
			ret += temp->val;
			temp = temp->next;
		}
		return ret;
	}

	ListNode * AddingTwoNumber::CreateListNode(int val)
	{
		int temp = val;
		ListNode *head = nullptr;
		ListNode *tail = nullptr;
		if (temp == 0)
		{
			ListNode *nowNode = (ListNode *)malloc(sizeof(ListNode));
			nowNode->val = 0;
			nowNode->next = nullptr;
			return nowNode;
		}
		while (temp > 0)
		{
			int now = temp % 10;
			ListNode *nowNode = (ListNode *)malloc(sizeof(ListNode));
			nowNode->val = now;
			nowNode->next = nullptr;
			if (head == nullptr)
			{
				head = nowNode;
				tail = nowNode;
			}
			else
			{
				tail->next = nowNode;
				tail = nowNode;
			}
			temp = temp / 10;
		}
		return  head;
	}

	ListNode * AddingTwoNumber::AddTwoNumbersFun2(ListNode *l1, ListNode *l2)
	{
		ListNode *tempL = l1;
		ListNode *tempR = l2;
		int tempA = 0;
		ListNode *freeHead = nullptr;
		ListNode *swap = nullptr;
		ListNode *ret = nullptr;
		ListNode *retTail = nullptr;
		while (tempL && tempR)
		{
			tempA += tempL->val;
			tempA += tempR->val;
			if (freeHead == nullptr)
			{
				freeHead = tempR;
				tempR = tempR->next;
			}
			else
			{
				swap = tempR;
				tempR = tempR->next;
				swap->next = freeHead;
				freeHead = swap;
			}
			swap = tempL;
			tempL = tempL->next;
			swap->next = freeHead;
			freeHead = swap;

			freeHead->val = tempA % 10;
			tempA = tempA / 10;

			if (ret == nullptr)
			{
				ret = freeHead;
				retTail = freeHead;
			}
			else
			{
				retTail->next = freeHead;
				retTail = freeHead;
			}
			freeHead = retTail->next;
			retTail->next = nullptr;
		}
		while (tempL)
		{
			if (tempA != 0)
			{
				tempL->val += tempA;
				tempA = tempL->val / 10;
				tempL->val = tempL->val % 10;
			}

			retTail->next = tempL;
			retTail = tempL;
			tempL = retTail->next;
			retTail->next = nullptr;
		}
		while (tempR)
		{
			if (tempA != 0)
			{
				tempR->val += tempA;
				tempA = tempR->val / 10;
				tempR->val = tempR->val % 10;
			}

			retTail->next = tempR;
			retTail = tempR;
			tempR= retTail->next;
			retTail->next = nullptr;
		}

		while (tempA > 0)
		{
			freeHead->val = tempA % 10;
			tempA = tempA / 10;

			retTail->next = freeHead;
			retTail = freeHead;
			freeHead = retTail->next;
			retTail->next = nullptr;
		}

		return ret;
	}

	ListNode * AddingTwoNumber::AddTwoNumbersFun3(ListNode *l1, ListNode *l2)
	{
		if (l2)
			l1->val += l2->val;
		l1->next = AddTwoNumbersFunInner(l1->next, l2->next, l1->val / 10, l2);
		l1->val %= 10;
		return l1;
	}

	ListNode * AddingTwoNumber::AddTwoNumbersFunInner(ListNode *l1, ListNode *l2, int carry, ListNode *feeHead)
	{
		if (l1 == nullptr && l2 == nullptr && carry == 0)
			return nullptr;

		ListNode *ret = feeHead;
		ListNode *nextL1 = nullptr;
		ListNode *nextL2 = nullptr;
		feeHead = feeHead->next;
		if (l1)
		{
			carry += l1->val;
			nextL1 = l1->next;
			l1->next = feeHead;
			feeHead = l1;
		}
		if (l2)
		{
			carry += l2->val;
			nextL2 = l2->next;
			l2->next = feeHead;
			feeHead = l2;
		}
		ret->val = carry % 10;

		ret->next = AddTwoNumbersFunInner(nextL1, nextL2, carry / 10, feeHead);
		return ret;
	}
	ListNode * AddingTwoNumber::AddTwoNumbersFunInner1(ListNode *l1, ListNode *l2, int carry, ListNode *feeHead)
	{
		if (l1 == nullptr && l2 == nullptr && carry == 0)
			return nullptr;

		ListNode *ret = feeHead;
		ListNode *nextL1 = nullptr;
		ListNode *nextL2 = nullptr;
		feeHead = feeHead->next;
		if (l1)
		{
			carry += l1->val;
			nextL1 = l1->next;
			l1->next = feeHead;
			feeHead = l1;
		}
		if (l2)
		{
			carry += l2->val;
			nextL2 = l2->next;
			l2->next = feeHead;
			feeHead = l2;
		}
		ret->val = carry % 10;

		ret->next = AddTwoNumbersFunInner(nextL1, nextL2, carry / 10, feeHead);
		return ret;
	}

	ListNode * AddingTwoNumber::AddTwoNumbersFun4(ListNode *l1, ListNode *l2)
	{
		if (l2)
			l1->val += l2->val;

		int carry = l1->val / 10;

		ListNode *nextL1 = l1->next;
		ListNode *nextL2 = l2->next;
		ListNode *freeHead = l2;
		ListNode *ret = nullptr;
		ListNode *temp = l1;

		while (nextL1 != nullptr || nextL2 != nullptr || carry != 0)
		{
			ret = freeHead;
			temp->next = ret;
			freeHead = freeHead->next;

			if (nextL1)
			{
				carry += nextL1->val;
				temp = nextL1;
				nextL1 = temp->next;
				temp->next = freeHead;
				freeHead = temp;
			}
			if (nextL2)
			{
				carry += nextL2->val;
				temp = nextL2;
				nextL2 = temp->next;
				temp->next = freeHead;
				freeHead = temp;
			}

			ret->val = carry % 10;
			carry /= 10;
			temp = ret;
		}

		temp->next = nullptr;
		l1->val %= 10;
		return l1;
	}
}
