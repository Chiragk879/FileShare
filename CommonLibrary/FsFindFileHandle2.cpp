#include "stdafx.h"

using namespace IMFS;

FSFindFileHandle2 :: FSFindFileHandle2()
{
	path = NULL;
	infoLevel = SMB_INFO_ERROR;
	searchAttributes = 0;
}

FSFindFileHandle2 :: ~FSFindFileHandle2()
{
}

ConstNormalizedPathPtr 
FSFindFileHandle2 :: GetPath() const
{
	return path;
}

void 
FSFindFileHandle2 :: SetPath(ConstNormalizedPathPtr value)
{
	path = value;
}

FindInfoLevel 
FSFindFileHandle2 :: GetInfoLevel() const
{
	return infoLevel;
}

void 
FSFindFileHandle2 :: SetInfoLevel(FindInfoLevel value)
{
	infoLevel = value;
}

const std::vector<byte>& 
FSFindFileHandle2 :: GetEaFilterData() const
{
	return eaFilterData;
}

void 
FSFindFileHandle2 :: SetEaFilterData(const std::vector<byte>& value)
{
	eaFilterData = value;
}

FlagsAndAttributes 
FSFindFileHandle2 :: GetSearchAttributes() const
{
	return searchAttributes;
}

void 
FSFindFileHandle2 :: SetSearchAttributes(FlagsAndAttributes value)
{
	searchAttributes = value;
}

Folder2& 
FSFindFileHandle2 :: GetSearchFolder()
{
	return searchFolder;
}

void 
FSFindFileHandle2 :: SetSearchFolder(Folder2& value)
{
	searchFolder = value;
}

const string& 
FSFindFileHandle2 :: ToString()
{
	if (mystring.Length() == 0 && path != NULL)
	{
		mystring = path->GetRelativePath();
	}
	return mystring;
}