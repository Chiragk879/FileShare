#pragma once

namespace IMFS
{
    /// <summary>
    /// Contains information that the Win Api GetFileInformationByHandle function retrieves.
    /// </summary>
    /// <remarks>
    /// Map to BY_HANDLE_FILE_INFORMATION
    /// </remarks>
    typedef struct _FileInformation : public BY_HANDLE_FILE_INFORMATION
    {
    public:
        uint nFileStatus;
    } FileInformation;
    using FileInformationPtr = std::shared_ptr<FileInformation>;

    /// <summary>
    /// File disposition info
    /// </summary>
    typedef struct _FileDispositionInfo : public FILE_DISPOSITION_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileDispositionInfo;
        }
    } FileDispositionInfo;
    using FileDispositionInfoPtr = std::shared_ptr<FileDispositionInfo>;

    /// <summary>
    /// File allocation info
    /// </summary>
    typedef struct _FileAllocationInfo : public FILE_ALLOCATION_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileAllocationInfo;
        }
    } FileAllocationInfo;
    using FileAllocationInfoPtr = std::shared_ptr<FileAllocationInfo>;

    /// <summary>
    /// File end of file info
    /// </summary>
    typedef struct _FileEndOfFileInfo : public FILE_END_OF_FILE_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileEndOfFileInfo;
        }

    } FileEndOfFileInfo;
    using FileEndOfFileInfoPtr = std::shared_ptr<FileEndOfFileInfo>;

    /// <summary>
    /// File basic info
    /// </summary>
    typedef struct _FileBasicInfo : public FILE_BASIC_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileBasicInfo;
        }
    } FileBasicInfo;
    using FileBasicInfoPtr=std::shared_ptr<IMFS::FileBasicInfo>;

    /// <summary>
    /// File standard info
    /// </summary>
    typedef struct _FileStandardInfo : public FILE_STANDARD_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>       
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileStandardInfo;
        }
    } FileStandardInfo;
    using FileStandardInfoPtr=std::shared_ptr<IMFS::FileStandardInfo>;

    /// <summary>
    /// File rename info
    /// </summary>
    typedef struct _FileRenameInfo : public FILE_RENAME_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileRenameInfo;
        }
    } FileRenameInfo;

    /// <summary>
    /// File compression info
    /// </summary>
    typedef struct _FileCompressionInfo : public FILE_COMPRESSION_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileCompressionInfo;
        }
    } FileCompressionInfo;
    using FileCompressionInfoPtr=std::shared_ptr<FileCompressionInfo>;

    /// <summary>
    /// File name info
    /// </summary>
    /// <returns>IFile information level</returns>
    typedef struct _FileNameInfo : public IFileInformationLevel
    {
        /// <summary>
        /// Information level
        /// </summary>
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileNameInfo;
        }
        string fileName;
    } FileNameInfo;
    using FileNameInfoPtr = std::shared_ptr<FileNameInfo>;

    /// <summary>
    /// File access info
    /// </summary>
    typedef struct _FILE_ACCESS_INFO
    {
        ACCESS_MASK AccessMask;
    }FILE_ACCESS_INFO, *PFILE_ACCESS_INFO;

    typedef struct _FileAccessInfo : public FILE_ACCESS_INFO, IFileInformationLevel
    {
    public:
        /// <summary>
        /// Information level
        /// </summary>       
        virtual FileInfoByHandleClass getInformationLevel() const
        {
            return FileInfoByHandleClass::FileStandardInfo;
        }
    } FileAccessInfo;
    using FileAccessInfoPtr=std::shared_ptr<FileAccessInfo>;

    /// <summary>
    /// File version info
    /// </summary>
    typedef struct _FILE_VERSION_INFO
    {
        uint32_t versionNumber;
        DATE creationDate;
        uint64_t allocationSize;
    } FILE_VERSION_INFO, *PFILE_VERSION_INFO;

    typedef struct _FileVersionInfo : public FILE_VERSION_INFO
    {
        _FileVersionInfo(long version, DATE creation, uint64_t size)
        {
            versionNumber = version;
            creationDate = creation;
            allocationSize = size;
        }
    } FileVersionInfo;
}