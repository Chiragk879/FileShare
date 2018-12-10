#pragma once

namespace IMFS
{
    /// <summary>
    /// Class that encapsulates data for information level: SMB_INFO_STANDARD
    /// </summary>
    class FindFileInfoStandard2 : public FindFileInfo2
    {
    private:
        /// <summary>
        /// Get or set the file name.
        /// </summary>
        ConstNormalizedPathPtr filename = nullptr;

        /// <summary>
        /// Get or set the resume key.
        /// </summary>
        uint32_t resumeKey = 0;

        ReturnPathNameAs pathType = ReturnPathNameAs::OriginalName;

    public:
        /// <summary>
        /// File name
        /// </summary>
        virtual ConstNormalizedPathPtr GetFileName() { return filename; }
        virtual void SetFileName(ConstNormalizedPathPtr value) { filename = value; }

        /// <summary>
        /// Resume key
        /// </summary>
        virtual uint32_t GetResumeKey() { return resumeKey; }
        virtual void SetResumeKey(uint32_t value) { resumeKey = value; }

        virtual void SetReturnPathNameAs(ReturnPathNameAs value){ pathType = value; }
        virtual ReturnPathNameAs GetReturnPathNameAs(){ return pathType; }

        // Set of accesors to the class data
        inline const FILETIME& GetCreationTime() { return CreationTime; }
        inline const FILETIME& GetLastAccessTime() { return LastAccessTime; }
        inline const FILETIME& GetLastWriteTime() { return LastWriteTime; }
        inline const FILETIME& GetChangeTime() { return LastWriteTime; }
        inline uint64_t GetAllocationSize() { return AllocationSize; }
        inline uint32_t GetFileAttributes() { return Attributes; }
        inline uint64_t GetEndOfFile() { return DataSize; }

        /// <summary>
        /// Get or set last creation time.
        /// </summary>
        FILETIME CreationTime;

        /// <summary>
        /// Get or set last access time.
        /// </summary>
        FILETIME LastAccessTime;

        /// <summary>
        /// Get or set last write time.
        /// </summary>
        FILETIME LastWriteTime;

        /// <summary>
        /// Get or set the DataSize.
        /// </summary>
        uint32_t DataSize;

        /// <summary>
        /// Get or set the AllocationSize.
        /// </summary>
        uint32_t AllocationSize;

        /// <summary>
        /// Get or set the Attributes.
        /// </summary>
        uint32_t Attributes;

        /// <summary>
        /// Get or set the short file name.
        /// </summary>
        ConstNormalizedPathPtr ShortFileName;

    public:
        FindFileInfoStandard2();
    };
    using FindFileInfoStandard2Ptr=std::shared_ptr<FindFileInfoStandard2>;

    /// <summary>
    /// Class that encapsulates data for information level: SMB_INFO_QUERY_EA_SIZE
    /// </summary>
    class FindFileInfoQueryEaSize2 : public FindFileInfoStandard2
    {
    public:
        /// <summary>
        /// Extended attribute size
        /// </summary>
        uint32_t EaSize;

    public:
        FindFileInfoQueryEaSize2();
    };
    using FindFileInfoQueryEaSize2Ptr=std::shared_ptr<FindFileInfoQueryEaSize2>;

    /// <summary>
    /// Class that encapsulates data for information level: SMB_INFO_QUERY_EAS_FROM_LIST
    /// </summary>
    class FindFileInfoQueryEasFromList2 : public FindFileInfoQueryEaSize2
    {
        /// <summary>
        /// Extended attributes data
        /// </summary>
    public:
        std::vector<byte> EaData;

    public:
        FindFileInfoQueryEasFromList2();
    };

    /// <summary>
    /// Class that encapsulates data for information level: SMB_FIND_FILE_NAMES_INFO
    /// </summary>
    class FindFileInfoNamesInfo2 : public FindFileInfo2
    {
    private:
        /// <summary>
        /// Get or set the file name.
        /// </summary>
        ConstNormalizedPathPtr filename = nullptr;

        /// <summary>
        /// Get or set the resume key.
        /// </summary>
        uint32_t resumeKey = 0;

        ReturnPathNameAs pathType = ReturnPathNameAs::OriginalName;


    public:
        /// <summary>
        /// File name
        /// </summary>
        virtual ConstNormalizedPathPtr GetFileName() { return filename; }
        virtual void SetFileName(ConstNormalizedPathPtr value) { filename = value; }

        virtual uint32_t GetResumeKey() { return resumeKey; }
        virtual void SetResumeKey(uint32_t value) { resumeKey = value; }

        virtual void SetReturnPathNameAs(ReturnPathNameAs value){ pathType = value; }
        virtual ReturnPathNameAs GetReturnPathNameAs(){ return pathType; }

        /// <summary>
        /// Get or Set file index
        /// </summary>
        uint32_t FileIndex;

    public:
        FindFileInfoNamesInfo2();
    };
    using FindFileInfoNamesInfo2Ptr=std::shared_ptr<FindFileInfoNamesInfo2>;

    /// <summary>
    /// Class that encapsulates data for information level: SMB_FIND_FILE_DIRECTORY_INFO
    /// </summary>
    class FindFileInfoDirectoryInfo2 : public FindFileInfoNamesInfo2
    {
    public:
        // Set of accesors to the class data
        inline const FILETIME& GetCreationTime() { return CreationTime; }
        inline const FILETIME& GetLastAccessTime() { return LastAccessTime; }
        inline const FILETIME& GetLastWriteTime() { return LastWriteTime; }
        inline const FILETIME& GetChangeTime() { return ChangeTime; }
        inline uint64_t GetAllocationSize() { return AllocationSize; }
        inline uint32_t GetFileAttributes() { return ExtFileAttributes; }
        inline uint64_t GetEndOfFile() { return EndOfFile; }
    public:
        /// <summary>
        /// Get or set creation time.
        /// </summary>
        FILETIME CreationTime;

        /// <summary>
        /// Get or set last access time.
        /// </summary>
        FILETIME LastAccessTime;

        /// <summary>
        /// Get or set last write time.
        /// </summary>
        FILETIME LastWriteTime;

        /// <summary>
        /// Change time
        /// </summary>
        FILETIME ChangeTime;

        /// <summary>
        /// Get or set the AllocationSize.
        /// </summary>
        __int64 AllocationSize;

        /// <summary>
        /// Get or set the Attributes.
        /// </summary>
        uint32_t ExtFileAttributes;

        /// <summary>
        /// End of file
        /// </summary>
        __int64 EndOfFile;

    public:
        FindFileInfoDirectoryInfo2();
    };
    using FindFileInfoDirectoryInfo2Ptr=std::shared_ptr<FindFileInfoDirectoryInfo2>;

    /// <summary>
    /// Class that encapsulates data for information level: SMB_FIND_FILE_FULL_DIRECTORY_INFO
    /// </summary>
    class FindFileInfoFullDirectoryInfo2 : public FindFileInfoDirectoryInfo2
    {
    public:
        /// <summary>
        /// EASize
        /// </summary>
        uint32_t EaSize;

    public:
        FindFileInfoFullDirectoryInfo2();
    };
    using FindFileInfoFullDirectoryInfo2Ptr=std::shared_ptr<FindFileInfoFullDirectoryInfo2>;

    /// <summary>
    /// Class that encapsulates data for information level: SMB_FIND_FILE_BOTH_DIRECTORY_INFO
    /// </summary>
    class FindFileInfoBothDirectoryInfo2 : public FindFileInfoFullDirectoryInfo2
    {
    public:
        /// <summary>
        /// Get or Set short file name
        /// </summary>
        ConstNormalizedPathPtr ShortFileName;

    public:
        FindFileInfoBothDirectoryInfo2();
    };
    using FindFileInfoBothDirectoryInfo2Ptr=std::shared_ptr<FindFileInfoBothDirectoryInfo2>;

    /// <summary>
    /// Find file info id full directory
    /// </summary>
    class FindFileInfoIdFullDirectoryInfo2 : public FindFileInfoFullDirectoryInfo2
    {
    public:
        /// <summary>
        /// Get or Set file id
        /// </summary>
        __int64 FileId;

    public:
        FindFileInfoIdFullDirectoryInfo2();
    };
    using FindFileInfoIdFullDirectoryInfo2Ptr=std::shared_ptr<FindFileInfoIdFullDirectoryInfo2>;

    /// <summary>
    /// Find file info id both directory
    /// </summary>
    class FindFileInfoIdBothDirectoryInfo2 : public FindFileInfoBothDirectoryInfo2
    {
    public:
        /// <summary>
        /// Get or Set file id
        /// </summary>
        __int64 FileId;

    public:
        FindFileInfoIdBothDirectoryInfo2();
    };
    using FindFileInfoIdBothDirectoryInfo2Ptr=std::shared_ptr<FindFileInfoIdBothDirectoryInfo2>;
}