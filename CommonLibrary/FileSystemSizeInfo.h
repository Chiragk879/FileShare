#pragma once

namespace IMFS
{
	// Possibly undocumented or in DDK
	typedef struct _FILE_FS_FULL_SIZE_INFORMATION {
		LARGE_INTEGER TotalAllocationUnits;
		LARGE_INTEGER CallerAvailableAllocationUnits;
		LARGE_INTEGER ActualAvailableAllocationUnits;
		ULONG SectorsPerAllocationUnit;
		ULONG BytesPerSector;
	} FILE_FS_FULL_SIZE_INFORMATION, *PFILE_FS_FULL_SIZE_INFORMATION;

	typedef FILE_FS_FULL_SIZE_INFORMATION FileSystemSizeInfo;
    using FileSystemSizeInfoPtr=std::shared_ptr<FileSystemSizeInfo>;
}