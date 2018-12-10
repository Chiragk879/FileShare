#pragma once

#include "IAuthInfo.h"
#include "FileChangeInfo.h"

namespace IMFS
{
    class IFileSystem2
    {
    public:
        /// <summary>
        /// Find first file
        /// </summary>
        /// 
        /// <param name="path">Path</param>
        /// <param name="infoLevel">Information level type.</param>
        /// <param name="attributes">Search file attributes.</param>
        /// <param name="eaFilterData">Extended attibute filter data.</param>
        /// <param name="fileHandle">File handle</param>
        /// <param name="data">Data</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindFirstFile(ConstNormalizedPathPtr path, FindInfoLevel infoLevel, FlagsAndAttributes attributes, const ByteVector& eaFilterData,   FSFindFileHandle2Ptr& fileHandle,   FindFileInfo2Ptr& data) = 0;
        /// <summary>
        /// Find next file
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="data">Data</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindNextFile(FSFindFileHandle2& fileHandle,   FindFileInfo2Ptr& data) = 0;
        /// <summary>
        /// Find file close
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindFileClose(FSFindFileHandle2& fileHandle) = 0;
        /// <summary>
        /// Find file first bulk
        /// </summary>
        /// 
        /// <param name="path">Path</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="findInfoLevel">Find info level</param>
        /// <param name="attributes">Search file attributes.</param>
        /// <param name="eaNameList">Extended attribute name list filter.</param>
        /// <param name="fileHandle">File handle</param>
        /// <param name="filesFound">Finded files</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindFileFirstBulk(ConstNormalizedPathPtr path, int maxFileNo, FindInfoLevel findInfoLevel, FlagsAndAttributes attributes, ByteVector& eaNameList, FSFindFileHandle2Ptr& fileHandle, FindFileInfo2ArrayPtr&  filesFound) = 0;
        /// <summary>
        /// Find file next bulk
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="filesFound">Finded files</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindFileNextBulk(FSFindFileHandle2& fileHandle, uint resumeKey, int maxFileNo, FindFileInfo2ArrayPtr&  filesFound) = 0;
        /// <summary>
        /// Find file next bulk
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="maxFileNo">Maximum file number</param>
        /// <param name="filesFound">Finded files</param>
        /// <returns>Api return</returns>
        virtual ApiRet FindFileNextBulk(FSFindFileHandle2& fileHandle, ConstNormalizedPathPtr resumeFile, int maxFileNo, FindFileInfo2ArrayPtr&  filesFound) = 0;
        /// <summary>
        /// Create directory
        /// </summary>
        /// 
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual ApiRet CreateDirectory(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Rename
        /// </summary>
        /// 
        /// <param name="oldFileName">Old file name</param>
        /// <param name="newFileName">New file name</param>
        /// <returns>Api return</returns>
        virtual ApiRet Rename(FsFileHandle2& fileHandle, ConstNormalizedPathPtr newFileName, bool forcedRename) = 0;
        /// <summary>
        /// Create file
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="desiredAccess">Desired access</param>
        /// <param name="shareMode">Share mode</param>
        /// <param name="creationDisposition">Creation disposition</param>
        /// <param name="flagsAndAttributes">Flags and attributes</param>
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual ApiRet CreateFile(ConstNormalizedPathPtr fileName, DesiredAccess desiredAccess,
            ShareMode shareMode, CreationDisposition creationDisposition, FlagsAndAttributes flagsAndAttributes,
            FsFileHandle2Ptr& fileHandle) = 0;
        /// <summary>
        /// Read file
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="buffer">Buffer</param>
        /// <param name="bytesToRead">Bytes to read</param>
        /// <param name="bytesRead">Bytes read</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual ApiRet ReadFile(FsFileHandle2& fileHandle, WriteOnlyArray<byte>& buffer, uint bytesToRead,   uint& bytesRead, unsigned __int64 offset) = 0;
        /// <summary>
        /// Write file
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="buffer">Buffer</param>
        /// <param name="numberOfBytesToWrite">Number of bytes to write</param>
        /// <param name="numberOfBytesWritten">Number of bytes written</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual ApiRet WriteFile(FsFileHandle2& fileHandle, const ReadOnlyArray<byte>& buffer, uint numberOfBytesToWrite,   uint& numberOfBytesWritten, unsigned __int64 offset) = 0;

        /// <summary>
        /// Get file information by handle
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileInfo">File info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileInformationByHandle(FsFileHandle2& fileHandle, FileInformationPtr& fileInfo) = 0;
        /// <summary>
        /// Get file attributes
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileAttributeData">File attribute data</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileAttributes(ConstNormalizedPathPtr fileName, FileAttributeDataPtr& fileAttributeData) = 0;
        /// <summary>
        /// Close file
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="doUpload">Indicates that upload to DMS should be done.</param>
        /// <returns>Api return</returns>
        virtual ApiRet CloseFile(FsFileHandle2& fileHandle, bool doUpload) = 0;
        /// <summary>
        /// Get file access info
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileAccessInfo">File access info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileAccessMask(ConstNormalizedPathPtr fileName, FileAccessInfoPtr& fileAccessInfo) = 0;
        /// <summary>
        /// Get all versions of a file
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileVersions">Vector containing file version info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileVersions(ConstNormalizedPathPtr fileName, std::vector<std::shared_ptr<FileVersionInfo>>& fileVersions) = 0;
        /// <summary>
        /// Get disk free space
        /// </summary>
        /// 
        /// <param name="fileSystemSizeInfo">File system size info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetDiskFreeSpace(FileSystemSizeInfoPtr& fileSystemSizeInfo) = 0;
        /// <summary>
        /// Delete file
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <returns>Api return</returns>
        virtual ApiRet DeleteFile(ConstNormalizedPathPtr fileName) = 0;
        /// <summary>
        /// Get volume information
        /// </summary>
        /// 
        /// <param name="volumeInfo">Volume info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetVolumeInformation(VolumeInformationPtr& volumeInfo) = 0;
        /// <summary>
        /// Set end of file
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetEndOfFile(FsFileHandle2& fileHandle, unsigned __int64 offset) = 0;
        /// <summary>
        /// Set file allocaiton size
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="offset">Offset</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetAllocationSize(FsFileHandle2& fileHandle, uint64_t offset) = 0;
        /// <summary>
        /// Delete directory
        /// </summary>
        /// 
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual ApiRet DeleteDirectory(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Special service method to delete directory without any checks
        /// </summary>
        /// 
        /// <param name="directoryName">Directory name</param>
        /// <returns>Api return</returns>
        virtual ApiRet DeleteDirectoryNoChecks(ConstNormalizedPathPtr directoryName) = 0;
        /// <summary>
        /// Unlock file
        /// </summary>
        /// 
        /// <param name="file">File</param>
        /// <param name="pid">Pid</param>
        /// <param name="offset">Offset</param>
        /// <param name="length">Length</param>
        /// <returns>Api return</returns>        
        virtual ApiRet UnLockFile(FsFileHandle2& file, std::vector<LockRange>& unlocks) = 0;
        /// <summary>
        /// Lock file
        /// </summary>
        /// <returns>Api return</returns>
        virtual ApiRet LockFile(FsFileHandle2& file, std::vector<SmbLockRange>& locks) = 0;

        virtual ApiRet AcquireFileLease(FsFileHandle2& file,
                                        uint32_t& leaseStatus, 
                                        std::function<uint32_t(uint32_t leaseStatus, bool waitLeaseStatus)> callback,
                                        uint64_t& leaseId,
                                        uint64_t parentLeaseId = 0) = 0;
        virtual ApiRet ReleaseFileLease(FsFileHandle2& file, uint64_t leaseId) = 0;
        virtual ApiRet CheckLeaseOnFileOplock(FsFileHandle2& file, uint8_t oplockLevel) = 0;
        virtual ApiRet SetFileOplock(FsFileHandle2& file, uint8_t& oplockLevel, std::function<uint8_t(uint8_t oplockLevel)> callback) = 0;

        /// <summary>
        /// Flush
        /// </summary>
        /// 
        /// <param name="file">File</param>
        /// <returns>Api return</returns>
        virtual ApiRet Flush(FsFileHandle2& file) = 0;
        /// <summary>
        /// Register file watcher
        /// </summary>
        /// 
        /// <param name="directoryPath">Directory path</param>
        /// <param name="filter">Filter</param>
        /// <param name="watchSubtree">If need to watch subtree</param>
        /// <param name="notifyObject">Notify object</param>
        /// <param name="watcherHandle">Watcher handle</param>
        /// <returns>Api return</returns>
        virtual ApiRet RegisterFileWatcher(FsFileHandle2& fileHandle, CompletionFilter filter, bool watchSubtree, std::function<void()> callback, uint64_t& watchId, std::list<VfsFileChangeInfo>& changes) = 0;
        /// <summary>
        /// Close file watcher
        /// </summary>
        /// 
        ///
        /// <param name="watcherHandle">Watcher handle</param>
        /// <returns>Api return</returns>
        virtual ApiRet CloseFileWatcher(uint64_t watchId) = 0;

        virtual ApiRet ReadFileWatcher(uint64_t watchId, std::list<VfsFileChangeInfo>& changes) = 0;

        /// <summary>
        /// Get file streams
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="streams">Streams</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileStreams(FsFileHandle2& fileHandle,   std::vector<DataStreamInfo>& streams) = 0;
        /// <summary>
        /// Get file streams
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="streams">Streams</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileStreams(ConstNormalizedPathPtr fileName,   std::vector<DataStreamInfo>& streams) = 0;
        /// <summary>
        /// Set file attributes
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileAttributes">File attributes</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFileAttributes(ConstNormalizedPathPtr fileName, uint fileAttributes) = 0;
        /// <summary>
        /// Set file time
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="creationTime">Creation time</param>
        /// <param name="lastAccessTime">Last access time</param>
        /// <param name="lastWriteTime">Last write time</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFileTime(FsFileHandle2& fileHandle, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime) = 0;
        /// <summary>
        /// Set file time
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="creationTime">Creation time</param>
        /// <param name="lastAccessTime">Last access time</param>
        /// <param name="lastWriteTime">Last write time</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFileTime(ConstNormalizedPathPtr fileName, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime) = 0;
        /// <summary>
        /// Create temporary file
        /// </summary>
        /// 
        /// <param name="pathName">Path name</param>
        /// <param name="desiredAccess">Desired access</param>
        /// <param name="shareMode">Share mode</param>
        /// <param name="creationDisposition">Creation disposition</param>
        /// <param name="flagsAndAttributes">Flags and attributes</param>
        /// <param name="tempFileName">Temp file name</param>
        /// <param name="fileHandle">File handle</param>
        /// <returns>Api return</returns>
        virtual ApiRet CreateTemporaryFile(ConstNormalizedPathPtr pathName, DesiredAccess desiredAccess,
            ShareMode shareMode, CreationDisposition creationDisposition, FlagsAndAttributes flagsAndAttributes,   ConstNormalizedPathPtr& tempFileName, FsFileHandle2Ptr& fileHandle) = 0;
        /// <summary>
        /// Get short path name
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="shortName">Short file name</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetShortPathName(FsFileHandle2& fileHandle, FileNameInfoPtr& nameInfo) = 0;
        /// <summary>
        /// Get file extended attribute data
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>        
        /// <param name="eaData">Extended attributes data</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileEAData(FsFileHandle2& fileHandle, ByteVectorPtr& eaData) = 0;
        /// <summary>
        /// Get file extended attribute data
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>        
        /// <param name="eaData">Extended attributes data</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileEAData(ConstNormalizedPathPtr fileName,   ByteVectorPtr& eaData) = 0;
        /// <summary>
        /// Set file extended attribute data
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="eaData">Extended attribute data</param>
        /// /// <returns>Api return</returns>
        virtual ApiRet SetFileEAData(FsFileHandle2& fileHandle, const ByteVector& eaData) = 0;
        /// <summary>
        /// Set file extended attribute data
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="eaData">Extended attribute data</param>
        /// /// <returns>Api return</returns>
        virtual ApiRet SetFileEAData(ConstNormalizedPathPtr fileName, const ByteVector& eaData) = 0;
        /// <summary>
        /// Get file system object id
        /// </summary>
        /// 
        ///
        /// <param name="fileSystemObjectIdInfo">File system object id info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileSystemObjectId(FsFileHandle2& fileHandle, FileSystemObjectIdInfoPtr& fileSystemObjectIdInfo) = 0;
        /// <summary>
        /// Get file system attribute info
        /// </summary>
        /// 
        /// <param name="fileSystemAttributeInfo">File system attribute info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileSystemAttributeInfo(FileSystemAttributeInformationPtr& fileSystemAttributeInfo) = 0;
        /// <summary>
        /// Get file system volume
        /// </summary>
        /// 
        /// <param name="fileSystemVolume">File system volume</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileSystemVolume(FileSystemVolumePtr& fileSystemVolume) = 0;
        /// <summary>
        /// Get file system device info
        /// </summary>
        /// 
        /// <param name="fileSystemDeviceInfo">File system device info</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileSystemDeviceInfo(FileSystemDeviceInfoPtr& fileSystemDeviceInfo) = 0;
        /// <summary>
        /// Get file alignment info
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="alignmentRequirement">Alignment requirement</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileAlignmentInfo(FsFileHandle2& fileHandle, AlignmentRequirement& alignmentRequirement) = 0;
        /// <summary>
        /// Set the file pointer
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="distanceToMove">The distance to move the pointer</param>
        /// <param name="moveMethod">The move method</param>
        /// /// <param name="newPosition">The new offset from the beginning of the file</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFilePointer(FsFileHandle2& fileHandle, __int64 distanceToMove, uint moveMethod,   __int64& newPosition) = 0;
        /// <summary>
        /// Get file information by handle extended
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="informationLevelClass">File information level class</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual ApiRet GetFileInformationByHandleEx(FsFileHandle2& fileHandle,
            FileInfoByHandleClass informationLevelClass,   IFileInformationLevelPtr& fileInformationLevel) = 0;
        /// <summary>
        /// Set file information by handle
        /// </summary>
        /// 
        /// <param name="fileHandle">File handle</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFileInformationByHandle(FsFileHandle2& fileHandle, const IFileInformationLevel& fileInformationLevel) = 0;
        /// <summary>
        /// Set file information by name
        /// </summary>
        /// 
        /// <param name="fileName">File name</param>
        /// <param name="fileInformationLevel">File information level</param>
        /// <returns>Api return</returns>
        virtual ApiRet SetFileInformationByName(ConstNormalizedPathPtr fileName, const IFileInformationLevel& fileInformationLevel) = 0;

        /// Does initialization of underlying object store and authentication.
        virtual ApiRet OnTreeConnect(std::shared_ptr<IAuthInfo> userContext) = 0;

        /// Invalidates cache at specified location.
        virtual ApiRet InvalidatePathCache(ConstNormalizedPathPtr path) = 0;

        ///
        /// Notifies that a delayed delete has expired and the file should be deleted
        /// permanently
        ///
        virtual ApiRet OnDelayedDelete(const IManID& id) = 0;
    public:
        IFileSystem2();
        virtual ~IFileSystem2();
    };

}