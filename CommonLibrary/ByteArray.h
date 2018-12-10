#pragma once

namespace IMFS
{
	class ByteArray
    {
	public:
		explicit ByteArray(size_t size);
		explicit ByteArray(const byte *inByte, size_t size);
		~ByteArray();
		
		byte& operator[](uint x);
		const byte& operator[](uint x) const;
		byte* operator->();
		const byte* operator->() const;
		byte& operator*();
		const byte& operator*() const;

		const size_t size()const;
		const byte *GetBytes() const;

		void resize(size_t newSize);
		void  push_back(byte &inByte);

		void SetBytes(const byte* p, size_t size);
		
		bool empty() const
		{
			return m_ByteCount == 0;
		}

        byte* begin() const
        {
            return m_pByte;
        }

        byte* end() const
        {
            return m_pByte + m_ByteCount;
        }

	private:
		ByteArray(const ByteArray& src);
		ByteArray& operator = (const ByteArray& src);
	private:
		byte *m_pByte;
		size_t m_ByteCount;
	};
}