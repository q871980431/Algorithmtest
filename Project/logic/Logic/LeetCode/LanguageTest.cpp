#include "LanguageTest.h"
#include "LeetCode.h"
#include <memory>
#include <vector>

namespace leetcode
{
	LeetCodeRegister<LanguageTest> test;
	void LanguageTest::StartTest(core::IKernel *kernel)
	{
		Test1();
	}
	void LanguageTest::Test1()
	{
		std::shared_ptr<F> f = std::make_shared<F>(1);
		std::shared_ptr<F> f1 = std::make_shared<F>(2);
		f.swap(f1);
		ECHO("F:UseCount:%d", f.use_count());
	}
}
