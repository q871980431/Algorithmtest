#include "DynamicPlan.h"
#include "LeetCode.h"
LeetCodeRegister<DynamicPlanTest> dynamicPlanTest;

void DynamicPlanTest::StartTest(core::IKernel *kernel)
{
	BarCutting(kernel);
}

void DynamicPlanTest::BarCutting(core::IKernel *kernel)
{
	TRACE_LOG("**********BarCutting**************");
	_priceMap.emplace(1, 1);
	_priceMap.emplace(2, 5);
	_priceMap.emplace(3, 8);
	_priceMap.emplace(4, 9);
	_priceMap.emplace(5, 10);
	_priceMap.emplace(6, 17);
	_priceMap.emplace(7, 17);
	_priceMap.emplace(8, 20);
	_priceMap.emplace(9, 24);
	_priceMap.emplace(10, 30);
	TRACE_LOG("BarLen:%d, MaxPrice:%d Buttom:%d", 4, MemedCuttingTest(kernel, 4), BottomUpCuttingTest(kernel, 4));
	TRACE_LOG("BarLen:%d, MaxPrice:%d Buttom:%d", 9, MemedCuttingTest(kernel, 9), BottomUpCuttingTest(kernel, 9));
	TRACE_LOG("BarLen:%d, MaxPrice:%d Buttom:%d", 12, MemedCuttingTest(kernel, 12), BottomUpCuttingTest(kernel, 12));
	TRACE_LOG("BarLen:%d, MaxPrice:%d Buttom:%d", 15, MemedCuttingTest(kernel, 15), BottomUpCuttingTest(kernel, 15));
	TRACE_LOG("BarLen:%d, MaxPrice:%d Buttom:%d", 22, MemedCuttingTest(kernel, 22), BottomUpCuttingTest(kernel, 22));
}

s32 DynamicPlanTest::MemedCuttingTest(core::IKernel *kernel, s32 barLen)
{
	auto maxIter = _maxPriceMap.find(barLen);
	if (maxIter != _maxPriceMap.end())
		return maxIter->second;

	auto iter = _priceMap.begin();
	if (barLen == iter->first)
	{
		_maxPriceMap.emplace(iter->first, iter->second);
		return iter->second;
	}
	if (barLen < iter->first)
		return 0;
	s32 maxPrice = 0;
	for (; iter != _priceMap.end(); iter++)
	{
		if (barLen < iter->first)
			break;
		s32 temp = iter->second + MemedCuttingTest(kernel, barLen - iter->first);
		maxPrice = max(maxPrice, temp);
	}
	_maxPriceMap.emplace(barLen, maxPrice);
	return maxPrice;
}

s32 DynamicPlanTest::BottomUpCuttingTest(core::IKernel *kernel, s32 barLen)
{
	PriceMap maxPrice;
	PriceMap pathPrice;
	for (s32 i = 0; i <= barLen; i++)
	{
		s32 val = 0;
		for (auto innerIter = _priceMap.begin(); innerIter != _priceMap.end(); innerIter++)
		{
			if (innerIter->first > i)
				break;

			s32 temp = innerIter->second;
			auto priceIter = maxPrice.find(i - innerIter->first);
			ASSERT(priceIter != maxPrice.end(), "error");
			if (priceIter != maxPrice.end())
				temp += priceIter->second;
			if (val < temp)
			{
				pathPrice[i] = innerIter->first;
				val = temp;
			}
		}
		maxPrice.emplace(i, val);
	}
	s32 val = barLen;
	while (val>0)
	{
		s32 cuut = pathPrice[val];
		printf("Cutting:%d, price:%d\n", cuut, _priceMap[cuut]);
		val = val - cuut;
	}
	return maxPrice[barLen];
}