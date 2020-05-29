#include "PoolTest.h"
#include "UnitTest.h"
#include "TIndexPool.h"
#include "Tools.h"

UnitTestRegister<PoolTest> poolTest;


void * operator new(size_t size) throw (std::bad_alloc);

void * operator new(size_t size) throw (std::bad_alloc)
{
	void *ret = malloc(size);
	return ret;
}



void * operator new[](size_t size)
{
	void *ret = malloc(size);
	ECHO("new[] addr:%x", ret);
	return ret;
}

void operator delete[](void *ptr)
{
	free(ptr);
}

struct PoolNode
{
	int32_t nodeId;
	~PoolNode() { ECHO("~PoolNode addr:%x", this); };
};

void PoolTest::StartTest(core::IKernel *kernel)
{
	PoolNode *pNode = new PoolNode[10];
	size_t arraySize = *(size_t *)((char*)pNode - 8);
	pNode->nodeId = 1;
	for (int32_t i = 0; i < 10; i++)
	{
		(pNode + i)->nodeId = i;
	}
	ECHO("pNodeId:%d", (pNode + 9)->nodeId);
	delete[] pNode;

	//IndexPoolTest();
}

class IndexPoolNode : public tlib::IndexNode
{
public:
	IndexPoolNode(int32_t id) :_id(id) {
		ECHO("setet");
	};
	~IndexPoolNode() { _id = 0; }

	inline int32_t Id() { return _id; };
private:
	int32_t _id;
};

void PoolTest::IndexPoolTest()
{
	typedef tlib::IndexPool<IndexPoolNode, 4> TestIndexPool;
	TestIndexPool testIndexPool;
	std::set<int32_t> nodeIndexs;
	for (int32_t i = 0; i < 10; i++)
	{
		IndexPoolNode *node = testIndexPool.Create(i);
		nodeIndexs.insert(node->GetIndex());
		ECHO("Id:%d, Index:%d", i, node->GetIndex());
	}
	std::set<int32_t> tmpIndexs = nodeIndexs;
	for (auto index : tmpIndexs)
	{
		IndexPoolNode *node = testIndexPool.Find(index);
		ECHO("Index:%d, Id:%d", index, node->Id());
		ASSERT(node->Id() == index, "id error");
		s32 flag = tools::GetRandom(0, 2);
		if (flag == 1)
		{
			ECHO("Index:%d Clear", index);
			testIndexPool.Recover(node);
			nodeIndexs.erase(index);
		}
	}
	//nodeIndexs.clear();
	for (int32_t i = 0; i < 10; i++)
	{
		IndexPoolNode *node = testIndexPool.Create(i);
		nodeIndexs.insert(node->GetIndex());
		ECHO("Id:%d, Index:%d", i, node->GetIndex());
	}

	for (auto &index : nodeIndexs)
	{
		IndexPoolNode *node = testIndexPool.Find(index);
		ASSERT(node->Id() >= 0, "error");
		ECHO("Id:%d", node->Id());
	}
}