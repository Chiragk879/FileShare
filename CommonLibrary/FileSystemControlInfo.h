#pragma once

namespace IMFS
{
    /// <summary>
    /// File system control flags.  This may be in a DDK somewhere but it isn't in
	/// Win32 API anywhere.
    /// </summary>
    typedef enum _FileSystemControlFlags
    {
        /// <summary>
        /// Content indexing is disabled.
        /// </summary>
        FILE_VC_CONTENT_INDEX_DISABLED = 0x00000008,
        /// <summary>
        /// An event log entry will be created when the user exceeds his or her assigned 
        /// disk quota limit.
        /// </summary>
        FILE_VC_LOG_QUOTA_LIMIT = 0x00000020,
        /// <summary>
        /// An event log entry will be created when the user exceeds his or her assigned 
        /// quota warning threshold.
        /// </summary>
        FILE_VC_LOG_QUOTA_THRESHOLD = 0x00000010,
        /// <summary>
        /// An event log entry will be created when the volume's free space limit 
        /// is exceeded.
        /// </summary>
        FILE_VC_LOG_VOLUME_LIMIT = 0x00000080,
        /// <summary>
        /// An event log entry will be created when the volume's free space threshold 
        /// is exceeded.
        /// </summary>
        FILE_VC_LOG_VOLUME_THRESHOLD = 0x00000040,
        /// <summary>
        /// Quotas are tracked and enforced on the volume.
        /// </summary>
        FILE_VC_QUOTA_ENFORCE = 0x00000002,
        /// <summary>
        /// Quotas are tracked on the volume, but they are not enforced. Tracked quotas 
        /// enable reporting on the file system space used by system users. If both this 
        /// field and FILE_VC_QUOTA_ENFORCE are specified, FILE_VC_QUOTA_ENFORCE is ignored.
        /// </summary>
        FILE_VC_QUOTA_TRACK = 0x00000001,
        /// <summary>
        /// The quota information for the volume is incomplete because it is corrupt, 
        /// or the system is in the process of rebuilding the quota information.
        /// </summary>
        FILE_VC_QUOTAS_INCOMPLETE = 0x00000100,
        /// <summary>
        /// The file system is rebuilding the quota information for the volume.
        /// </summary>
        FILE_VC_QUOTAS_REBUILDING = 0x00000200
    } FileSystemControlFlags;

    /// <summary>
	/// File system control info (from undocumented NtQueryVolumeInformationFile())
    /// </summary>
	typedef struct _FILE_FS_CONTROL_INFORMATION {
		LARGE_INTEGER FreeSpaceStartFiltering; 
		LARGE_INTEGER FreeSpaceThreshold; 
		LARGE_INTEGER FreeSpaceStopFiltering; 
		LARGE_INTEGER DefaultQuotaThreshold; 
		LARGE_INTEGER DefaultQuotaLimit; 
		FileSystemControlFlags FileSystemControlFlags;
	} FILE_FS_CONTROL_INFORMATION, *PFILE_FS_CONTROL_INFORMATION;

	typedef FILE_FS_CONTROL_INFORMATION FileSystemControlInfo;
}