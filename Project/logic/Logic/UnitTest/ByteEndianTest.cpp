#include "ByteEndianTest.h"
#include "BigEndian.h"
#include "UnitTest.h"

UnitTestRegister<ByteEndianTest> byteEndianTest;
void ByteEndianTest::StartTest(core::IKernel *kernel)
{
	TestBigEndianTemplat();
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