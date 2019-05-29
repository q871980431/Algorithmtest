#ifndef __DynamicPlan_h__
#define __DynamicPlan_h__
#include "ILeetCode.h"
#include <map>
typedef std::map<s32, s32> PriceMap;
class DynamicPlanTest : public ILeetCodeTest
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
	void BarCutting(core::IKernel *kernel);
	s32 MemedCuttingTest(core::IKernel *kernel, s32 barLen);
	s32 BottomUpCuttingTest(core::IKernel *kernel, s32 barLen);
private:
	PriceMap	_priceMap;
	PriceMap	_maxPriceMap;
};

#endif
