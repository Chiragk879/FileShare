#pragma once

namespace IMFS
{
    /// <summary>
    /// Virtual file system interface
    /// </summary>
    class IVfs2
    {
    public:
        /// <summary>
        /// Find first file
        /// </summary>
        /// 
        ///
        /// <param name="path">Path</param>
        /// <param name="findInfoLevel">Find information level type.</param>
        /// <param name="attributes">Search file attibutes.</param>
        /// <param name="eaNameList">Extended attributes name list filter.</param>
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileFoundInfo">Founf file information.</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindFirstFile(ConstNormalizedPathPtr path, FindInfoLevel findInfoLevel, FlagsAndAttributes attributes, std::vector<byte>& eaNameList,  VfsFindFileHandlePtr& fileHandle,  FindFileInfo2Ptr& fileFoundInfo) = 0;
        /// <summary>
        /// Find next file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileFoundInfo">Data</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindNextFile(VfsFindFileHandle& fileHandle,  FindFileInfo2Ptr& fileFoundInfo) = 0;
        /// <summary>
        /// Find file close
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindFileClose(VfsFindFileHandle& fileHandle) = 0;
        /// <summary>
        /// Find first file bulk
        /// </summary>
        /// 
        ///
        /// <param name="path">Path</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="findInfoLevel">Find info level</param>
        /// <param name="attributes">Search file attibutes.</param>
        /// <param name="eaNameList">Extended attributes name list filter.</param>
        /// <param name="fileHandle">File handle</param>
        /// <param name="filesFound">Files found</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindFirstFileBulk(ConstNormalizedPathPtr path, int maxFileNo, FindInfoLevel findInfoLevel, FlagsAndAttributes attributes, std::vector<byte>& eaNameList,  VfsFindFileHandlePtr& fileHandle, FindFileInfo2ArrayPtr& filesFound) = 0;
        /// <summary>
        /// Find file next bulk
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="filesFound">Files found</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindFileNextBulk(VfsFindFileHandle& fileHandle, uint resumeKey, int maxFileNo, FindFileInfo2ArrayPtr& filesFound) = 0;
        /// <summary>
        /// Find file next bulk
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="filesFound">Files found</param>
        /// <returns>Api return</returns>
        virtual NtStatus FindFileNextBulk(VfsFindFileHandle& fileHandle, ConstNormalizedPathPtr resumeFile, int maxFileNo, FindFileInfo2ArrayPtr& filesFound) = 0;
        /// <summary>
        /// Create directory
        /// </summary>
        /// 
        ///
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual NtStatus CreateDirectory(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Rename
        /// </summary>
        /// 
        ///
        /// <param name="oldFileName">Old file name</param>
        /// <param name="newFileName">New file name</param>
        /// <returns>Api return</returns>
        virtual NtStatus Rename(VfsFileHandle& fileHandle, ConstNormalizedPathPtr newFileName, bool forcedRename) = 0;
        /// <summary>
        /// Create file
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="desiredAccess">Desired access</param>
        /// <param name="shareMode">Share mode</param>
        /// <param name="creationDisposition">Creation disposition</param>
        /// <param name="flagsAndAttributes">Flags and attributes</param>
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus CreateFile(ConstNormalizedPathPtr fileName, DesiredAccess desiredAccess, ShareMode shareMode, CreationDisposition creationDisposition, FlagsAndAttributes flagsAndAttributes, VfsFileHandlePtr& fileHandle) = 0;
        /// <summary>
        /// Read file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="buffer">Buffer</param>
        /// <param name="bytesToRead">Bytes to read</param>
        /// <param name="bytesRead">Bytes read</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual NtStatus ReadFile(VfsFileHandle& fileHandle, WriteOnlyArray<byte>& buffer, uint bytesToRead,  uint& bytesRead, ulong64 offset) = 0;
        /// <summary>
        /// Write file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="buffer">Buffer</param>
        /// <param name="numberOfBytesToWrite">Number of bytes to write</param>
        /// <param name="numberOfBytesWritten">Number of bytes written</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual NtStatus WriteFile(VfsFileHandle& fileHandle, const ReadOnlyArray<byte>& buffer, uint numberOfBytesToWrite,  uint& numberOfBytesWritten, ulong64 offset) = 0;
        /// <summary>
        /// Get file information by handle
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileInfo">File info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileInformationByHandle(VfsFileHandle& fileHandle, FileInformationPtr& fileInfo) = 0;
        /// <summary>
        /// Get file attributes
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="fileAttributeData">File attribute data</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileAttributes(ConstNormalizedPathPtr fileName, FileAttributeDataPtr& fileAttributeData) = 0;
        /// <summary>
        /// Get file access info
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileAccessInfo">File access info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileAccessMask(ConstNormalizedPathPtr fileName, FileAccessInfoPtr& fileAccessInfo) = 0;
        /// <summary>
        /// Get all versions of a file
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileVersions">Vector containing file version info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileVersions(ConstNormalizedPathPtr fileName, std::vector<std::shared_ptr<FileVersionInfo>>& fileVersions) = 0;
        /// <summary>
        /// Close file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="doUpload">Indicates that upload to DMS should be done.</param>
        /// <returns>Api return</returns>
        virtual NtStatus CloseFile(VfsFileHandle& fileHandle, bool doUpload) = 0;
        /// <summary>
        /// Get disk free space
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemSizeInfo">File system size info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetDiskFreeSpace(FileSystemSizeInfoPtr& fileSystemSizeInfo) = 0;
        /// <summary>
        /// Delete file
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <returns>Api return</returns>
        virtual NtStatus DeleteFile(ConstNormalizedPathPtr fileName) = 0;
        /// <summary>
        /// Get volume information
        /// </summary>
        /// 
        ///
        /// <param name="volumeInfo">Volume info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetVolumeInformation(VolumeInformationPtr& volumeInfo) = 0;
        /// <summary>
        /// Set end of file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetEndOfFile(VfsFileHandle& fileHandle, ulong64 offset) = 0;
        /// <summary>
        /// Set file allocaiton size
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetAllocationSize(VfsFileHandle& fileHandle, uint64_t offset) = 0;
        /// <summary>
        /// Delete directory
        /// </summary>
        /// 
        ///
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual NtStatus DeleteDirectory(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Special service method to delete directory without any checks
        /// </summary>
        /// 
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual NtStatus DeleteDirectoryNoChecks(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Lock file
        /// </summary>
        /// <returns>Api return</returns>
        virtual NtStatus LockFile(VfsFileHandle& fileHandle, std::vector<SmbLockRange>& locks) = 0;

        /// callback - Receives LeaseStatus, and returns final status after ChangeNotify Acknolegement or timeout
        virtual NtStatus AcquireFileLease(VfsFileHandle& fileHandle,
                                          uint32_t& leaseStatus,
                                          std::function<uint32_t(uint32_t leaseStatus, bool waitLeaseStatus)> callback,
                                          uint64_t& leaseId,
                                          uint64_t parentLeaseId = 0) = 0;
        virtual NtStatus ReleaseFileLease(VfsFileHandle& fileHandle, uint64_t leaseId) = 0;
        virtual NtStatus CheckLeaseOnFileOplock(VfsFileHandle& fileHandle, uint8_t oplockLevel) = 0;
        virtual NtStatus SetFileOplock(VfsFileHandle& fileHandle, uint8_t& oplockLevel, std::function<uint8_t(uint8_t oplockLevel)> callback) = 0;

        /// <summary>
        /// Unlock file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="unlocks">Array with locks information</param>
        /// <returns>Api return</returns>
        virtual NtStatus UnLockFile(VfsFileHandle& fileHandle, std::vector<LockRange>& unlocks) = 0;
        /// <summary>
        /// Cancel a pending lock file
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="locks">Array with locks information</param>
        /// <returns>Api return</returns>
        virtual NtStatus CancelLockFile(VfsFileHandle& fileHandle, std::vector<LockRange>& locks) = 0;
        /// <summary>
        /// Flush
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus Flush(VfsFileHandle& fileHandle) = 0;
        /// <summary>
        /// Register file watcher
        /// </summary>
        /// 
        ///
        /// <param name="directoryPath">Directory path</param>
        /// <param name="filter">Filter</param>
        /// <param name="watchSubtree">Watch subtree</param>
        /// <param name="notifyObject">Notify object</param>
        /// <param name="watcherHandle">Watcher handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus RegisterFileWatcher(VfsFileHandle& fileHandle, CompletionFilter filter, bool watchSubtree, std::function<void()> callback, uint64_t& watchId, std::list<VfsFileChangeInfo>& changes) = 0;
        /// <summary>
        /// Close file watcher
        /// </summary>
        /// 
        ///
        /// <param name="watcherHandle">Watcher handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus CloseFileWatcher(uint64_t watchId) = 0;

        virtual NtStatus ReadFileWatcher(uint64_t watchId, std::list<VfsFileChangeInfo>& changes) = 0;

        /// <summary>
        /// Get file streams
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="streams">Streams</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileStreams(VfsFileHandle& fileHandle,  std::vector<DataStreamInfo>& streams) = 0;
        /// <summary>
        /// Get file streams
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="streams">Streams</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileStreams(ConstNormalizedPathPtr fileName,  std::vector<DataStreamInfo>& streams) = 0;
        /// <summary>
        /// Set file attributes
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="fileAttributes">File attributes</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileAttributes(ConstNormalizedPathPtr fileName, uint fileAttributes) = 0;
        /// <summary>
        /// Set file time
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="creationTime">Creation time</param>
        /// <param name="lastAccessTime">Last access time</param>
        /// <param name="lastWriteTime">Last write time</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileTime(VfsFileHandle& fileHandle, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime) = 0;
        /// <summary>
        /// Set file time
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="creationTime">Creation time</param>
        /// <param name="lastAccessTime">Last access time</param>
        /// <param name="lastWriteTime">Last write time</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileTime(ConstNormalizedPathPtr fileName, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime) = 0;
        /// <summary>
        /// Create temporary file
        /// </summary>
        /// 
        ///
        /// <param name="pathName">Path name</param>
        /// <param name="tempFileName">Temp file name</param>
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual NtStatus CreateTemporaryFile(ConstNormalizedPathPtr pathName,  ConstNormalizedPathPtr& tempFileName,  VfsFileHandlePtr& fileHandle) = 0;
        /// <summary>
        /// Get short path name
        /// </summary>
        /// 
        ///
        /// <param name="longPath">Long path</param>
        /// <param name="shortPath">Short path</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetShortPathName(VfsFileHandle& fileHandle, FileNameInfoPtr& nameInfo) = 0;
        /// <summary>
        /// Get file extended attribute data
        /// </summary>
        /// 
        ///
        /// <param name="vfsFileHandle">Vfs file handle</param>
        /// <param name="eaData">Extended attributes data</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileEAData(VfsFileHandle& vfsFileHandle,  ByteVectorPtr& eaData) = 0;
        /// <summary>
        /// Get file extended attribute data
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="eaData">Extended attributes data</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileEAData(ConstNormalizedPathPtr fileName,  ByteVectorPtr& eaData) = 0;
        /// <summary>
        /// Set file extended attribute data
        /// </summary>
        /// 
        ///
        /// <param name="vfsFileHandle">Vfs file handle</param>
        /// <param name="eaData">Extended attribute data</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileEAData(VfsFileHandle& vfsFileHandle, std::vector<byte>& eaData) = 0;
        /// <summary>
        /// Set file extended attribute data
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="eaData">Extended attribute data</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileEAData(ConstNormalizedPathPtr fileName, std::vector<byte>& eaData) = 0;
        /// <summary>
        /// Get file system object id
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemAttributeInfo">File system object id info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileSystemObjectId(VfsFileHandle& vfsFileHandle, FileSystemObjectIdInfoPtr& fileSystemObjectIdInfo) = 0;
        /// <summary>
        /// Get file system attribute info
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemAttributeInfo">File system attribute info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileSystemAttributeInfo(FileSystemAttributeInformationPtr& fileSystemAttributeInfo) = 0;
        /// <summary>
        /// Get file system volume
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemVolume">File system volume</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileSystemVolume(FileSystemVolumePtr& fileSystemVolume) = 0;
        /// <summary>
        /// Get file system device info
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemDeviceInfo">File system device info</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileSystemDeviceInfo(FileSystemDeviceInfoPtr& fileSystemDeviceInfo) = 0;
        /// <summary>
        /// Get file alignment info
        /// </summary>
        /// 
        ///
        /// <param name="vfsFileHandle">Vfs file handle</param>
        /// <param name="alignmentRequirement">Alignment requirement</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileAlignmentInfo(VfsFileHandle& vfsFileHandle,  AlignmentRequirement& alignmentRequirement) = 0;
        /// <summary>
        /// Set the file pointer
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="distanceToMove">The distance to move the pointer</param>
        /// <param name="moveMethod">The move method</param>
        /// /// <param name="newPosition">The new offset from the beginning of the file</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFilePointer(VfsFileHandle& fileHandle, signed __int64 distanceToMove, uint moveMethod,  signed __int64& newPosition) = 0;
        /// <summary>
        /// Sends a control code directly to a specified device driver, causing the corresponding device to perform the corresponding operation.
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="controlCode">The control code for the operation. This value identifies the specific operation to be performed and the type of device on which to perform it.</param>
        /// <param name="isFSCtl">File System control</param>
        /// <param name="input">Input data</param>
        /// <param name="output">Result data</param>
        /// <returns>Api return</returns>
        virtual NtStatus DeviceIO(VfsFileHandle& fileHandle, uint controlCode, bool isFSCtl, std::vector<byte>& input,  ByteVectorPtr& output) = 0;
        /// <summary>
        /// Get file information by handle exception
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="informationLevelClass">File information level class</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual NtStatus GetFileInformationByHandleEx(VfsFileHandle& fileHandle,
            FileInfoByHandleClass informationLevelClass,  IFileInformationLevelPtr& fileInformationLevel) = 0;
        /// <summary>
        /// Set file information by handle
        /// </summary>
        /// 
        ///
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileInformationByHandle(VfsFileHandle& fileHandle, IFileInformationLevel& fileInformationLevel) = 0;
        /// <summary>
        /// Set file information by name
        /// </summary>
        /// 
        ///
        /// <param name="fileName">File name</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual NtStatus SetFileInformationByName(ConstNormalizedPathPtr fileName, IFileInformationLevel& fileInformationLevel) = 0;
        /// <summary>
        /// Offers the VFS an opportunity to setup and/or reject a connection from a particular
        /// user to a particular context.
        /// </summary>
        /// 
        ///
        /// <returns>Api return</returns>
        virtual NtStatus OnTreeConnect(std::shared_ptr<IAuthInfo> authInfo) = 0;

        virtual NtStatus InvalidatePathCache(ConstNormalizedPathPtr path) = 0;

        ///
        /// Notifies VFS a delayed delete has expired and the file should be deleted
        /// permanently
        ///
        virtual NtStatus OnDelayedDelete(const IManID& id) = 0;
    public:
        virtual ~IVfs2() = default;
    };
    using IVfs2Ptr = std::shared_ptr<IVfs2>;
}