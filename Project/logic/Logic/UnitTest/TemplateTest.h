#ifndef _TEMPLATE_TEST_H_
#define _TEMPLATE_TEST_H_
#include "IUnitTest.h"

class TemplateTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

	template<typename T>
	void TestInnerTemplate();
	template<typename T>
	bool getRet();
protected:
private:
};

template<>
bool TemplateTest::getRet<s32>() { return true; }

template<>
bool TemplateTest::getRet<float>() { return false; }

template<>
void TemplateTest::TestInnerTemplate<s32>()
{
	bool intRet = getRet<s32>();
	if (intRet)
	{
		ECHO("test oks");
	}
}


#endif
