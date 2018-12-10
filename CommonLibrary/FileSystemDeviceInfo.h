#pragma once

namespace IMFS
{
	// possibly undocumented or in DDK
	typedef struct _FILE_FS_DEVICE_INFORMATION 
	{
		DWORD DeviceType; // should be 7, DISK = 0x00000007
		ULONG Characteristics;  // should be 0x20
	} FILE_FS_DEVICE_INFORMATION, *PFILE_FS_DEVICE_INFORMATION;

	typedef FILE_FS_DEVICE_INFORMATION FileSystemDeviceInfo;
    using FileSystemDeviceInfoPtr=std::shared_ptr<FileSystemDeviceInfo>;
}