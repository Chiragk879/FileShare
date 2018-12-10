
#include "stdafx.h"

using namespace IMFS;

const DWORD FILE_ALL_MASK = (
    FILE_READ_DATA              |
    FILE_WRITE_DATA             |
    FILE_APPEND_DATA            |
    FILE_READ_EA                |
    FILE_WRITE_EA               |
    // FILE_EXECUTE                |
    //n/a                       |
    FILE_READ_ATTRIBUTES        |
    FILE_WRITE_ATTRIBUTES       |
    //n/a                       |
    DELETE                      |
    READ_CONTROL                |
    //WRITE_DAC                 |
    WRITE_OWNER                 |
    SYNCHRONIZE                 |
    //n/a                       |
    //ACCESS_SYSTEM_SECURITY    |
    //MAXIMUM_ALLOWED           |
    // GENERIC_ALL                 |
    // GENERIC_EXECUTE             |
    GENERIC_WRITE               |
    GENERIC_READ);

const DWORD FOLDER_ALL_MASK(FILE_ALL_MASK & (~WRITE_OWNER));

std::atomic<uint64_t> FsFileHandle2::m_idCounter = 1;
 FsFileHandle2::FsFileHandle2() :
m_id(m_idCounter.fetch_add(1))
{
    m_contentCacheHandle = INVALID_HANDLE_VALUE;
    m_fileName = NULL;
    m_deleteOnClose = false;
    m_creationTimeAttributeModified = false;
    m_writeTimeAttributeModified = false;
    m_changeTimeAttributeModified = false;
    m_accessTimeAttributeModified = false;
    m_sizeAttributesModified = false;
    m_fileAttributesModified = false;
    m_contentModified = false;
    m_truncatedOnOpen = false;
    m_dwAccessMask = 0;
    m_desiredAccess = 0;
}

FsFileHandle2 :: ~FsFileHandle2()
{
}

void FsFileHandle2::SetContentCacheHandle(HANDLE value)
{
    m_contentCacheHandle = value;
}

HANDLE FsFileHandle2::GetContentCacheHandle() const
{
    return m_contentCacheHandle;
}

void FsFileHandle2::SetFileName(ConstNormalizedPathPtr value)
{
    m_fileName = value;
}

ConstNormalizedPathPtr  FsFileHandle2::GetFileName() const
{
    return m_fileName;
}

void FsFileHandle2::SetIManID(const IManID& id)
{
    m_imanID = id;
    if (m_imanID.IsTemporary())
    {
        if (m_imanID.isFolder())
            m_dwAccessMask = FOLDER_ALL_MASK;
        else
            m_dwAccessMask = FILE_ALL_MASK;
    }
}

const IManID& FsFileHandle2::GetIManID() const
{
    return m_imanID;
}
 FsFileHandle2::FsFileHandle2(const FsFileHandle2& copy)
{
    // not allowed
    IMFS_ASSERT(false);
}

void FsFileHandle2::SetFile(const File2& value_)
{
    m_file = value_;
}

const File2& FsFileHandle2::GetFile() const
{
    return m_file;
}

File2& FsFileHandle2::GetFile()
{
    return m_file;
}

const string& FsFileHandle2::ToString()
{
    if (m_mystring.Length() == 0 && m_fileName != NULL)
    {
        m_mystring = m_fileName->GetRelativePath();
    }
    return m_mystring;
}

bool FsFileHandle2::GetDeleteOnClose() const
{
    return m_deleteOnClose;
}

void FsFileHandle2::SetDeleteOnClose(bool value)
{
    m_deleteOnClose = value;
}

bool FsFileHandle2::GetAttributesModified() const
{
    return GetTimeAttributesModified() || GetSizeAttributesModified() || GetFileAttributesModified();
}

void FsFileHandle2::SetAttributesModified(bool value)
{
    m_creationTimeAttributeModified = m_writeTimeAttributeModified =
    m_changeTimeAttributeModified = m_accessTimeAttributeModified =
    m_sizeAttributesModified = m_fileAttributesModified = value;
}

void FsFileHandle2::SetTimeAttributesModified(bool value)
{
    m_creationTimeAttributeModified = m_writeTimeAttributeModified =
    m_changeTimeAttributeModified = m_accessTimeAttributeModified = value;
}

void FsFileHandle2::SetSizeAttributesModified(bool value)
{
    m_sizeAttributesModified = value;
}

void FsFileHandle2::SetFileAttributesModified(bool value)
{
    m_fileAttributesModified = value;
}

void FsFileHandle2::UpdateFileAttributes(File2& file)
{
    if (GetChangeTimeAttributeModified())
        file.SetChangeTime(m_file.GetChangeTime());
    if (GetCreationTimeAttributeModified())
        file.SetCreationTime(m_file.GetCreationTime());
    if (GeAccessTimeAttributeModified())
        file.SetLastAccessTime(m_file.GetLastAccessTime());
    if (GetWriteTimeAttributeModified())
        file.SetLastWriteTime(m_file.GetLastWriteTime());

    if (m_sizeAttributesModified)
    {
        file.SetEndOfFile(m_file.GetEndOfFile());
        file.SetAllocationSize(m_file.GetAllocationSize());
    }

    if (m_fileAttributesModified)
    {
        file.SetFileAttributes(m_file.GetFileAttributes());
    }
}

bool FsFileHandle2::GetContentModified() const
{
    return m_contentModified;
}

void FsFileHandle2::SetContentModified(bool value)
{
    m_contentModified = value;
}

DesiredAccess FsFileHandle2::GetDesiredAccess() const
{
    return m_desiredAccess;
}

void FsFileHandle2::SetDesiredAccess(DesiredAccess value)
{
    m_desiredAccess = value;
}

bool FsFileHandle2::DoesAccessAllowWriteAttributes() const
{
    return (m_desiredAccess & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES ||
           DoesAccessAllowContentUpdates();
}

bool FsFileHandle2::DoesAccessAllowContentUpdates() const
{
    return (
        ((m_desiredAccess & GENERIC_WRITE) == GENERIC_WRITE) ||
        ((m_desiredAccess & FILE_WRITE_DATA) == FILE_WRITE_DATA) ||
        ((m_desiredAccess & FILE_APPEND_DATA) == FILE_APPEND_DATA)
        );
}

bool FsFileHandle2::GetTruncatedOnOpen() const
{
    return m_truncatedOnOpen;
}

void FsFileHandle2::SetTruncatedOnOpen(bool value)
{
    m_truncatedOnOpen = value;
}

DWORD FsFileHandle2::GetGrantedAccessMask()
{
    return m_dwAccessMask;
}

void FsFileHandle2::SetGrantedAccessMask(DWORD value)
{
    m_dwAccessMask = value;
}

bool FsFileHandle2::IsRecentlyCreated() const
{
    return m_file.IsRecentlyCreated();
}

bool FsFileHandle2::HasDeletePermission() const
{
    return ((DELETE & m_file.GetAccessRights()) == DELETE);
}
