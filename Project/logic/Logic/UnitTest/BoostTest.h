#ifndef __BOOST_TEST_H__
#define __BOOST_TEST_H__
#include "IUnitTest.h"

class BoostTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);


protected:
private:
	void PoolTest();

	void LinkTest();

	void PerToolsTest();
	void TypeCastTest();
};

#endif
