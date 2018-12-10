#pragma once

namespace IMFS
{
    /// <summary>
    /// File system attribute information
    /// </summary>
    typedef struct _FileSystemAttributeInformation
    {        
        /// <summary>
        /// File System Attributes
        /// </summary>
		uint FileSystemAttributes;

        /// <summary>
        /// Maximum length of each file name component in number of bytes
        /// </summary>
		uint LabelLength;

        /// <summary>
        /// Length, in bytes, of the name of the file system
        /// </summary>
		int MaxNameLength;

        /// <summary>
        /// Name of the file system
        /// </summary>
		string FileSystemName;

		_FileSystemAttributeInformation()
		{
			FileSystemAttributes = 0;
			LabelLength = 0;
			MaxNameLength = 0;
		}

	} FileSystemAttributeInformation;
    using FileSystemAttributeInformationPtr=std::shared_ptr<FileSystemAttributeInformation>;
}