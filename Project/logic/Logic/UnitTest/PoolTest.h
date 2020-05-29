#ifndef __POOL_TEST_h__
#define __POOL_TEST_h__
#include "IUnitTest.h"
#define RANK_KEY_SPLITTER '@'

void * operator new (size_t size);

class PoolTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void IndexPoolTest();

private:

};
#endif
