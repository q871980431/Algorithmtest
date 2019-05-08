#ifndef __LanguageTest_h__
#define __LanguageTest_h__
#include "ILeetCode.h"
namespace leetcode
{
	class F
	{
	public:
		F(s32 n) :_n(n) { ECHO("this is f construct(), n = %d", _n); };
		~F() { ECHO("this is f disconstruct(), n = %d", _n); }
	protected:
	private:
		s32 _n;
	};
	class LanguageTest : public ILeetCodeTest
	{
	public:
		virtual void StartTest(core::IKernel *kernel);
	protected:
		void Test1();

	private:
	};
}

#endif
