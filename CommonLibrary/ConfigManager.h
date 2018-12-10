#pragma once

namespace IMFS
{
    /// <summary>
    /// Provides access to App.config configuration file.
    /// </summary>
    /// <remarks>
    /// Singleton class that load all configuration objects on server start.
    /// </remarks>
    class ConfigManager
    {
    private:

        static ConfigManager* m_instance;

        /// <summary>
        /// Initializes all config sections.
        /// </summary>
        void Init();

        Timer m_timer;

    protected:
        ConfigManager();
        ~ConfigManager();

        static void configTimerHandler(INT_PTR state);

        DialectsSection m_dialectsSection;
        ServerSection m_serverSection;
        SharesSection m_sharesSection;
        MergeSection m_mergeSection;
        AccessRightsSection m_rightsSection;
        LogSection m_logSection;
        LogSection m_auditlogSection;
        DatabasesSection m_databasesSection;
        KeysSection m_keysSection;
        VersionSection m_versionSection;

        FILETIME m_lastConfigFileModifiedTime;

    public:
        enum class FileShareMode : uint8_t
        {
            FS_MODE_NORMAL = 0,
            FS_MODE_RO = 1,
            FS_MODE_DROPBOX = 2
        };
    public:
        static string configfileName;
        static ConfigManager* GetInstance();
        static void SetInstance(ConfigManager *instance);
        static void Destroy();

        uint8_t GetVersion();

        /// <summary>
        /// Dialects configuration section.
        /// </summary>
        const DialectsSection& GetDialectsSection();

        /// <summary>
        /// Server configuration section.
        /// </summary>
        ServerSection& GetServerSection();

        LogSection& GetLogSection();

        LogSection& GetAuditLogSection();

        /// <summary>
        /// Shares configuration section.
        /// </summary>
        const SharesSection& GetSharesSection();

        /// <summary>
        /// Merge configuration section.
        /// </summary>
        const MergeSection& GetMergeSection();

        ///
        /// Access rights section
        ///
        const AccessRightsSection& GetAccessRightsSection();

        /// <summary>
        /// Keys configuration section.
        /// </summary>
        const KeysSection& GetKeysSection();

        /// <summary>
        /// Retrieves a share configuration element.
        /// </summary>
        /// <param name="shareName">Share name.</param>
        /// <returns>The share configuration element.</returns>
        const ShareElement* GetShare(const string &shareName);

        /// <summary>
        /// Retrieves a share configuration element.
        /// </summary>
        /// <param name="shareId">Share id.</param>
        /// <returns>The share configuration element.</returns>
        const ShareElement GetShare(int shareId);

        /// <summary>
        /// Database configuration section.
        /// </summary>
        const DatabasesSection& GetDatabasesSection();

        bool GetConfigFileModifiedTime(FILETIME &ftWrite);
        const FILETIME& GetLastConfigFileModifiedTime() const;

        bool RequireMessageSigning();

        /// <summary>
        /// Returns FS mode. Logic of definition is based on Disabled access rights.
        /// </summary>
        FileShareMode GetFileShareMode();

        bool IsConfigFileModified();
    };
}
