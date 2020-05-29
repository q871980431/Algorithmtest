#ifndef __STLTest_h__
#define __STLTest_h__
#include "IUnitTest.h"
#include <map>
#include <mutex>

#define RANK_KEY_SPLITTER '@'

typedef bool(*SCORE_COMP_FUN)(const std::string &left, const std::string &right);
typedef std::map<std::string, uint64_t, SCORE_COMP_FUN> HostScoreOrderMap;

class StlTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void TestKernelAsync(core::IKernel *kernel);
	void TestAsyncQueue(core::IKernel *kernel);
	void TestStrSqlite();
	void TestVectorAndSharedPtr();
	void TestMap();
	void TestOffSet();
	void TestMapRErase();
	void TestVector();
	void TestSort(s32 iType);

private:
	uint64_t StrToUl(std::string &strVal);
	template<typename T>
	std::string GetIdentityName(const T &key);
	int32_t GetIdentityKey(std::string &strIdentityName);

private:
	void TestString();
	void TestLock();
	void TestLock2();

private:
	std::string m_zoneIdKey;
	std::recursive_mutex  m_mutex;
private:
	void TestMapKey();
	static bool CompareGreaterInner(unsigned char *pLeftBuff, int32_t iLeftLen, unsigned char *pRightBuff, int32_t iRightLen);
	static bool CompareGreater(const std::string &left, const std::string &right) { return CompareGreaterInner((unsigned char *)left.c_str(), (int32_t)left.size(), (unsigned char *)right.c_str(), (int32_t)right.size()); };
};
template<typename T>
inline std::string StlTest::GetIdentityName(const T &key)
{
	std::string ret(m_zoneIdKey);
	ret.push_back(RANK_KEY_SPLITTER);
	ret.append(std::to_string(key));
	return ret;
}
template<>
inline std::string StlTest::GetIdentityName<std::string>(const std::string &strKey)
{
	std::string ret(m_zoneIdKey);
	ret.push_back(RANK_KEY_SPLITTER);
	ret.append(strKey);
	return ret;
}

class CanLock
{
public:
	CanLock() { ECHO("CanLock"); };
	~CanLock() { ECHO("~CanLock"); };

	void lock() { ECHO("Enter Lock"); /*throw std::runtime_error("lock error");*/ };
	void unlock() { ECHO("Leave Lock"); };

protected:
private:
};

#endif
