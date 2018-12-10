#pragma once

#include <atomic>

namespace IMFS
{
    /// <summary>
    /// The filesystem file handle
    /// </summary>
    class FsFileHandle2
    {
    public:
        FsFileHandle2();
        ~FsFileHandle2();

        void SetContentCacheHandle(HANDLE value);
        HANDLE GetContentCacheHandle() const;

        void SetFileName(ConstNormalizedPathPtr value);
        ConstNormalizedPathPtr GetFileName() const;

        void SetIManID(const IManID& id);
        const IManID& GetIManID() const;

        void SetFile(const File2& value_);
        const File2& GetFile() const;
        File2& GetFile();

        bool GetDeleteOnClose() const;
        void SetDeleteOnClose(bool value);

        bool GetAttributesModified() const;
        void SetAttributesModified(bool value);

        void SetTimeAttributesModified(bool value);
        inline bool GetTimeAttributesModified() const 
        { 
            return GetCreationTimeAttributeModified() || GetWriteTimeAttributeModified() ||
                   GetChangeTimeAttributeModified() || GeAccessTimeAttributeModified();
        }
        void SetCreationTimeAttributeModified(bool value) { m_creationTimeAttributeModified = value; }
        inline bool GetCreationTimeAttributeModified() const { return m_creationTimeAttributeModified; }
        void SetWriteTimeAttributeModified(bool value) { m_writeTimeAttributeModified = value; }
        inline bool GetWriteTimeAttributeModified() const { return m_writeTimeAttributeModified; }
        void SetChangeTimeAttributeModified(bool value) { m_changeTimeAttributeModified = value; }
        inline bool GetChangeTimeAttributeModified() const { return m_changeTimeAttributeModified; }
        void SetAccessTimeAttributeModified(bool value) { m_accessTimeAttributeModified = value; }
        inline bool GeAccessTimeAttributeModified() const { return m_accessTimeAttributeModified; }

        void SetSizeAttributesModified(bool value);
        inline bool GetSizeAttributesModified() const { return m_sizeAttributesModified; }
        void SetFileAttributesModified(bool value);
        inline bool GetFileAttributesModified() const { return m_fileAttributesModified; }

        void UpdateFileAttributes(File2& file);

        bool GetContentModified() const;
        void SetContentModified(bool value);

        DesiredAccess GetDesiredAccess() const;
        void SetDesiredAccess(DesiredAccess value);

        // true if any of the desired access bits indicate
        // an intent to write to the content
        bool DoesAccessAllowContentUpdates() const;
        // true if any of the desired access bits indicate
        // an intent to write file attributes
        bool DoesAccessAllowWriteAttributes() const;

        bool GetTruncatedOnOpen() const;
        void SetTruncatedOnOpen(bool value);

        DWORD GetGrantedAccessMask();
        void  SetGrantedAccessMask(DWORD dwMask);

        bool IsRecentlyCreated() const;
        bool HasDeletePermission() const;

        typedef uint64_t id_t;

        id_t GetId() {
            return m_id;
        }

    public:
        const string& ToString();

    private:
        HANDLE m_contentCacheHandle;
        ConstNormalizedPathPtr m_fileName;
        IManID m_imanID;
        File2 m_file;
        string m_mystring;
        bool m_deleteOnClose;
        bool m_fileAttributesModified;
        bool m_creationTimeAttributeModified;
        bool m_writeTimeAttributeModified;
        bool m_changeTimeAttributeModified;
        bool m_accessTimeAttributeModified;
        bool m_sizeAttributesModified;
        bool m_contentModified;
        bool m_truncatedOnOpen;
        DesiredAccess m_desiredAccess;
        DWORD m_dwAccessMask;

        uint64_t m_id;
        static std::atomic<uint64_t> m_idCounter;

        FsFileHandle2(const FsFileHandle2& copy); // not allowed
    };
    using FsFileHandle2Ptr=std::shared_ptr<FsFileHandle2>;
}