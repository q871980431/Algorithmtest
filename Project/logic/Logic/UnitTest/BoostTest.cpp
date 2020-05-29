#include "BoostTest.h"
#include "UnitTest.h"
#include "Game_tools.h"
#include "Tools.h"
#include <map>
#include <memory>
#include "boost/pool/pool.hpp"
#include "gperftools/malloc_extension.h"
#include "gperftools/malloc_extension_c.h"
#include "google/profiler.h"


UnitTestRegister<BoostTest> boostTest;
void BoostTest::StartTest(core::IKernel *kernel)
{
	PoolTest();
	PerToolsTest();
	LinkTest();
	TypeCastTest();
}

void BoostTest::PoolTest()
{
	char pName[sizeof("xuping1") + 1] = "xuping1";
	char pBuff[sizeof(void*)]{0};
	memset(pBuff, 1, sizeof(pBuff));
	void **pNull = (void **)pBuff;
	*pNull = pName;

	char *pTest = (char *)*(void **)pNull;
	boost::pool<> p(sizeof(int32_t));
	for (size_t i= 0; i < 1000; i++)
	{
		int32_t *const t = (int32_t *)p.malloc();
		p.free(t);
	}
}

struct TestLink
{
	TestLink *next;
	s32 id;
};

struct TestLinkB 
{
	s32 idb;
};

struct TestLinkA : public TestLinkB, public TestLink
{
	s32 ida;
};
TestLink * & nextlink(void *ptr)
{
	return *(TestLink**)ptr;
}

size_t * &netsize_t(void *ptr)
{
	return *(size_t**)ptr;
}

void BoostTest::LinkTest()
{
	size_t *testIV = nullptr;
	size_t *testI = (size_t*)&testIV;
	size_t testIP = 1;
	size_t *testP = &testIP;
	//size_t **ppTest = (size_t**)testI;
	//size_t *pTest1 = *ppTest;
	*(size_t**)&testI = testP;

	TestLink links[20];
	for (size_t i = 0; i < 20; i++)
	{
		links[i].id = i;
	}
	TestLink *first = nullptr;
	TestLink *end = &links[19];
	//end->next = first;
	nextlink(end) = first;
	for (TestLink *iter = end -1; iter != links; end = iter, iter--)
	{
		//iter->next = end;
		nextlink(iter) = end;
	}
	//links->next = end;
	nextlink(links) = end;

	TestLink *iter = links->next;
	while (iter != nullptr)
	{
		ECHO("Iter Id:%d", iter->id);
		iter = iter->next;
	}
	ECHO("Link OK");
	void *pVoid = nullptr;
	void **ppVoid = &pVoid;
	void **ppVoidE = reinterpret_cast<void**>(pVoid);
	void **ppVoidF = (void **)pVoid;
	void *pTarget = malloc(sizeof(void*));
	void *pTarget1 = malloc(sizeof(void*));
	ECHO("%p, %p", pTarget, pTarget1);
	pVoid = pTarget1;
	void **pTarget11 = (void **)pTarget1;
	*pTarget11 = pTarget;
	//*(void **)pTarget1 = pTarget;
	ECHO("%p", pVoid);
	ECHO("%p", *(void**)pVoid);
	ECHO("Test");
}

void BoostTest::PerToolsTest()
{
	//ProfilerStart("my.prof");
	char *pBuff1 = (char*)malloc(100);
	size_t cxx_bytes_used, c_bytes_used;
	MallocExtension::instance()->GetNumericProperty(
		"generic.current_allocated_bytes", &cxx_bytes_used);
	MallocExtension_GetNumericProperty("generic.current_allocated_bytes", &c_bytes_used);
	ECHO("%zu byte", cxx_bytes_used);
	//ProfilerStop();
}

void BoostTest::TypeCastTest()
{
	TestLinkA stLinkA;
	stLinkA.id = 1;
	stLinkA.ida = 2;
	TestLinkA *pStLinkA = &stLinkA;
	TestLink *pTestLink = pStLinkA;
	TestLink *pTestLink1 = static_cast<TestLink *>(pStLinkA);
	TestLink *pTestLinkF = (TestLink *)pStLinkA;
	TestLink *pTestR = reinterpret_cast<TestLink*>(pStLinkA);
	ECHO(":%p s", pStLinkA);
	ECHO(":%p auto", pTestLink);
	ECHO(":%p static_cast", pTestLink1);
	ECHO(":%p forc cast", pTestLinkF);
	ECHO(":%p forc cast", pTestR);
}