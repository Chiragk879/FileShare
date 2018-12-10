#pragma once

namespace IMFS
{
    typedef struct _FILE_FS_OBJECTID_INFORMATION {
        uint8_t ObjectId[16];
        uint8_t BirthVolumeId[16];
    } FILE_FS_OBJECTID_INFORMATION, *PFILE_FS_OBJECTID_INFORMATION;

    using FileSystemObjectIdInfo=FILE_FS_OBJECTID_INFORMATION;
    using FileSystemObjectIdInfoPtr = std::shared_ptr<FileSystemObjectIdInfo>;
}