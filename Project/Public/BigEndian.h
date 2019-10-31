#ifndef __BIGENDIAN_H__
#define __BIGENDIAN_H__

namespace endian{
	const static int tmp = 0x4321;
	constexpr bool IsBigEndian()
	{
		return 0x21 != *(unsigned char *)&tmp;
	}
	const static bool IS_BIG_ENDIAN = IsBigEndian();

	template<int32_t N>
	inline void reverse(char *l, const char *r)
	{
		*l = *r;
		reverse<N - 1>(l + 1, r - 1);
	}

	template<>
	inline void reverse<1>(char *l, const char *r)
	{
		*l = *r;
	}

	template<int32_t BUFF_SIZE = 16>
	class BigEndian
	{
	public:
		BigEndian() :m_size(0) {};

		void Append(uint16_t val) { InnerAppend<2>(&val); };
		void Append(uint32_t val) { InnerAppend<4>(&val); };
		void Append(uint64_t val) { InnerAppend<8>(&val); };
		template<typename ...Args>
		void Append(Args... args)
		{
			int32_t a[] = { (Append(args), 0)... };
		}

		inline const char *GetBuff() { return m_buff; }
		inline int32_t Size() { return m_size; };
		inline std::string ToString() { return std::string(m_buff, m_size); };
	private:
		template<int32_t N>
		void InnerAppend(void *data)
		{
			if (m_size + N <= BUFF_SIZE)
			{
				if (IS_BIG_ENDIAN)
					memcpy(m_buff + m_size, data, N);
				else
					reverse<N>(m_buff + m_size, (const char*)data+(N-1));
				m_size += N;
			}
		}
	protected:
	private:
		char m_buff[BUFF_SIZE];
		int32_t m_size;
	};
}
#endif
