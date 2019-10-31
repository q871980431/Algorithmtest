#include "STLTest.h"
#include "UnitTest.h"
#include "Game_tools.h"
#include <map>
#include "BigEndian.h"
#include <memory>

UnitTestRegister<StlTest> test;
void StlTest::StartTest(core::IKernel *kernel)
{
	m_zoneIdKey = "113";
	TestKernelAsync(kernel);
	TestAsyncQueue(kernel);
	TestStrSqlite();
	TestVectorAndSharedPtr();
	TestMap();
	TestOffSet();
}

void StlTest::TestKernelAsync(core::IKernel *kernel)
{
	s32 i = -1;
	s32 j = 1;
	if (!endian::IS_BIG_ENDIAN)
	{
		ECHO("Less code");
	}
	else
	{
		ECHO("Big Code");
	}
	std::map<int32_t, int32_t> playerIds;
	for (int32_t i = 0; i < 10; i++)
	{
		playerIds.emplace(i, i);
	}

	int32_t iSize = 10;
	if (playerIds.size() > 0)
	{
		auto rIter = playerIds.rbegin();
		int32_t id = rIter->first;
		ECHO("Id:%d", id);
	}
	uint64_t maxUInt = (std::numeric_limits<uint64_t>::max)();
	int64_t iInt = (int64_t)maxUInt;
	std::string strInt = std::to_string(iInt);
	int64_t iTemp = std::atoll(strInt.c_str());
	uint64_t iuTemp = (uint64_t)iTemp;
	if (iuTemp == maxUInt)
	{
		ECHO("OK");
	}

	std::string strUint = std::to_string(maxUInt);
	int64_t iUTemp = std::atoll(strUint.c_str());
	uint64_t iUTemp2 = (uint64_t)iUTemp;
	if (iUTemp2 == maxUInt)
	{
		ECHO("OK");
	}
	std::string sVal("dsd");
	uint64_t iTestStr = StrToUl(sVal);
	ECHO("ITestStr:%zu", iTestStr);
	uint64_t iUTemp3 = StrToUl(strUint);
	if (iUTemp3 == maxUInt)
	{
		ECHO("OK");
	}
	char a = 0;
	std::string sEmpity;
	sEmpity.push_back(a);
	if (sEmpity.empty())
	{
		ECHO("Empty");
	}
	iSize = sEmpity.size();
	int32_t iLen = sEmpity.length();
	int32_t iStrlen = strlen(sEmpity.c_str());


	ECHO("Test");
}

void StlTest::TestAsyncQueue(core::IKernel *kernel)
{

}

void StlTest::TestStrSqlite()
{
	std::string strIdentityKey = GetIdentityName<int32_t>(-5);
	int32_t val = GetIdentityKey(strIdentityKey);
	ECHO("Val:%d", val);
}

class TestSharedPtr
{
public:
	TestSharedPtr() { ECHO("TestSharedPtr()"); };
	~TestSharedPtr() { ECHO("~TestSharedPtr"); };
protected:
private:
};

void StlTest::TestVectorAndSharedPtr()
{
	typedef std::vector<std::shared_ptr<TestSharedPtr>> VecTestPtr;
	VecTestPtr tempVecPtr;
	for (int32_t i = 0; i < 10; i++)
	{
		auto pTestPtr = std::make_shared<TestSharedPtr>();
		tempVecPtr.push_back(pTestPtr);
	}
	tempVecPtr.clear();
	ECHO("ssssssss");
}

struct TestMapNode 
{
	int32_t iId;
	std::string strName;
	TestMapNode() {};

	TestMapNode(const TestMapNode &stVal): strName(stVal.strName)
	{
		this->iId = stVal.iId;
	}

	TestMapNode(TestMapNode &&stVal)
	{
		this->iId = stVal.iId;
		this->strName.swap(stVal.strName);
	}

	bool operator<(const TestMapNode &stVal) const
	{
		if (iId == stVal.iId)
		{
			return strName > stVal.strName;
		}
		return iId > stVal.iId;
	}
};
void StlTest::TestMap()
{
	typedef std::set<TestMapNode> TestSet;
	TestSet testSet;
	for (int32_t i = 0; i < 5; i++)
	{
		TestMapNode node;
		node.iId = i;
		node.strName = "test";
		testSet.insert(node);
		node.strName = "test1";
		testSet.insert(std::move(node));
	}
	ECHO("Count:%zu", testSet.size());
}

void StlTest::TestOffSet()
{
	struct TmpStruct 
	{
		char c;
		double d;
	};
#ifdef WIN32
	size_t offsetC = offsetof(struct TmpStruct, c);
	size_t offsetD = offsetof(struct TmpStruct, d);
	ECHO("the first element is at offset %zu\n", offsetC);
	ECHO("the double is at offset %zu\n", offsetD);
#endif // WIN32

	std::vector<int32_t> playerIds;
	playerIds.push_back(1);
	int32_t i = 8;
	int32_t j = 0;
	int32_t k = (j + (size_t)i - 1) & ~((size_t)i - 1);
	ECHO("K = %d", k);
}

void StlTest::TestMapRErase()
{
	typedef std::map<int32_t, int32_t> TestMap;
	TestMap players;
	for (int32_t i = 0; i < 10; i++)
	{
		players.emplace(i, i);
	}
		
}

uint64_t StlTest::StrToUl(std::string &strVal)
{
	uint64_t iRet = 0;
	try
	{
		iRet = std::stoull(strVal);
	}
	catch (const std::exception& e)
	{
		ECHO("What:%s", e.what());
		iRet = 0;
	}
	return iRet;
}

int32_t StlTest::GetIdentityKey(std::string &strIdentityName)
{
	std::string::size_type n;
	n = strIdentityName.find(RANK_KEY_SPLITTER);
	if (n == std::string::npos || n == strIdentityName.size())
		return 0;
	std::string strSub = strIdentityName.substr(n+1);
	return std::atoi(strSub.c_str());
}