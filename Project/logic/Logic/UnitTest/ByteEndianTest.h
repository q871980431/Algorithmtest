#ifndef __BYTEENDIAN_H__
#define __BYTEENDIAN_H__
#include "IUnitTest.h"

struct PlayerNode 
{
	s64 playerId;
	char *scoreBuff;
	s32 len;
};

struct HostNode 
{
	s64 hostId;
	std::string score;
};

class ByteEndianTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void TestBigEndianTemplat();
	void TestModule();
	void TestBigEndianMap();

	static bool CompareInner(unsigned char *buff1, int32_t len1, unsigned char *buff2, int32_t size2);
	static bool Compare(const PlayerNode &left, const PlayerNode &right);
	static bool CompareGreater(const std::string &left, const std::string &right) { return CompareInner((unsigned char *)left.c_str(), (int32_t)left.size(), (unsigned char *)right.c_str(), (int32_t)right.size()); };
};


#endif
