#ifndef __HeapTest_h__
#define __HeapTest_h__
#include "IUnitTest.h"
class HeapTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void TestHeapRemove(core::IKernel *kernel);

private:
	std::string m_zoneIdKey;
};
#endif
