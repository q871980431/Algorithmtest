/*
 * File:	ILeetCode.h
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#ifndef  __ILeetCode_h__
#define __ILeetCode_h__
#include "IModule.h"
class ILeetCode : public IModule
{
public:
    virtual ~ILeetCode(){};
    
};

class ILeetCodeTest
{
public:
	virtual ~ILeetCodeTest() {};
	virtual void StartTest(core::IKernel *kernel) = 0;
};
#endif