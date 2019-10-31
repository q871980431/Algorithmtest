#include "HeapTest.h"
#include "UnitTest.h"
#include "Game_tools.h"
#include "Tools.h"
#include "THeap.h"
#include <map>
#include <memory>


UnitTestRegister<HeapTest> heapTest;
void HeapTest::StartTest(core::IKernel *kernel)
{
	m_zoneIdKey = "113";
	TestHeapRemove(kernel);
}

void HeapTest::TestHeapRemove(core::IKernel *kernel)
{
	typedef THeap<s32> IDHeap;
	IDHeap idHeap(10);
	std::vector<int32_t> ids;
	for (int32_t i = 0; i < 10; i++)
	{
		idHeap.Insert(i);
		ids.push_back(i);
	}
	//for (int32_t i = 0; i < 10; i++)
	//{
	//	s32 left = tools::GetRandom(0, (int32_t)ids.size());
	//	s32 right = tools::GetRandom(0, (int32_t)ids.size());
	//	if (left != right)
	//		std::swap(ids[left], ids[right]);
	//}
	for (auto id : ids)
	{
		bool ret = idHeap.Remove(id);
		ASSERT(ret, "error");
		int32_t heapSize = 0;
		const int32_t *head = idHeap.GetHeap(heapSize);
		ECHO("Remove:%d, Heap size:%d, Min:%d", id, heapSize, head[0]);
	}
	ECHO("Remove Test OK!!!!!!");
}