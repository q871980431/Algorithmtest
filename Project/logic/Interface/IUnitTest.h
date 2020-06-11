/*
 * File:	IUnitTest.h
 * Author:	XuPing
 * 
 * Created On 2019/5/16 16:19:20
 */

#ifndef  __IUnitTest_h__
#define __IUnitTest_h__
#include "IModule.h"
#include <sstream>
#include <iostream>

#define TEST_EQ(A, B) if ((A) != (B))\
{\
	std::stringstream ostream;\
	ostream << A << " don't eq " << B << "File:" << __FILE__ << "Line:" << __LINE__;\
	std::string tmp(ostream.str());\
	THREAD_LOG("Test","TEST EQ FAILED:%s", tmp.c_str());\
}

class IUnitTest : public IModule
{
public:
    virtual ~IUnitTest(){};
    
};

class IUnitTestInstance
{
public:
	virtual ~IUnitTestInstance() {};
	virtual void StartTest(core::IKernel *kernel) = 0;
};

#endif