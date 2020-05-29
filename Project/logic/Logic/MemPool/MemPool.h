/*
 * File:	MemPool.h
 * Author:	XuPing
 * 
 * Created On 2020/1/10 16:09:02
 */

#ifndef __MemPool_h__
#define __MemPool_h__
#include "IMemPool.h"
class MemPool : public IMemPool
{
public:
    virtual ~MemPool(){};

    virtual bool Initialize(IKernel *kernel);
    virtual bool Launched(IKernel *kernel);
    virtual bool Destroy(IKernel *kernel);
protected:
private:
    static MemPool     * s_self;
    static IKernel  * s_kernel;
};
#endif