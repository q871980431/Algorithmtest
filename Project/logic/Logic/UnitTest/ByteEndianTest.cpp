#include "ByteEndianTest.h"
#include "BigEndian.h"
#include "UnitTest.h"
#include "Tools.h"
#include <map>

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
	TestBigEndianMap();

	for (int32_t i = 0; i < 100000; i++)
	{
		endian::BigEndian<32> testEndian;
		int32_t tmpA = tools::GetRandom(10, 1000000);
		int64_t tmpB = ((int64_t)tools::GetRandom(10000000, 100000000)) * 10000LL;
		int32_t tmpC = tools::GetRandom(10, 10000000);
		testEndian.Append(tmpA, tmpB, tmpC);

		endian::BigEndian<32> testEndianA(testEndian.ToString());
		int64_t tmpD = tmpB + tools::GetRandom(10, 100000) + tmpC;
		testEndianA.Append(tmpD);
		endian::BigEndian<32> testEndianB(testEndianA.ToString());
		int32_t val = tools::GetRandom(0, 4);
		switch (val)
		{
		case 0:
		{
			int32_t tmp = 0;
			testEndianB.Pick(0, tmp);
			if (tmp != tmpA)
			{
				ASSERT(false, "error");
			}
		}
		break;
		case 1:
		{
			int64_t tmp = 0;
			testEndianB.Pick(sizeof(int32_t), tmp);
			if (tmp != tmpB)
			{
				ASSERT(false, "error");
			}
		}
		break;
		case 2:
		{
			int32_t tmp = 0;
			testEndianB.Pick(sizeof(int32_t) + sizeof(int64_t), tmp);
			if (tmp != tmpC)
			{
				ASSERT(false, "error");
			}
		}
		break;
		case 3:
		{
			int64_t tmp = 0;
			testEndianB.Pick(sizeof(int32_t) + sizeof(int64_t) + sizeof(int32_t), tmp);
			if (tmp != tmpD)
			{
				ASSERT(false, "error");
			}
		}
		break;
		default: {
			ASSERT(false, "error");
		}
			break;
		}
	}
	ECHO("big endian test ok");

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

typedef bool(*SCORE_COMP_FUN)(const std::string &left, const std::string &right);
typedef std::map<std::string, HostNode, SCORE_COMP_FUN> HostScoreOrderMap;

void ByteEndianTest::TestBigEndianMap()
{
	HostScoreOrderMap map(CompareGreater);
	for (s32 i = 0; i < 10000; i++)
	{
		HostNode node;
		node.hostId = i;
		endian::BigEndian<32> bigEndian;
		int32_t tmpA = tools::GetRandom(10, 1000000);
		int64_t tmpB = ((int64_t)tools::GetRandom(10000000, 100000000)) * 10000LL;
		int32_t tmpC = tools::GetRandom(10, 10000000);
		bigEndian.Append(i, tmpA, tmpB, tmpC);
		node.score = bigEndian.ToString();
		map.emplace(node.score, node);
	}

	s32 mark = map.size() - 1;
	for (auto &iter : map)
	{
		auto findIter = map.find(iter.first);
		ASSERT(findIter != map.end(), "error");
		if (findIter->second.hostId != iter.second.hostId)
		{
			ASSERT(false, "error");
		}
		if (iter.second.hostId != mark)
		{
			ASSERT(false, "error");
		}
		mark--;
	}
	ECHO("sort success");
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
	if (len1 == 0)
		return false;

	return *buff1 > *buff2;
}

bool ByteEndianTest::Compare(const PlayerNode &left, const PlayerNode &right)
{
	return CompareInner((unsigned char *)left.scoreBuff, left.len, (unsigned char *)right.scoreBuff, right.len);
}