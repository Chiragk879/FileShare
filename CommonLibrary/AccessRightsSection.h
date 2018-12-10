#pragma once

namespace IMFS
{
    /// <summary>
    /// Represents global access rights applied to the share
    /// </summary>
    class AccessRightsSection : public ConfigurationSection
    {
    public:
        DWORD deniedFileRights;
        DWORD deniedFolderRights;
    public:
        AccessRightsSection();
        virtual ~AccessRightsSection();

        void ReadSectionData();
    };
}
