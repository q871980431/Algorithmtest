#ifndef __BYTEENDIAN_H__
#define __BYTEENDIAN_H__
#include "IUnitTest.h"

struct PlayerNode 
{
	s64 playerId;
	char *scoreBuff;
	s32 len;
};

class ByteEndianTest : public IUnitTestInstance
{
public:
	virtual void StartTest(core::IKernel *kernel);

protected:
private:
	void TestBigEndianTemplat();

	static bool CompareInner(unsigned char *buff1, int32_t len1, unsigned char *buff2, int32_t size2);
	static bool Compare(const PlayerNode &left, const PlayerNode &right);
};


#endif
