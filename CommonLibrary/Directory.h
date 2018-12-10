#pragma once

#include <set>

namespace IMFS
{
	class Directory
	{
		public:
			static string GetDirectoryRoot(const string& path);
			static bool Exists(const string& path);
			static bool CreateDirectory(const string& path);
			static void DeleteAllFiles(const string& path);

	};
}