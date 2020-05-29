#include "STLTest.h"
#include "UnitTest.h"
#include "Game_tools.h"
#include <map>
#include "BigEndian.h"
#include <memory>
#include <mutex>
#include "Tools.h"
#include "Tools_time.h"


UnitTestRegister<StlTest> stlTest;
void StlTest::StartTest(core::IKernel *kernel)
{
	m_zoneIdKey = "113";
	TestMapKey();
	TestString();
	TestKernelAsync(kernel);
	TestAsyncQueue(kernel);
	TestStrSqlite();
	TestVectorAndSharedPtr();
	TestMap();
	TestOffSet();
	TestLock();
	TestLock2();
	TestMapRErase();
	TestSort(0);
	TestSort(1);
	TestSort(2);
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
	std::vector<int32_t> vecPlayerIds;
	for (int32_t i = 0; i < 10; i++)
	{
		vecPlayerIds.push_back(i);
	}
	std::set<int32_t> setPlayerIds(vecPlayerIds.begin(), vecPlayerIds.end());
	for (auto &id : setPlayerIds)
	{
		ECHO("Id:%d", id);
	}

}

void StlTest::TestVector()
{
	//typedef std::vector<std::string &> VecName;
	//std::string tmp1("XP1");
	//std::string &tmpR = tmp1;
	//VecName vecName;
	//vecName.push_back(tmpR);
}

int cmp(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b)
		return -1;
	else if (*(int*)a > *(int*)b)
		return 1;
	else
		return 0;
}

void StlTest::TestSort(s32 iType)
{
	s32 iNum = 1000000;

	std::vector<s32> vec;
	vec.reserve(iNum);

	while (iNum--)
		vec.push_back((s32)tools::Random());
	s64 iNow = tools::GetTimeMillisecond();

	if (iType == 0)
		qsort(&vec[0], vec.size(), sizeof(int), cmp);
	else if (iType == 1)
		std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) { return a < b; });
	else if (iType == 2)
		std::sort(vec.begin(), vec.end());
	TRACE_LOG("type:%d, expends %ld ms", iType, tools::GetTimeMillisecond() - iNow);
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

void StlTest::TestString()
{
	std::string content = "this is a string";
	size_t pos = content.find("as");
	size_t fPos = content.find_first_of("as");
	pos = content.find("is");
	content.insert(pos + strlen("is"), "a");
	ECHO("content:%s", content.c_str());
	size_t iBegin = fPos;
	//std::string *tenR = &content;
	size_t &pTmp = pos;
	size_t iEnd = pos;
	ECHO("iBegin:%p, iEnd:%p iP:%p, Diff = %zu, ", &iBegin, &iEnd, &pTmp, &iEnd - &iBegin);
	const char *pConstTmp = "\r\n23";
	int32_t iVal = atoi(pConstTmp);
	ECHO("val:%d", iVal);
	std::ostringstream osStream;
	osStream << "test";
	osStream.clear();
	const char *contentStream = osStream.str().c_str();
	ECHO("Content:%s", contentStream);
}

void StlTest::TestLock()
{
	try
	{
		CanLock lock;
		std::lock_guard<CanLock> lockGuard(lock);
	}
	catch (const std::exception&e)
	{
		ECHO("Exception:%s", e.what());
	}
	ECHO("No Try");
	CanLock lock;
	std::lock_guard<CanLock> lockGuard(lock);
	int32_t i = 3;
	ECHO("i:%d", i);
}

void StlTest::TestLock2()
{
	std::lock_guard<std::recursive_mutex> lockGuard(m_mutex);
	ECHO("GetLock 1");
	{
		std::lock_guard<std::recursive_mutex> lockGuard1(m_mutex);
		ECHO("GetLock 2");
	}
	ECHO("Sucesss");
}

void StlTest::TestMapKey()
{
	std::map<int32_t, int32_t> playerIds;
	playerIds.emplace(1, 1);
	playerIds.emplace(1, 2);
	HostScoreOrderMap hostMap(StlTest::CompareGreater);
	std::string key1 = "xuping";
	std::string key2 = "";
	hostMap.emplace(key1, 1);
	hostMap.emplace("y", 3);
	hostMap.emplace("y", 4);
	hostMap.emplace(key2, 2);
	hostMap.emplace(key2, 3);
	auto iter = hostMap.find(key2);
	if (iter != hostMap.end())
	{
		ECHO("Find Key2:%s", iter->first.c_str());
		hostMap.erase(iter);
		auto tmpIter = hostMap.find(key2);
		if (tmpIter == hostMap.end())
		{
			ECHO("Don't find key2 :%s", key2.c_str());
		}
	}

}

bool StlTest::CompareGreaterInner(unsigned char *pLeftBuff, int32_t iLeftLen, unsigned char *pRightBuff, int32_t iRightLen)
{
	if (iLeftLen == 0)
		return false;
	if (iRightLen == 0)
		return false;

	if (iLeftLen > iRightLen)
		iLeftLen = iRightLen;

	while (iLeftLen > 0 && (*pLeftBuff == *pRightBuff))
	{
		pLeftBuff++;
		pRightBuff++;
		iLeftLen--;
	}
	if (iLeftLen == 0)
		return false;

	return *pLeftBuff > *pRightBuff;
}