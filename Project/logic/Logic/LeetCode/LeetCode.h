/*
 * File:	LeetCode.h
 * Author:	XuPing
 * 
 * Created On 2019/4/17 16:46:43
 */

#ifndef __LeetCode_h__
#define __LeetCode_h__
#include "ILeetCode.h"
#include <vector>

typedef std::vector<ILeetCodeTest *> TestList;
class LeetCode : public ILeetCode
{
public:
    virtual ~LeetCode(){};

    virtual bool Initialize(IKernel *kernel);
    virtual bool Launched(IKernel *kernel);
    virtual bool Destroy(IKernel *kernel);

	static TestList & GetTestList() { return s_testList; };
protected:
private:
    static LeetCode     * s_self;
    static IKernel  * s_kernel;
	static TestList   s_testList;
};

template<typename T>
struct LeetCodeRegister
{
	LeetCodeRegister()
	{
		LeetCode::GetTestList().push_back(NEW T());
	}
};

#endif