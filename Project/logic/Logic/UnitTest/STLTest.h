#ifndef __STLTest_h__
#define __STLTest_h__
#include "IUnitTest.h"
#define RANK_KEY_SPLITTER '@'
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

private:
	uint64_t StrToUl(std::string &strVal);
	template<typename T>
	std::string GetIdentityName(const T &key);
	int32_t GetIdentityKey(std::string &strIdentityName);

private:


private:
	std::string m_zoneIdKey;
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
#endif
