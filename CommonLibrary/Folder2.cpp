#include "stdafx.h"

using namespace IMFS;

Folder2::Folder2() : File2(), m_pDocuments(NULL), m_pSubfolders(NULL) { }

Folder2::Folder2(ConstNormalizedPathPtr pFileName_,
    IFile2Enumerator* pDocuments_,
    IFile2Enumerator* pSubfolders_) : File2(pFileName_)
{
    m_pDocuments = (NULL == pDocuments_) ? NULL : pDocuments_->Clone();
    m_pSubfolders = (NULL == pSubfolders_) ? NULL : pSubfolders_->Clone();
    SetIsDirectory(TRUE);
}

Folder2 :: ~Folder2(void)
{
    if (NULL != m_pDocuments) delete m_pDocuments;
    if (NULL != m_pSubfolders) delete m_pSubfolders;
}

Folder2::Folder2(const Folder2& x_) : File2(x_)
{
    m_pDocuments = (NULL == x_.m_pDocuments) ? NULL : x_.m_pDocuments->Clone();
    m_pSubfolders = (NULL == x_.m_pSubfolders) ? NULL : x_.m_pSubfolders->Clone();
    SetIsDirectory(TRUE);
}

Folder2&
Folder2 :: operator=(const Folder2& x_)
{
    if (&x_ == this) return *this;

    File2::operator=(x_);

    m_pDocuments = (NULL == x_.m_pDocuments) ? NULL : x_.m_pDocuments->Clone();
    m_pSubfolders = (NULL == x_.m_pSubfolders) ? NULL : x_.m_pSubfolders->Clone();

    return *this;
}


void Folder2::SetAlwaysAccessRights(DWORD& dwMask)
{
    // all folders have these
    dwMask = FILE_LIST_DIRECTORY |
        FILE_READ_EA |
        FILE_WRITE_EA |
        FILE_TRAVERSE |
        FILE_READ_ATTRIBUTES |
        READ_CONTROL |
        SYNCHRONIZE;
}

void Folder2::SetGenericRights(DWORD& dwMask)
{
    // GENERIC_READ
    DWORD geMask = (FILE_READ_ATTRIBUTES | FILE_LIST_DIRECTORY | FILE_READ_EA | STANDARD_RIGHTS_READ | SYNCHRONIZE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_READ;
    }

    // GENERIC_WRITE
    geMask = (FILE_ADD_SUBDIRECTORY | FILE_WRITE_ATTRIBUTES | FILE_ADD_FILE | FILE_WRITE_EA | STANDARD_RIGHTS_WRITE | SYNCHRONIZE);
    if ((dwMask & geMask) == geMask)
    {
        dwMask = dwMask | GENERIC_WRITE;
    }

    // GENERIC_EXECUTE
    geMask = (FILE_TRAVERSE | FILE_READ_ATTRIBUTES | STANDARD_RIGHTS_EXECUTE | SYNCHRONIZE);
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

bool
Folder2::IsEmpty() const
{
    return m_pDocuments->IsEmpty() && m_pSubfolders->IsEmpty();
}

void
Folder2::RenameInsideDataProvider(ConstNormalizedPathPtr pNewName_)
{
    File2::RenameInsideDataProvider(pNewName_);

    if (m_pDocuments)
        m_pDocuments->RenameInsideDataProvider(pNewName_);

    if (m_pSubfolders)
        m_pSubfolders->RenameInsideDataProvider(pNewName_);
}

string Folder2::FolderAccessRightsToString(DWORD mask)
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
        if ((mask & MAXIMUM_ALLOWED) == MAXIMUM_ALLOWED)
        {
            if (!result.empty()) result.append(or);
            result.append(L"MAXIMUM_ALLOWED");
        }
        if ((mask & ACCESS_SYSTEM_SECURITY) == ACCESS_SYSTEM_SECURITY)
        {
            if (!result.empty()) result.append(or);
            result.append(L"ACCESS_SYSTEM_SECURITY");
        }
        if ((mask & SYNCHRONIZE) == SYNCHRONIZE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"SYNCHRONIZE");
        }
        if ((mask & WRITE_OWNER) == WRITE_OWNER)
        {
            if (!result.empty()) result.append(or);
            result.append(L"WRITE_OWNER");
        }
        if ((mask & WRITE_DAC) == WRITE_DAC)
        {
            if (!result.empty()) result.append(or);
            result.append(L"WRITE_DAC");
        }
        if ((mask & READ_CONTROL) == READ_CONTROL)
        {
            if (!result.empty()) result.append(or);
            result.append(L"READ_CONTROL");
        }
        if ((mask & DELETE) == DELETE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"DELETE");
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
        if ((mask & FILE_TRAVERSE) == FILE_TRAVERSE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_TRAVERSE");
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
        if ((mask & FILE_ADD_SUBDIRECTORY) == FILE_ADD_SUBDIRECTORY)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_ADD_SUBDIRECTORY");
        }
        if ((mask & FILE_ADD_FILE) == FILE_ADD_FILE)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_ADD_FILE");
        }
        if ((mask & FILE_LIST_DIRECTORY) == FILE_LIST_DIRECTORY)
        {
            if (!result.empty()) result.append(or);
            result.append(L"FILE_LIST_DIRECTORY");
        }
    }
    return result;
}
