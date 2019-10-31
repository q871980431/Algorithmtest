#include "PoolTest.h"
#include "UnitTest.h"
#include "TIndexPool.h"
#include "Tools.h"

UnitTestRegister<PoolTest> poolTest;
void PoolTest::StartTest(core::IKernel *kernel)
{
	IndexPoolTest();
}

class IndexPoolNode : public tlib::IndexNode
{
public:
	IndexPoolNode(int32_t id) :_id(id) {
		ECHO("setet");
	};

	inline int32_t Id() { return _id; };
private:
	int32_t _id;
};

void PoolTest::IndexPoolTest()
{
	typedef tlib::IndexPool<IndexPoolNode, 4> TestIndexPool;
	TestIndexPool testIndexPool;
	std::vector<int32_t> nodeIndexs;
	for (int32_t i = 0; i < 10; i++)
	{
		IndexPoolNode *node = testIndexPool.Create(i);
		nodeIndexs.push_back(node->GetIndex());
		ECHO("Id:%d, Index:%d", i, node->GetIndex());
	}

	for (auto index : nodeIndexs)
	{
		IndexPoolNode *node = testIndexPool.Find(index);
		ECHO("Index:%d, Id:%d", index, node->Id());
		s32 flag = tools::GetRandom(0, 2);
		if (flag == 1)
		{
			ECHO("Index:%d Clear", index);
			testIndexPool.Recover(node);
		}
	}
	nodeIndexs.clear();
	for (int32_t i = 0; i < 10; i++)
	{
		IndexPoolNode *node = testIndexPool.Create(i);
		nodeIndexs.push_back(node->GetIndex());
		ECHO("Id:%d, Index:%d", i, node->GetIndex());
	}
}