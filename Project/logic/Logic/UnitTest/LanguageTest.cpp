#include "LanguageTest.h"
#include "UnitTest.h"
#include "Tools.h"
#include <thread>

UnitTestRegister<LanguageTest> lunguagetest;
void LanguageTest::StartTest(core::IKernel *kernel)
{
	TestUnion();
	TestTry();
	TestPoint();
	TestLambda();
	TestString();
	TestDataFiled();
	TestThreadLocal();
}

void LanguageTest::TestUnion()
{
	int32_t iCount = -10;
	uint32_t iModle = 3;
	uint32_t iNum = (uint32_t)iCount % iModle;
	ECHO("Num:%d", iNum);
	std::string strTemp = "xuping";
	std::string emptyStr;
	size_t nPos = strTemp.find(emptyStr);
	if (nPos != std::string::npos)
	{
		ECHO("Find Pos");
	}
	else
	{
		ECHO("Don't Find");
	}
	TestUnitStruct testStruct;
	testStruct.ptr = nullptr;
}

void LanguageTest::TestPoint()
{
	Point* arryPoint[5];
	Point **pHead = new Point*[5];
	Point **tmp = &arryPoint[0];
	for (int32_t i = 0; i < 5; i++)
	{
		pHead[i] = new Point();
		pHead[i]->iId = i;
		tmp[i] = pHead[i];
	}
	delete[] pHead;
	ECHO("%d", 5);
}

void LanguageTest::TestTry()
{
	int32_t ret = TryTestInner(true);
	ECHO("ret:%d", ret);
	ret = TryTestInner(false);
	ECHO("ret:%d", ret);
}

int32_t LanguageTest::TryTestInner(bool isThrow)
{
	int32_t ret = 0;
	try
	{
		TestConstruct testThrow(536);
		//ThrowFun(isThrow);
		ret += 2;
		ECHO("Ret throw:%d", ret);
		return 1;
	}
	catch (const std::exception& e)
	{
		ECHO("exception msg:%s", e.what());
	}
	ret += 1;
	ECHO("Ret:%d", ret);
	return 3;
}

void LanguageTest::ThrowFun(bool isThrow)
{
	int32_t i = 0;
	i += 1;
	ECHO("i:%d", i);
	if (isThrow)
	{
		throw std::runtime_error("this is throw");
	}
}

#include <functional>

void printTest() { ECHO("__PRETTY_FUNCTION__"); }
void LanguageTest::TestBind()
{
	auto wrapper = [](const std::function<void()> &f) {
		std::cout << "__PRETTY_FUNCTION__" << std::endl;
		f();
	};

	auto print_wrapper = std::bind(wrapper, std::bind(printTest));
	//print_wrapper();
}

void LanguageTest::TestLambda()
{
	std::string myName = "xuping";
	std::string &namePtr = myName;
	auto callFun = [this, &namePtr]()
	{
		ECHO("nameptr:%d", &namePtr);
		LambdaCallFun();
		namePtr.append("test");
	};
	callFun();
	ECHO("myName:%d", &myName);
}

void LanguageTest::LambdaCallFun()
{
	m_lambda = 10;
	ECHO("This is lambda call fun, ptr:%d", &m_lambda);
}

void LanguageTest::TestString()
{
	uint32_t iA = 1;
	uint32_t iB = 2;
	int32_t iC = iA - iB;
	int32_t i = -23;
	std::string strI = std::to_string(i);
	int64_t len = strI.length();
	const char *pContet = strI.c_str();
	if (*pContet == '-')
	{
		ECHO("Content Star -");
	}
	const char *pEnd = pContet + len;
	pContet++;
	int32_t j = 0;
	while (pContet != pEnd)
	{
		pContet++;
		j++;
	}
	ECHO("End");
	i = 10;
	std::string test1((char*)&i, sizeof(i));
	if (test1.size() == sizeof(i))
	{
		const char *p = test1.c_str() + sizeof(i);
		ECHO("test:%s", test1.c_str());

	}
	char name[8];
	for (int32_t j = 0; j < 8; j++)
	{
		name[j] = j;
	}
	int32_t a = 3;
	name[a = 4,5] = 0;
}

void LanguageTest::TestDataFiled()
{
	for (s32 i = 0; i < 300; i++)
	{
		s32 num = tools::GetRandom(i, 0xFFFFFF);
		s32 val = CreateDataFiled(i, num);
		s32 num1 = 0;
		u8 iVal = 0;
		UnCreateDataFiled(val, iVal, num1);
		ASSERT(num == num1, "error");
		ASSERT((u8)i == iVal, "error");
	}
	TRACE_LOG("Test Cross");
}

int32_t LanguageTest::CreateDataFiled(u8 type, s32 count)
{
	int32_t ret = (int32_t)type << 24;
	ret |= (count & 0xFFFFFF);
	return ret;
}

void LanguageTest::UnCreateDataFiled(int32_t val, u8 &type, s32 &count)
{
	count = val & 0xFFFFFF;
	type = val >> 24;
}

class ThreadTestA
{
public:
	ThreadTestA(int32_t id) 
	{
		_id = id;
		ECHO("threadid:%ld, id:%d", std::this_thread::get_id(), _id);
	}
	~ThreadTestA()
	{
		ECHO("threadid:%ld", std::this_thread::get_id());
	}
	inline int32_t GetId() { return _id; };
protected:
private:
	int32_t _id;
};

void LanguageTest::TestThreadLocal()
{
	auto fun = []()
	{
		for (int32_t i = 0; i < 2; i++)
		{
			static thread_local ThreadTestA a(i);
			ECHO("a.id:%d", a.GetId());
		}
		ECHO("ssssssss");
	};
	std::thread t1(fun);
	std::thread t2(fun);
	t1.join();
	t2.join();
}



ConstructThrow::ConstructThrow()
{
	try
	{
		_iId = 135;
		ECHO("Construct  id:%d", _iId);
		throw std::runtime_error("this is throw");
	}
	catch (const std::exception&e)
	{
		ECHO("Construct throw:%s", e.what());
	}

}

ConstructThrow::ConstructThrow(int32_t id)
{
	_iId = id;
	throw std::runtime_error("this is ConstructThrow(int32_t id) throw");
	ECHO("ConstructThrow int id :%d", _iId);
}

ConstructThrow::ConstructThrow(const char *pName)
{
	_iId = 256;
	ECHO("ConstructThrow name id :%d", _iId);
}

ConstructThrow::~ConstructThrow()
{
	ECHO("~Construct Throw id:%d", _iId);
}

TestConstruct::TestConstruct(int32_t iId) :_def(""), _int(iId)
{
	ECHO("TestConstruct");
}

TestConstruct::~TestConstruct()
{
	ECHO("~TestConstruct");
}