#include "stdafx.h"
#include "ByteStreamReader.h"

using namespace IMFS;

ByteStreamReader ::	ByteStreamReader(const std::vector<unsigned char>& source_)
: source(source_)
{
	pos = 0;
}

ByteStreamReader ::	~ByteStreamReader()
{
}

int ByteStreamReader :: ReadInt32()
{
	unsigned char bytes[4];
	bytes[0] = source[pos];
	bytes[1] = source[pos+1];
	bytes[2] = source[pos+2];
	bytes[3] = source[pos+3];
	pos+=4;
	int *result = (int*)bytes;
	return *result;
}

unsigned char 
ByteStreamReader :: ReadByte()
{
	unsigned char result = source[pos];
	pos++;
	return result;
}

unsigned int 
ByteStreamReader :: ReadUInt32()
{
	return (unsigned int)ReadInt32();
}

void 
ByteStreamReader :: SkipBytes(int size)
{
	if (size < 0)
		pos -= size;
	else if (size > 0)
		pos += (unsigned int)size;
}

unsigned short 
ByteStreamReader :: ReadUInt16()
{
	unsigned char bytes[2];
	bytes[0] = source[pos];
	bytes[1] = source[pos+1];
	pos+=2;
	unsigned short *result = (unsigned short*)bytes;
	return *result;
}

