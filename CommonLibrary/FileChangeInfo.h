#pragma once

namespace IMFS
{

    /// <summary>
    /// Structure that contains details about a changed file/folder
    /// </summary>
    class FileChangeInfo2
    {
    public:
        ConstNormalizedPathPtr m_fileName;
        ConstNormalizedPathPtr m_oldFileName;

        /// Parent list, front is nearest parent folder IManID.
        std::list<int64_t> m_folderIdChain;

        uint64_t m_userId;

        /// <summary>
        /// Get/set type of change event
        /// </summary>
        COMPLETIONFILTER m_changes;

        //
        // The folder ID is the same for everyone.  The folder name may be 
        // different across different sessions / connections.
        //
        // Therefore, it doesn't make sense to use NormalizedPath here 
        // because the path name isn't the same for all receivers of this 
        // change info.
        //
        // Instead we simply pass the file name, which in this case is the 
        // last path element with no directory or stream info.
        //
        FileChangeInfo2(const std::list<int64_t> &folderIdChain,
            ConstNormalizedPathPtr fileName, ConstNormalizedPathPtr oldfileName,
            COMPLETIONFILTER changes, uint64_t userId) :
            m_fileName(fileName), m_oldFileName(oldfileName),
            m_changes(changes),
            m_folderIdChain(folderIdChain),
            m_userId(userId)
        {}
    };

    class VfsFileChangeInfo
    {
    public:
        VfsFileChangeInfo::VfsFileChangeInfo(IMFS::string fileName, uint32_t fileAction) :
            m_fileName(fileName),
            m_fileAction(fileAction)
        {}
        IMFS::string m_fileName;

        /*
        Value is one of the following:
            FILE_ACTION_ADDED,
            FILE_ACTION_REMOVED,
            FILE_ACTION_MODIFIED,
            FILE_ACTION_RENAMED_OLD_NAME,
            FILE_ACTION_RENAMED_NEW_NAME,

        Other values not supported.
        */
        uint32_t m_fileAction;
    };
}
