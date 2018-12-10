#include "stdafx.h"

using namespace IMFS;

FindFileInfoStandard2 :: FindFileInfoStandard2()
: FindFileInfo2()
{
    filename = nullptr;
    ShortFileName = nullptr;
	resumeKey = 0;
	::memset(&CreationTime, 0, sizeof(CreationTime));
	::memset(&LastAccessTime, 0, sizeof(CreationTime));
	::memset(&LastWriteTime, 0, sizeof(CreationTime));
	DataSize = 0;
	AllocationSize = 0;
	Attributes = 0;
}

FindFileInfoQueryEaSize2 :: FindFileInfoQueryEaSize2()
: FindFileInfoStandard2()
{
	EaSize = 0;
}


FindFileInfoQueryEasFromList2 :: FindFileInfoQueryEasFromList2()
: FindFileInfoQueryEaSize2()
{
}

FindFileInfoNamesInfo2 :: FindFileInfoNamesInfo2()
:FindFileInfo2()
{
	filename = nullptr;
	resumeKey = 0;
	FileIndex = 0;
}

FindFileInfoDirectoryInfo2 :: FindFileInfoDirectoryInfo2()
: FindFileInfoNamesInfo2()
{
	::memset(&CreationTime, 0, sizeof(CreationTime));
	::memset(&LastAccessTime, 0, sizeof(CreationTime));
	::memset(&LastWriteTime, 0, sizeof(CreationTime));
	::memset(&ChangeTime, 0, sizeof(ChangeTime));

	AllocationSize = 0;
	ExtFileAttributes = 0;
	EndOfFile = 0;
}

FindFileInfoFullDirectoryInfo2 :: FindFileInfoFullDirectoryInfo2()
: FindFileInfoDirectoryInfo2()
{
	EaSize = 0;
}


FindFileInfoBothDirectoryInfo2 :: FindFileInfoBothDirectoryInfo2()
: FindFileInfoFullDirectoryInfo2()
{
    ShortFileName = nullptr;
}

FindFileInfoIdFullDirectoryInfo2 :: FindFileInfoIdFullDirectoryInfo2()
: FindFileInfoFullDirectoryInfo2()
{
	FileId = 0;
}

FindFileInfoIdBothDirectoryInfo2 :: FindFileInfoIdBothDirectoryInfo2()
: FindFileInfoBothDirectoryInfo2()
{
	FileId = 0;
}

