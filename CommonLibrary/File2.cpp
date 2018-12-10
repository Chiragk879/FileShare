#include "stdafx.h"

using namespace IMFS;

File2::File2() : m_pFileName(NULL)
{
    m_CreationTime.QuadPart = 0;
    m_LastAccessTime.QuadPart = 0;
    m_LastWriteTime.QuadPart = 0;
    m_ChangeTime.QuadPart = 0;
    m_FileAttributes = 0;
    m_AllocationSize.QuadPart = 0;
    m_EndOfFile.QuadPart = 0;
    m_NumberOfLinks = 0;
    m_DeletePending = FALSE;
    m_Directory = FALSE;
    m_ReparseTag = 0;
    m_DeleteFile = FALSE;
    m_EaSize = 0;
    m_PriorityHint = MaximumIoPriorityHintType;
    m_IsImaginaryFolder = FALSE;
    m_AccessRights = 0;
    m_DMSAccessRights = 0;

}

File2::File2(ConstNormalizedPathPtr pFileName_) : m_pFileName(pFileName_)
{
    m_CreationTime.QuadPart = 0;
    m_LastAccessTime.QuadPart = 0;
    m_LastWriteTime.QuadPart = 0;
    m_ChangeTime.QuadPart = 0;
    m_FileAttributes = 0;
    m_AllocationSize.QuadPart = 0;
    m_EndOfFile.QuadPart = 0;
    m_NumberOfLinks = 0;
    m_DeletePending = FALSE;
    m_Directory = FALSE;
    m_ReparseTag = 0;
    m_DeleteFile = FALSE;
    m_EaSize = 0;
    m_PriorityHint = MaximumIoPriorityHintType;
    m_IsImaginaryFolder = FALSE;
    m_AccessRights = 0;
    m_DMSAccessRights = 0;
}

File2 :: ~File2(void)
{
}

File2::File2(const File2& x_)
{
    SetFrom(x_);
}

File2& File2 :: operator=(const File2& x_)
{
    if (&x_ == this)
        return *this;
    SetFrom(x_);
    // Copy streams only when operator= called, since SetFrom is called to sync handle, which
    // may have incomplete information
    m_streams = x_.GetStreams();
    return *this;
}

void File2::SetFrom(const File2& file2_)
{
    m_pFileName = file2_.GetFileName();
    m_IManID = file2_.GetIManID();
    m_CreationTime = file2_.GetCreationTime();
    m_LastAccessTime = file2_.GetLastAccessTime();
    m_LastWriteTime = file2_.GetLastWriteTime();
    m_ChangeTime = file2_.GetChangeTime();
    m_FileAttributes = file2_.GetFileAttributes();
    m_AllocationSize = file2_.GetAllocationSize();
    m_EndOfFile = file2_.GetEndOfFile();
    m_NumberOfLinks = file2_.GetNumberOfLinks();
    m_DeletePending = file2_.GetDeletePending();
    m_Directory = file2_.IsDirectory();
    m_ReparseTag = file2_.GetReparseTag();
    m_DeleteFile = file2_.GetDeleteFile();
    m_EaSize = file2_.GetEaSize();
    m_PriorityHint = file2_.GetPriorityHint();
    m_IsImaginaryFolder = file2_.GetIsImaginaryFolder();
    m_AccessRights = file2_.GetAccessRights();
    m_DMSAccessRights = file2_.GetDMSAccessRights();
}

void File2::RenameInsideDataProvider(ConstNormalizedPathPtr pNewName_)
{
    m_pFileName = pNewName_;
}

void File2::SetFileAttributes(DWORD FileAttributes_)
{
    if ((m_FileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
    {
        // don't allow the directory attribute to be turned off
        FileAttributes_ = FileAttributes_ | FILE_ATTRIBUTE_DIRECTORY;
    }

    m_FileAttributes = FileAttributes_;
}

void File2::SetAlwaysAccessRights(DWORD& dwMask)
{
    dwMask = FILE_READ_DATA |                // If you can see the profile, in DMS, that means you can always read it
        FILE_READ_EA |                  // Always allowed b/c we don't support EA
        FILE_WRITE_EA |                 // Always allowed b/c we don't support EA
        FILE_EXECUTE |                  // Always on b/c the flag has no meaning to us
        FILE_READ_ATTRIBUTES |          // Always allow attributes to be read
        FILE_WRITE_ATTRIBUTES |         // Always allow attributes to be written (since they are ignored anyway)
        READ_CONTROL |                  // Always allow
        //DELETE|					   // Always allow (for Office 2007 compatibility); let the DMS enforce delete permission //removed to enforce no delete on fileshare
        SYNCHRONIZE;                   // Always allow
}

void File2::SetGenericRights(DWORD& dwMask)
{
    // GENERIC_READ
    DWORD geMask = (FILE_READ_ATTRIBUTES | FILE_READ_DATA | FILE_READ_EA | STANDARD_RIGHTS_READ | SYNCHRONIZE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_READ;
    }

    // GENERIC_WRITE
    geMask = (FILE_APPEND_DATA | FILE_WRITE_ATTRIBUTES | FILE_WRITE_DATA | FILE_WRITE_EA | STANDARD_RIGHTS_WRITE | SYNCHRONIZE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_WRITE;
    }

    // GENERIC_EXECUTE
    geMask = (FILE_EXECUTE | FILE_READ_ATTRIBUTES | STANDARD_RIGHTS_EXECUTE | SYNCHRONIZE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_EXECUTE;
    }

    // GENERIC_ALL
    geMask = (GENERIC_WRITE | GENERIC_READ | GENERIC_EXECUTE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_ALL;
    }
}


void File2::SetIsImaginaryFolder(BOOLEAN value)
{
    m_IsImaginaryFolder = value;
}

BOOLEAN File2::GetIsImaginaryFolder() const
{
    return m_IsImaginaryFolder;
}

bool File2::IsRecentlyCreated() const
{
    return (m_EndOfFile.QuadPart == 0 && m_AllocationSize.QuadPart == 0);
}

string File2::FileAccessRightsToString(DWORD mask)
{
    string result;
    string or(L"|");

    if (mask == 0)
    {
        result = L"NO ACCESS";
    }
    else
    {
        if ((mask & GENERIC_READ) == GENERIC_READ)
        {
            if (!result.empty()) result.append(or);
            result.append(L"GENERIC_READ");
        }
        if ((mask & GENERIC_WRITE) == GENERIC_WRITE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"GENERIC_WRITE");
        }
        if ((mask & GENERIC_EXECUTE) == GENERIC_EXECUTE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"GENERIC_EXECUTE");
        }
        if ((mask & GENERIC_ALL) == GENERIC_ALL)
        {
            if (!result.empty()) result.append(or);
            result.append(L"GENERIC_ALL");
        }
        if ((mask & ACCESS_SYSTEM_SECURITY) == ACCESS_SYSTEM_SECURITY)
        {
            if (!result.empty()) result.append(or);
            result.append(L"ACCESS_SYSTEM_SECURITY");
        }
        if ((mask & DELETE) == DELETE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"DELETE");
        }
        if ((mask & READ_CONTROL) == READ_CONTROL)
        {
            if (!result.empty()) result.append(or);
            result.append(L"READ_CONTROL");
        }
        if ((mask & WRITE_DAC) == WRITE_DAC)
        {
            if (!result.empty()) result.append(or);
            result.append(L"WRITE_DAC");
        }
        if ((mask & SYNCHRONIZE) == SYNCHRONIZE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"SYNCHRONIZE");
        }
        if ((mask & FILE_WRITE_ATTRIBUTES) == FILE_WRITE_ATTRIBUTES)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_WRITE_ATTRIBUTES");
        }
        if ((mask & FILE_READ_ATTRIBUTES) == FILE_READ_ATTRIBUTES)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_READ_ATTRIBUTES");
        }
        if ((mask & FILE_DELETE_CHILD) == FILE_DELETE_CHILD)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_DELETE_CHILD");
        }
        if ((mask & WRITE_OWNER) == WRITE_OWNER)
        {
            if (!result.empty()) result.append(or);
            result.append(L"WRITE_OWNER");
        }
        if ((mask & FILE_EXECUTE) == FILE_EXECUTE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_EXECUTE");
        }
        if ((mask & FILE_WRITE_EA) == FILE_WRITE_EA)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_WRITE_EA");
        }
        if ((mask & FILE_READ_EA) == FILE_READ_EA)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_READ_EA");
        }
        if ((mask & FILE_APPEND_DATA) == FILE_APPEND_DATA)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_APPEND_DATA");
        }
        if ((mask & FILE_WRITE_DATA) == FILE_WRITE_DATA)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_WRITE_DATA");
        }
        if ((mask & FILE_READ_DATA) == FILE_READ_DATA)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_READ_DATA");
        }
    }
    return result;
}
