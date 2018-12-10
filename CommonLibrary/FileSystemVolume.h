#pragma once

namespace IMFS
{
    /// <summary>
    /// File system volume
    /// </summary>
    class FileSystemVolume
    {
    public:
        /// <summary>
        /// Volume serial number
        /// </summary>
        uint VolumeSerialNumber;

        /// <summary>
        /// Label name length
        /// </summary>
        byte LabelNameLength;

        /// <summary>
        /// Label name
        /// </summary>
        string LabelName;

    public:
        FileSystemVolume();
    };
    using FileSystemVolumePtr = std::shared_ptr<FileSystemVolume>;
}