#include "ByteEndianTest.h"
#include "BigEndian.h"
#include "UnitTest.h"

UnitTestRegister<ByteEndianTest> byteEndianTest;
void ByteEndianTest::StartTest(core::IKernel *kernel)
{
	TestBigEndianTemplat();
	TestModule();
}

void ByteEndianTest::TestBigEndianTemplat()
{
	endian::BigEndian<> bigEndian;
	bigEndian.Append((uint16_t)10, (uint64_t)13, (uint32_t)4);
	endian::BigEndian<> endian2;
	endian2.Append((uint16_t)10, (uint64_t)13, (uint32_t)5);
	
	std::vector<PlayerNode> playerNodes;
	playerNodes.push_back({10, (char *)bigEndian.GetBuff(), bigEndian.Size() });
	playerNodes.push_back({ 11, (char *)endian2.GetBuff(), endian2.Size() });
	std::sort(playerNodes.begin(), playerNodes.end(), ByteEndianTest::Compare);

	for (const auto & node : playerNodes)
	{
		TRACE_LOG("PlayerId:%d", node.playerId);
	}
	std::string testNode = bigEndian.ToString();
	const char *pCtr = testNode.c_str();
	const char *pData = testNode.data();
	size_t len = testNode.size();
	testNode.append(std::to_string(12345));
	size_t len2 = testNode.size();
	ECHO("Len:%u, Len2:%u", len, len2);

	if (pCtr == pData)
	{
		ECHO("C_Str == data");
	}
	else
	{
		ECHO("C_Str != data");
	}

}

const int32_t index1 = 0x1;
const int32_t index2 = 0x1 << 1;
const int32_t index3 = 0x1 << 2;

#define SETBIT(x, y) x |= (1<<y)
#define CLRBIT(x, y) x &= ~(1<<y)
#define GETBIT(x, y) ((x & (1<<y)) ? true : false)

void ByteEndianTest::TestModule()
{
	int32_t i = 0;
	SETBIT(i, 0);
	ASSERT(GETBIT(i,0), "OK");
	CLRBIT(i, 1);
	ASSERT(!GETBIT(i,1), "OK");
	SETBIT(i, 2);
	ASSERT(GETBIT(i, 1) == false, "OK");
	ASSERT(GETBIT(i, 2) == true, "OK");
	SETBIT(i, 1);
	ASSERT(GETBIT(i, 1), "OK");
	ASSERT(GETBIT(i, 2), "OK");
	CLRBIT(i, 1);
	ASSERT(GETBIT(i, 1) == false, "OK");
	ASSERT(GETBIT(i, 2), "OK");
}

bool ByteEndianTest::CompareInner(unsigned char *buff1, int32_t len1, unsigned char *buff2, int32_t size2)
{
	if (len1 > size2)
		len1 = size2;

	while (len1 > 0 && (*buff1 == *buff2) )
	{
		buff1++;
		buff2++;
		len1--;
	}

	return *buff1 > *buff2;
}

bool ByteEndianTest::Compare(const PlayerNode &left, const PlayerNode &right)
{
	return CompareInner((unsigned char *)left.scoreBuff, left.len, (unsigned char *)right.scoreBuff, right.len);
}