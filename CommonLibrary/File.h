#pragma once

namespace IMFS
{
	class File
	{
		public:
			static bool Exists(const string& fileName);
			static void Delete(const string& path);
	};
}