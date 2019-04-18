/*
 * File:	LeetCode.cpp
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#include "LeetCode.h"
LeetCode * LeetCode::s_self = nullptr;
IKernel * LeetCode::s_kernel = nullptr;
TestList LeetCode::s_testList;
bool LeetCode::Initialize(IKernel *kernel)
{
    s_self = this;
    s_kernel = kernel;
    
    return true;
}

bool LeetCode::Launched(IKernel *kernel)
{
	for (auto &test : s_testList)
	{
		test->StartTest(kernel);
	}

    return true;
}

bool LeetCode::Destroy(IKernel *kernel)
{
	for (auto test : s_testList)
	{
		DEL test;
	}
	s_testList.clear();
    DEL this;
    return true;
}


