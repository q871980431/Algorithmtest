#ifndef _ThreadTest_h_
#define _ThreadTest_h_
#include "IUnitTest.h"
#include "AtomicIntrusiveLinkedList.h"
#include <thread>

struct TestNode
{
	s32 id;
	folly::AtomicIntrusiveLinkedListHook<TestNode> hook_;
};
typedef folly::AtomicIntrusiveLinkedList<TestNode, &TestNode::hook_> TestNodeList;

class ThreadTest : public IUnitTestInstance
{
public:
	ThreadTest() {};
	virtual ~ThreadTest() {};

	virtual void StartTest(core::IKernel *kernel);
protected:
private:
	void TestConsumerAndProducter();
private:
	std::thread		s_producter;
	std::thread		s_consumer;
	TestNodeList	s_nodeList;
	bool			_close{ false };
};

#endif
