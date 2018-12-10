#include "stdafx.h"
#include <stdexcept>
using namespace IMFS;

byte error = 0x0;

ByteArray::ByteArray(size_t size)
{
	m_ByteCount = size;
	m_pByte = new byte[m_ByteCount];
	ZeroMemory(m_pByte, m_ByteCount);
}

ByteArray::ByteArray(const byte *inByte, size_t size)
{
	m_ByteCount = size;
	m_pByte = new byte[m_ByteCount];
	CopyMemory(m_pByte, inByte, m_ByteCount);	
}

ByteArray::~ByteArray()
{
	if(NULL != m_pByte && m_ByteCount > 0)
	{
		delete []m_pByte;
		m_pByte = NULL;
		m_ByteCount = 0;
	}
}


byte* ByteArray::operator->()
{
	return m_pByte;
}

const byte* ByteArray::operator->() const
{
	return m_pByte;
}

byte& ByteArray::operator*()
{
	return *m_pByte;
}

const byte& ByteArray::operator*() const
{
	return *m_pByte;
}

byte& ByteArray::operator[](uint x)
{
	if (x > m_ByteCount) 
	{
		return error;
	}

	return (m_pByte[x]);
}

const byte& ByteArray::operator[](uint x) const
{
	if (x > m_ByteCount) 
	{
		return error;
	}

	return (m_pByte[x]);
}

const size_t ByteArray::size()const
{
	return m_ByteCount;
}

const byte *ByteArray::GetBytes()const
{
	return (const byte *)m_pByte;
}

void ByteArray::resize(size_t newSize)
{
	byte *tempByte = new byte[newSize];
	ZeroMemory(tempByte, newSize); 
	CopyMemory(tempByte, m_pByte, m_ByteCount);
	m_pByte = tempByte;
	m_ByteCount = newSize;
}

void  ByteArray::push_back(byte &inByte)
{
	resize(m_ByteCount+1);
	m_pByte[m_ByteCount-1] = inByte;
}

void ByteArray::SetBytes(const byte* p, size_t size)
{
	delete []m_pByte;
	m_pByte = new byte[size];

	CopyMemory(m_pByte, p, size);
	m_ByteCount = size;
}








