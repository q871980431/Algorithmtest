#ifndef _LANGUAGE_TEST_H_
#define _LANGUAGE_TEST_H_
#include "IUnitTest.h"
#define RANK_KEY_SPLITTER '@'

union MyUnion
{
	int32_t id;
	std::string name;
};

enum class Test1
{
	X = 0,
	Y = 1,
};
enum class Test2
{
	X = 0,
	Y = 1,
};

struct TestUnitStruct 
{
	union 
	{
		void *ptr;
		size_t count;
	};
};

class LanguageTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void TestUnion();
	void TestPoint();

private:
	void TestTry();
	int32_t TryTestInner(bool isThrow);
	void ThrowFun(bool isThrow);
	void TestBind();

private:
	void TestLambda();
	void LambdaCallFun();
	int32_t m_lambda;
private:

	void TestString();
	void TestDataFiled();
	int32_t CreateDataFiled(u8 type, s32 count);
	void UnCreateDataFiled(int32_t val, u8 &type, s32 &count);

private:

	void TestThreadLocal();

private:
};

class ConstructThrow
{
public:
	ConstructThrow();
	ConstructThrow(int32_t id);
	ConstructThrow(const char *pName);

	~ConstructThrow();
protected:
private:
	int32_t _iId;
};

class TestConstruct 
{
public:
	TestConstruct(int32_t iId);
	~TestConstruct();
private:
	ConstructThrow _def;
	ConstructThrow _int;
};

struct Point 
{
	int32_t iId;
};

#endif
