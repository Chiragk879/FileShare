#pragma once

namespace IMFS
{

    class File2 : public virtual IM::ObjectSignature
    {
    public:
        File2();
        File2(ConstNormalizedPathPtr pFileName_);
        virtual ~File2(void);
        File2(const File2& x_);
        File2& operator=(const File2& x_);

        ConstNormalizedPathPtr GetFileName() const { return m_pFileName; }
        IManID GetIManID() const { return m_IManID; }
        LARGE_INTEGER GetCreationTime() const { return m_CreationTime; }
        LARGE_INTEGER GetLastAccessTime() const { return m_LastAccessTime; }
        LARGE_INTEGER GetLastWriteTime() const { return m_LastWriteTime; }
        LARGE_INTEGER GetChangeTime() const { return m_ChangeTime; }
        DWORD GetFileAttributes() const { return m_FileAttributes; }
        LARGE_INTEGER GetAllocationSize() const { return m_AllocationSize; }
        LARGE_INTEGER GetEndOfFile() const { return m_EndOfFile; }
        DWORD GetNumberOfLinks() const { return m_NumberOfLinks; }
        BOOLEAN GetDeletePending() const { return m_DeletePending; }
        BOOLEAN IsDirectory() const { return m_Directory; }
        DWORD GetReparseTag() const { return m_ReparseTag; }
        BOOLEAN GetDeleteFile() const { return m_DeleteFile; }
        DWORD GetEaSize() const { return m_EaSize; }
        LARGE_INTEGER GetFileId() const { return GetIManID().GetID(); }
        PRIORITY_HINT GetPriorityHint() const { return m_PriorityHint; }
        BOOLEAN GetIsImaginaryFolder() const;
        DWORD GetAccessRights() const { return m_AccessRights; }
        DWORD GetDMSAccessRights() const { return m_DMSAccessRights; }
        bool IsRecentlyCreated() const;

        void SetpFileName(ConstNormalizedPathPtr pFileName_) { m_pFileName = pFileName_; }
        void SetIManID(const IManID& IManID_) { m_IManID = IManID_; }
        void SetCreationTime(const LARGE_INTEGER& CreationTime_) { m_CreationTime = CreationTime_; }
        void SetCreationTime(const FILETIME& CreationTime_) { m_CreationTime.LowPart = CreationTime_.dwLowDateTime; m_CreationTime.HighPart = CreationTime_.dwHighDateTime; }
        void SetLastAccessTime(const LARGE_INTEGER& LastAccessTime_) { m_LastAccessTime = LastAccessTime_; }
        void SetLastAccessTime(const FILETIME& LastAccessTime_) { m_LastAccessTime.LowPart = LastAccessTime_.dwLowDateTime; m_LastAccessTime.HighPart = LastAccessTime_.dwHighDateTime; }
        void SetLastWriteTime(const LARGE_INTEGER& LastWriteTime_) { m_LastWriteTime = LastWriteTime_; }
        void SetLastWriteTime(FILETIME& LastWriteTime_) { m_LastWriteTime.LowPart = LastWriteTime_.dwLowDateTime; m_LastWriteTime.HighPart = LastWriteTime_.dwHighDateTime; }
        void SetChangeTime(const LARGE_INTEGER& ChangeTime_) { m_ChangeTime = ChangeTime_; }
        void SetChangeTime(const FILETIME& ChangeTime_) { m_ChangeTime.LowPart = ChangeTime_.dwLowDateTime; m_ChangeTime.HighPart = ChangeTime_.dwHighDateTime; }
        void SetFileAttributes(DWORD FileAttributes_);
        void SetAllocationSize(const LARGE_INTEGER& AllocationSize_) { m_AllocationSize = AllocationSize_; }
        void SetAllocationSize(unsigned __int64 size) { LARGE_INTEGER t; t.QuadPart = size; m_AllocationSize = t; }
        void SetEndOfFile(const LARGE_INTEGER& EndOfFile_) { m_EndOfFile = EndOfFile_; }
        void SetEndOfFile(unsigned __int64 size) { LARGE_INTEGER t; t.QuadPart = size; m_EndOfFile = t; }
        void SetNumberOfLinks(DWORD NumberOfLinks_) { m_NumberOfLinks = NumberOfLinks_; }
        void SetDeletePending(BOOLEAN DeletePending_) { m_DeletePending = DeletePending_; }
        void SetIsDirectory(BOOLEAN Directory_) { m_Directory = Directory_; }
        void SetReparseTag(DWORD ReparseTag_) { m_ReparseTag = ReparseTag_; }
        void SetDeleteFile(BOOLEAN DeleteFile_) { m_DeleteFile = DeleteFile_; }
        void SetEaSize(DWORD EaSize_) { m_EaSize = EaSize_; }
        void SetPriorityHint(PRIORITY_HINT PriorityHint_) { m_PriorityHint = PriorityHint_; }
        void SetIsImaginaryFolder(BOOLEAN value);
        void SetAccessRights(DWORD rights) { m_AccessRights = rights; }
        void SetDMSAccessRights(DWORD rights) { m_DMSAccessRights = rights; }

        void SetFrom(const File2& file2_);

        // Streams
        void AddStream(ConstNormalizedPathPtr streamName) { m_streams.push_back(streamName); }
        void RemoveStream(ConstNormalizedPathPtr streamName) 
            { m_streams.erase(std::remove_if(m_streams.begin(), m_streams.end(), 
                              [&streamName](ConstNormalizedPathPtr fileStreamName) 
                              { return fileStreamName.get() == streamName.get(); }
                             )); }
        const std::vector<ConstNormalizedPathPtr>& GetStreams() const { return m_streams; }
        void RemoveStreams() { m_streams.clear(); }
    public:
        // don't call this unless you really really know what you're doing
        virtual void RenameInsideDataProvider(ConstNormalizedPathPtr pNewName_);

        static string FileAccessRightsToString(DWORD mask);
        static void SetAlwaysAccessRights(DWORD& dwMask);
        static void SetGenericRights(DWORD& dwMask);

    protected:
        ConstNormalizedPathPtr m_pFileName;
        IManID m_IManID;
        LARGE_INTEGER m_CreationTime;
        LARGE_INTEGER m_LastAccessTime;
        LARGE_INTEGER m_LastWriteTime;
        LARGE_INTEGER m_ChangeTime;
        DWORD m_FileAttributes;
        LARGE_INTEGER m_AllocationSize;
        LARGE_INTEGER m_EndOfFile;
        DWORD m_NumberOfLinks;
        BOOLEAN m_DeletePending;
        BOOLEAN m_Directory;
        DWORD m_ReparseTag;
        BOOLEAN m_DeleteFile;
        DWORD m_EaSize;
        PRIORITY_HINT m_PriorityHint;
        BOOLEAN m_IsImaginaryFolder;
        DWORD m_AccessRights;
        DWORD m_DMSAccessRights;
        std::vector<ConstNormalizedPathPtr> m_streams;
    };

    using File2Ptr = std::shared_ptr<File2>;
    using ConstFile2Ptr = std::shared_ptr<const File2>;
}