#include "stdafx.h"

using namespace IMFS;

// one reporter collects stats for all monitored file systems
CallReporter IFileSystem2Monitor::ms_reporter(L"IFS");

IFileSystem2Monitor::IFileSystem2Monitor(const string& fsName_, std::shared_ptr<IFileSystem2> wrapped_)
    : m_wrapped(wrapped_), m_fsName(fsName_)
{

}

IFileSystem2Monitor :: ~IFileSystem2Monitor()
{
    if (m_wrapped != nullptr)
    {
        m_wrapped.reset();
    }
}


ApiRet
IFileSystem2Monitor::FindFirstFile(ConstNormalizedPathPtr path, FindInfoLevel infoLevel, FlagsAndAttributes attributes, const ByteVector& eaFilterData,  FSFindFileHandle2Ptr& fileHandle,  FindFileInfo2Ptr& data)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"FindFirstFile");
    ret = m_wrapped->FindFirstFile(path, infoLevel, attributes, eaFilterData, fileHandle, data);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::FindNextFile(FSFindFileHandle2& fileHandle,  FindFileInfo2Ptr& data)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"FindNextFile");
    ret = m_wrapped->FindNextFile(fileHandle, data);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::FindFileClose(FSFindFileHandle2& fileHandle)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"FindFileClose");
    ret = m_wrapped->FindFileClose(fileHandle);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::FindFileFirstBulk(ConstNormalizedPathPtr path, int maxFileNo, FindInfoLevel findInfoLevel, FlagsAndAttributes attributes, ByteVector& eaNameList,  FSFindFileHandle2Ptr& fileHandle, FindFileInfo2ArrayPtr& filesFound)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"FindFileFirstBulk", path);
    ret = m_wrapped->FindFileFirstBulk(path, maxFileNo, findInfoLevel, attributes, eaNameList, fileHandle, filesFound);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::FindFileNextBulk(FSFindFileHandle2& fileHandle, uint resumeKey, int maxFileNo, FindFileInfo2ArrayPtr&  filesFound)
{
    ApiRet ret;
    string strKey((int)resumeKey);
    MethodCall call(ms_reporter, L"FindFileNextBulk", fileHandle.ToString().c_str(), strKey.c_str());
    ret = m_wrapped->FindFileNextBulk(fileHandle, resumeKey, maxFileNo, filesFound);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::FindFileNextBulk(FSFindFileHandle2& fileHandle, ConstNormalizedPathPtr resumePath, int maxFileNo, FindFileInfo2ArrayPtr&  filesFound)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"FindFileNextBulk", fileHandle.ToString().c_str(), resumePath);
    ret = m_wrapped->FindFileNextBulk(fileHandle, resumePath, maxFileNo, filesFound);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::CreateDirectory(ConstNormalizedPathPtr directoryName)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CreateDirectory", directoryName);
    ret = m_wrapped->CreateDirectory(directoryName);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::Rename(FsFileHandle2& fileHandle, ConstNormalizedPathPtr newFileName, bool forcedRename)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"Rename", newFileName);
    ret = m_wrapped->Rename(fileHandle, newFileName, forcedRename);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::CreateFile(ConstNormalizedPathPtr fileName, DesiredAccess desiredAccess,
                                ShareMode shareMode, CreationDisposition creationDisposition,
                                FlagsAndAttributes flagsAndAttributes, FsFileHandle2Ptr& fileHandle)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CreateFile", fileName);
    ret = m_wrapped->CreateFile(fileName, desiredAccess, shareMode, creationDisposition, flagsAndAttributes, fileHandle);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::ReadFile(FsFileHandle2& fileHandle, WriteOnlyArray<byte>& buffer, uint bytesToRead,  uint& bytesRead, unsigned __int64 offset)
{
    ApiRet ret;
    string strOffset((int)offset);
    string strToWrite((int)bytesToRead);
    string strparams = string::Format(L"%s at %s", (const wchar_t *)strToWrite.GetString(), (const wchar_t *)strOffset.GetString());
    MethodCall call(ms_reporter, L"ReadFile", fileHandle.ToString().c_str(), strparams.c_str());
    ret = m_wrapped->ReadFile(fileHandle, buffer, bytesToRead, bytesRead, offset);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::WriteFile(FsFileHandle2& fileHandle, const ReadOnlyArray<byte>& buffer, uint numberOfBytesToWrite,  uint& numberOfBytesWritten, unsigned __int64 offset)
{
    ApiRet ret;
    string strOffset((int)offset);
    string strToWrite((int)numberOfBytesToWrite);
    string strparams = string::Format(L"%s at %s", (const wchar_t *)strToWrite.GetString(), (const wchar_t *)strOffset.GetString());
    MethodCall call(ms_reporter, L"WriteFile", fileHandle.ToString().c_str(), strparams.c_str());
    ret = m_wrapped->WriteFile(fileHandle, buffer, numberOfBytesToWrite, numberOfBytesWritten, offset);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileInformationByHandle(FsFileHandle2& fileHandle, FileInformationPtr& fileInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileInformationByHandle", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileInformationByHandle(fileHandle, fileInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileAttributes(ConstNormalizedPathPtr fileName, FileAttributeDataPtr& fileAttributeData)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileAttributes", fileName);
    ret = m_wrapped->GetFileAttributes(fileName, fileAttributeData);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileAccessMask(ConstNormalizedPathPtr fileName, FileAccessInfoPtr& fileAccessInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileAccessMask", fileName);
    ret = m_wrapped->GetFileAccessMask(fileName, fileAccessInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::CloseFile(FsFileHandle2& fileHandle, bool doUpload)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CloseFile", fileHandle.ToString().c_str());
    ret = m_wrapped->CloseFile(fileHandle, doUpload);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileVersions(ConstNormalizedPathPtr fileName, std::vector<std::shared_ptr<FileVersionInfo>>& fileVersions)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileVersions");
    ret = m_wrapped->GetFileVersions(fileName, fileVersions);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetDiskFreeSpace(FileSystemSizeInfoPtr& fileSystemSizeInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetDiskFreeSpace");
    ret = m_wrapped->GetDiskFreeSpace(fileSystemSizeInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::DeleteFile(ConstNormalizedPathPtr fileName)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"DeleteFile", fileName);
    ret = m_wrapped->DeleteFile(fileName);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetVolumeInformation(VolumeInformationPtr& volumeInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetVolumeInformation");
    ret = m_wrapped->GetVolumeInformation(volumeInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetAllocationSize(FsFileHandle2& fileHandle, uint64_t offset)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetAllocationSize", fileHandle.ToString().c_str());
    ret = m_wrapped->SetAllocationSize(fileHandle, offset);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetEndOfFile(FsFileHandle2& fileHandle, unsigned __int64 offset)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetEndOfFile", fileHandle.ToString().c_str());
    ret = m_wrapped->SetEndOfFile(fileHandle, offset);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::DeleteDirectoryNoChecks(ConstNormalizedPathPtr directoryName)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"DeleteDirectoryNoChecks", directoryName);
    ret = m_wrapped->DeleteDirectoryNoChecks(directoryName);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::DeleteDirectory(ConstNormalizedPathPtr directoryName)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"DeleteDirectory", directoryName);
    ret = m_wrapped->DeleteDirectory(directoryName);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::UnLockFile(FsFileHandle2& file, std::vector<LockRange>& unlocks)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"UnLockFile", file.ToString().c_str());
    ret = m_wrapped->UnLockFile(file, unlocks);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::LockFile(FsFileHandle2& file, std::vector<SmbLockRange>& locks)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"LockFile", file.ToString().c_str());
    ret = m_wrapped->LockFile(file, locks);
    call.End(ret);
    return ret;
}

ApiRet IFileSystem2Monitor::AcquireFileLease(FsFileHandle2& file,
                                             uint32_t& leaseStatus,
                                             std::function<uint32_t(uint32_t leaseStatus, bool waitLeaseStatus)> callback,
                                             uint64_t& leaseId,
                                             uint64_t parentLeaseId)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"AcquireFileLease", file.ToString().c_str());
    ret = m_wrapped->AcquireFileLease(file, leaseStatus, callback, leaseId, parentLeaseId);
    call.End(ret);
    return ret;
}

ApiRet IFileSystem2Monitor::ReleaseFileLease(FsFileHandle2& file, uint64_t leaseId)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"ReleaseFileLease", file.ToString().c_str());
    ret = m_wrapped->ReleaseFileLease(file, leaseId);
    call.End(ret);
    return ret;
}

ApiRet IFileSystem2Monitor::CheckLeaseOnFileOplock(FsFileHandle2& file, uint8_t oplockLevel)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CheckLeaseOnFileOplock", file.ToString().c_str());
    ret = m_wrapped->CheckLeaseOnFileOplock(file, oplockLevel);
    call.End(ret);
    return ret;
}

ApiRet IFileSystem2Monitor::SetFileOplock(FsFileHandle2& file, uint8_t& oplockLevel, std::function<uint8_t(uint8_t oplockLevel)> callback)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileOplock", file.ToString().c_str());
    ret = m_wrapped->SetFileOplock(file, oplockLevel, callback);
    // The case when the ret == ERROR_CANCELLED it is not an error
    call.End(ret == ERROR_CANCELLED ? ERROR_SUCCESS : ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::Flush(FsFileHandle2& file)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"Flush", file.ToString().c_str());
    ret = m_wrapped->Flush(file);
    call.End(ret);
    return ret;
}

ApiRet 
IFileSystem2Monitor::RegisterFileWatcher(FsFileHandle2& file, CompletionFilter filter, bool watchSubtree, std::function<void()> callback, uint64_t& watchId, std::list<VfsFileChangeInfo>& changes)
{
    ApiRet ret;
	MethodCall call(ms_reporter, L"RegisterFileWatcher", file.ToString().c_str());
    ret = m_wrapped->RegisterFileWatcher(file, filter, watchSubtree, callback, watchId, changes);
    call.End(ret);
    return ret;
}

ApiRet 
IFileSystem2Monitor :: CloseFileWatcher(uint64_t watchId)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CloseFileWatcher", std::to_wstring(watchId).c_str());
    ret = m_wrapped->CloseFileWatcher(watchId);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::ReadFileWatcher(uint64_t watchId, std::list<VfsFileChangeInfo>& changes)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"ReadFileWatcher", std::to_wstring(watchId).c_str());
    ret = m_wrapped->ReadFileWatcher(watchId, changes);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileStreams(FsFileHandle2& fileHandle,  std::vector<DataStreamInfo>& streams)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileStreams", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileStreams(fileHandle, streams);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileStreams(ConstNormalizedPathPtr fileName,  std::vector<DataStreamInfo>& streams)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileStreams", fileName);
    ret = m_wrapped->GetFileStreams(fileName, streams);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileAttributes(ConstNormalizedPathPtr fileName, uint fileAttributes)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileAttributes", fileName);
    ret = m_wrapped->SetFileAttributes(fileName, fileAttributes);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileTime(FsFileHandle2& fileHandle, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileTime", fileHandle.ToString().c_str());
    ret = m_wrapped->SetFileTime(fileHandle, creationTime, lastAccessTime, lastWriteTime);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileTime(ConstNormalizedPathPtr fileName, FSDateTime& creationTime, FSDateTime& lastAccessTime, FSDateTime& lastWriteTime)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileTime", fileName);
    ret = m_wrapped->SetFileTime(fileName, creationTime, lastAccessTime, lastWriteTime);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::CreateTemporaryFile(ConstNormalizedPathPtr pathName, DesiredAccess desiredAccess,
ShareMode shareMode, CreationDisposition creationDisposition, FlagsAndAttributes flagsAndAttributes,  ConstNormalizedPathPtr& tempFileName,  FsFileHandle2Ptr& fileHandle)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"CreateTemporaryFile", pathName);
    ret = m_wrapped->CreateTemporaryFile(pathName, desiredAccess, shareMode, creationDisposition, flagsAndAttributes, tempFileName, fileHandle);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetShortPathName(FsFileHandle2& fileHandle, FileNameInfoPtr& nameInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetShortPathName", fileHandle.GetFileName());
    ret = m_wrapped->GetShortPathName(fileHandle, nameInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileEAData(FsFileHandle2& fileHandle,  ByteVectorPtr& eaData)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileEAData", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileEAData(fileHandle, eaData);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileEAData(ConstNormalizedPathPtr fileName,  ByteVectorPtr& eaData)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileEAData", fileName);
    ret = m_wrapped->GetFileEAData(fileName, eaData);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileEAData(FsFileHandle2& fileHandle, const ByteVector& eaData)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileEAData", fileHandle.ToString().c_str());
    ret = m_wrapped->SetFileEAData(fileHandle, eaData);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileEAData(ConstNormalizedPathPtr fileName, const ByteVector& eaData)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileEAData", fileName);
    ret = m_wrapped->SetFileEAData(fileName, eaData);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileSystemObjectId(FsFileHandle2& fileHandle, FileSystemObjectIdInfoPtr& fileSystemObjectIdInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileSystemObjectId", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileSystemObjectId(fileHandle, fileSystemObjectIdInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileSystemAttributeInfo( FileSystemAttributeInformationPtr& fileSystemAttributeInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileSystemAttributeInfo");
    ret = m_wrapped->GetFileSystemAttributeInfo(fileSystemAttributeInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileSystemVolume(FileSystemVolumePtr& fileSystemVolume)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileSystemVolume");
    ret = m_wrapped->GetFileSystemVolume(fileSystemVolume);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileSystemDeviceInfo(FileSystemDeviceInfoPtr& fileSystemDeviceInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileSystemDeviceInfo");
    ret = m_wrapped->GetFileSystemDeviceInfo(fileSystemDeviceInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileAlignmentInfo(FsFileHandle2& fileHandle,  AlignmentRequirement& alignmentRequirement)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileAlignmentInfo", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileAlignmentInfo(fileHandle, alignmentRequirement);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFilePointer(FsFileHandle2& fileHandle, __int64 distanceToMove, uint moveMethod,  __int64& newPosition)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFilePointer", fileHandle.ToString().c_str());
    ret = m_wrapped->SetFilePointer(fileHandle, distanceToMove, moveMethod, newPosition);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::GetFileInformationByHandleEx(FsFileHandle2& fileHandle,
FileInfoByHandleClass informationLevelClass,  IFileInformationLevelPtr& fileInformationLevel)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"GetFileInformationByHandleEx", fileHandle.ToString().c_str());
    ret = m_wrapped->GetFileInformationByHandleEx(fileHandle, informationLevelClass, fileInformationLevel);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileInformationByHandle(FsFileHandle2& fileHandle, const IFileInformationLevel& fileInformationLevel)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileInformationByHandle", fileHandle.ToString().c_str());
    ret = m_wrapped->SetFileInformationByHandle(fileHandle, fileInformationLevel);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::SetFileInformationByName(ConstNormalizedPathPtr fileName, const IFileInformationLevel& fileInformationLevel)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"SetFileInformationByName", fileName);
    ret = m_wrapped->SetFileInformationByName(fileName, fileInformationLevel);
    call.End(ret);
    return ret;
}

ApiRet 
IFileSystem2Monitor::OnTreeConnect(std::shared_ptr<IAuthInfo> authInfo)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"OnTreeConnect");
    ret = m_wrapped->OnTreeConnect(authInfo);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::InvalidatePathCache(ConstNormalizedPathPtr path)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"InvalidatePathCache");
    ret = m_wrapped->InvalidatePathCache(path);
    call.End(ret);
    return ret;
}

ApiRet
IFileSystem2Monitor::OnDelayedDelete(const IManID& id)
{
    ApiRet ret;
    MethodCall call(ms_reporter, L"OnDelayedDelete");
    ret = m_wrapped->OnDelayedDelete(id);
    call.End(ret);
    return ret;
}
