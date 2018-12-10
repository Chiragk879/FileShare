#include "stdafx.h"

using namespace IMFS;

bool
File::Exists(const string& name)
{
    DWORD attr = ::GetFileAttributes(name.GetString());
    if (attr == -1)
    {
        DWORD dwErr = ::GetLastError();
        if (dwErr == ERROR_FILE_NOT_FOUND || dwErr == ERROR_PATH_NOT_FOUND || dwErr == ERROR_ACCESS_DENIED)
            return false;
    }
    return true;
}

void File::Delete(const string& path)
{
    if (!::DeleteFile(path.c_str()))
    {
        IMLOG_ERROR(L"Error deleting file %s, error: %s", path, string(::GetLastError()).c_str());
    }

}
