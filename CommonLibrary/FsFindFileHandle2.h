#pragma once

namespace IMFS
{
    /// <summary>
    /// The filesystem file handle
    /// </summary>
    class FSFindFileHandle2
    {
		public:
			FSFindFileHandle2();
			~FSFindFileHandle2();

			ConstNormalizedPathPtr GetPath() const;
			void SetPath(ConstNormalizedPathPtr value);

			Folder2& GetSearchFolder();
			void SetSearchFolder(Folder2& folder);

			FindInfoLevel GetInfoLevel() const;
			void SetInfoLevel(FindInfoLevel value);

			const std::vector<byte>& GetEaFilterData() const;
			void SetEaFilterData(const std::vector<byte>& value);

			FlagsAndAttributes GetSearchAttributes() const;
			void SetSearchAttributes(FlagsAndAttributes value);

		public:
			const string& ToString();

		private:
			ConstNormalizedPathPtr path;
			FindInfoLevel infoLevel;
			std::vector<byte> eaFilterData;
			FlagsAndAttributes searchAttributes;
			Folder2 searchFolder;
			string mystring;

			FSFindFileHandle2(const FSFindFileHandle2& copy); // not allowed
    };
    using FSFindFileHandle2Ptr=std::shared_ptr<FSFindFileHandle2>;
}