#ifndef __POOL_TEST_h__
#define __POOL_TEST_h__
#include "IUnitTest.h"
#define RANK_KEY_SPLITTER '@'
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
