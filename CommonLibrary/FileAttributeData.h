#pragma once

namespace IMFS
{

    /// <summary>
    /// Contains information that the Win Api GetFileAttributesEx function retrieves.
    /// </summary>
    /// <remarks>
    /// Map to WIN32_FILE_ATTRIBUTE_DATA
    /// </remarks>        
    typedef struct _FileAttributeData : public WIN32_FILE_ATTRIBUTE_DATA
    {
    public:
        /// <summary>
        /// Is directory
        /// </summary>
        inline bool IsDirectory()
        {
            return (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
        }

        /// <summary>
        /// Is readonly
        /// </summary>
        inline bool IsReadonly()
        {
            return (dwFileAttributes & FILE_ATTRIBUTE_READONLY) != 0;
        }
    } FileAttributeData;

    using FileAttributeDataPtr = std::shared_ptr<FileAttributeData>;
}
