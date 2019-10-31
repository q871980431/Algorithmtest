#include "TreeNode.h"
#include "LeetCode.h"
#include "THeap.h"
#include <functional>
namespace leetcode {

	LeetCodeRegister<TreeNodeTest> treeNodeTest;
	void VistNode(s32 &val)
	{
		printf("%d  ", val);
	}
	void TreeNodeTest::StartTest(core::IKernel *kernel)
	{
		TestSort(kernel);
		TreeNode<s32> *root = nullptr;
		MakeTreeNode(root, 3);
		PrintTree(root, 0);
		TreeNode<s32> *copyTree = CopyTree(root);
		PrintTree(copyTree, 0);
		s32 deep = GetDeep(copyTree);
		printf("Deep:%d\n", deep);
		LevelScan(copyTree, VistNode);
		s32 id1[] = { 4,3,5,8,15,7,6, 8, 35 };
		auto f = [](s32 *id, s32 size)
		{
			for (s32 i = 0; i < size; i++)
			{
				printf("id[%d]= %d", i, id[i]);
			}
		};
		QuckSort(id1, 9);
		THeap<s32> heap(id1, 6, 6);
		f(id1, 6);
		heap.HeapSort();
		f(id1, 6);
	}

	void TreeNodeTest::TestSort(core::IKernel *kernel)
	{
		struct TestNode 
		{
			s32 id;
			bool operator < (const TestNode &right)
			{
				return this->id > right.id;
			}
		};

		auto f = [](TestNode *node, s32 size)
		{
			for (s32 i = 0; i < size; i++)
			{
				printf("id[%d]= %d", i, node[i].id);
			}
		};
		TestNode node[] = { 4,3,5,8,15,7,6, 8, 35 };
		QuckSort(node, 9);
		f(node, 9);
		printf("\nsucess\n");
	}

	void TreeNodeTest::IndentBlanks(s32 num)
	{
		for (s32 i = 0; i < num; i++)
			printf("%s", " ");
	}
}