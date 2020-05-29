#include "TemplateTest.h"
#include "UnitTest.h"
UnitTestRegister<TemplateTest> templateTest;

void TemplateTest::StartTest(core::IKernel *kernel)
{
	//TestInnerTemplate<s32>();
	bool retInt = getRet<s32>();
	bool retFloat = getRet<float>();
}