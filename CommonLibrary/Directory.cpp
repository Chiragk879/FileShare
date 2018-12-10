#include "stdafx.h"

using namespace IMFS;

string 
Directory :: GetDirectoryRoot(const string& path)
{
	if (path.Contains(':'))
	{
		return path.Substring(0, (int) path.find_first_of(':')+1) + L"\\";
	}
	else if (path.Contains('\\'))
	{
		return path.Substring(0, (int) path.find_first_of('\\')+1);
	}
	else if (path.Contains('/'))
	{
		return path.Substring(0, (int) path.find_first_of('/')+1);
	}
	return L"";
}

bool 
Directory :: Exists(const string& path)
{
	DWORD attr = ::GetFileAttributes(path.GetString());
	if (attr == INVALID_FILE_ATTRIBUTES)
		return false;

	return ( (attr & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY );
}

bool 
Directory :: CreateDirectory(const string& path)
{
	if (Exists(path))
		return true;

	int pos = path.LastIndexOf(Path::DirectorySeparatorChar);
	if (pos != -1)
	{
		string parentPath = path.Substring(0, pos);
		if (!CreateDirectory(parentPath))
			return false;
	}

	return (TRUE == ::CreateDirectory(path.GetString(), NULL));
}

void
Directory::DeleteAllFiles(const string& dir)
{
	string allFileSearch = dir + Path::DirectorySeparatorChar + L"*";
	WIN32_FIND_DATA data;
	memset(&data, 0, sizeof(WIN32_FIND_DATA));
	HANDLE hSearch = ::FindFirstFile(allFileSearch.GetString(), &data);
	if (hSearch != INVALID_HANDLE_VALUE)
	{
		bool done = false;
		do
		{
			string fileName(data.cFileName);

			if ( (!fileName.Equals(Path::ThisDirectory)) && (!fileName.Equals(Path::ParentDirectory)) )
			{
				fileName = dir + Path::DirectorySeparatorChar + fileName;
				if ( (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != FILE_ATTRIBUTE_DIRECTORY)
				{
					::DeleteFile(fileName.GetString());
				}
				else
				{
					DeleteAllFiles(fileName.GetString()); // Delete childs
					::RemoveDirectory(fileName.GetString());
				}
			}
			done = (::FindNextFile(hSearch, &data) == FALSE);
		} while (!done);

		::FindClose(hSearch);
	}
}

