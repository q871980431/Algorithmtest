#ifndef __TreeNode_h__
#define __TreeNode_h__
#include "ILeetCode.h"
#include "Tools.h"
#include <list>
namespace leetcode
{

	template<typename T>
	class TreeNode
	{
	public:
		T _data;

		TreeNode(T&item, TreeNode* left, TreeNode *right) :_data(item), _left(left), _right(right) {};
		inline TreeNode * Left()const { return _left; };
		inline TreeNode * Right()const { return _right; };
	private:
		TreeNode *_left;
		TreeNode *_right;
	};


	class TreeNodeTest : public ILeetCodeTest
	{
	public:
		TreeNodeTest() {};
		virtual ~TreeNodeTest(){}

		virtual void StartTest(core::IKernel *kernel);
	private:
		void TestSort(core::IKernel *kernel);
	protected:
	private:
		void MakeTreeNode(TreeNode<s32> * &root, s32 level)
		{
			if (level > 0)
			{
				TreeNode<s32> *left = nullptr;
				MakeTreeNode(left, level - 1);
				TreeNode<s32> *right = nullptr;
				MakeTreeNode(right, level - 1);
				s32 item = tools::Random() / 10;
				root = NEW TreeNode<s32>(item, left, right);
			}
		}

		template <class T>
		TreeNode<T> * CopyTree(TreeNode<T> *tree)
		{
			if (tree == nullptr)
				return nullptr;
			return NEW TreeNode<T>(tree->_data, CopyTree(tree->Left()), CopyTree(tree->Right()));
		}

		template <class T>
		s32 GetDeep(TreeNode<T> *node)
		{
			if (node == nullptr)
				return -1;
			s32 leftDeep = GetDeep(node->Left());
			s32 rightDeep = GetDeep(node->Right());
			return leftDeep > rightDeep ? leftDeep + 1 : rightDeep + 1;
		}

	private:
		template < class T>
		void Inorder(TreeNode<T> *node, void visit(T& item))
		{
			if (node != nullptr)
			{
				Inorder(node->Left(), visit);
				visit(node->_data);
				Inorder(node->Right(), visit);
			}
		}

		template<class T>
		void LevelScan(TreeNode<T> *node, void visit(T&item))
		{
			std::list<TreeNode<T>*> nodeList;
			nodeList.push_back(node);
			while (!nodeList.empty())
			{
				TreeNode<T> *temp = nodeList.front();
				nodeList.pop_front();
				visit(temp->_data);
				if (temp->Left())
					nodeList.push_back(temp->Left());
				if (temp->Right())
					nodeList.push_back(temp->Right());
			}
		}

		void IndentBlanks(s32 num);
		template< class T>
		void PrintTree(TreeNode<T> *node, s32 level)
		{
			if (node != nullptr)
			{
				PrintTree(node->Right(), level + 1);
				IndentBlanks(6 * level);
				printf("%d\n", node->_data);
				PrintTree(node->Left(), level + 1);
			}
		}

		template<typename T>
		void QuckSort(T &item, s32 n)
		{
			InnerQuckSort(item, 0, n-1);
		}

		template<typename T>
		void InnerQuckSort(T* item, s32 start, s32 end)
		{
			if (end - start == 1)
			{
				if (item[end] < item[start])
				{
					std::swap(item[start], item[end]);
					return;
				}
				return;
			}

			s32 mid = (start + end) / 2;
			T temp = item[mid];
			std::swap(item[mid], item[start]);

			s32 scanUp = start + 1;
			s32 scanDown = end;
			do
			{
				while (scanUp < scanDown && item[scanUp] < temp)
					scanUp++;
				while (temp < item[scanDown])
					scanDown--;
				if (scanUp < scanDown)
					std::swap(item[scanUp], item[scanDown]);
			} while (scanUp < scanDown);

			item[start] = item[scanDown];
			item[scanDown] = temp;
			if (start < scanDown - 1)
				InnerQuckSort(item, start, scanDown - 1);
			if (end > scanDown + 1)
				InnerQuckSort(item, scanDown + 1, end);
		}
	};
}

#endif
