/*
 * File:	MemPool.cpp
 * Author:	XuPing
 * 
 * Created On 2020/1/10 16:09:02
 */

#include "MemPool.h"
MemPool * MemPool::s_self = nullptr;
IKernel * MemPool::s_kernel = nullptr;
bool MemPool::Initialize(IKernel *kernel)
{
    s_self = this;
    s_kernel = kernel;
    
    return true;
}

bool MemPool::Launched(IKernel *kernel)
{

    return true;
}

bool MemPool::Destroy(IKernel *kernel)
{
    DEL this;
    return true;
}


