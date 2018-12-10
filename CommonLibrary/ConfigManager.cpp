#include "stdafx.h"
#include "XMLReader.h"
using namespace IMFS;

#define FS_RO_MODE_FILE_ACCESS_RIGHTS (DELETE | FILE_WRITE_DATA | FILE_APPEND_DATA | \
                                       FILE_WRITE_EA | FILE_WRITE_ATTRIBUTES | WRITE_OWNER | \
                                       GENERIC_WRITE)
#define FS_RO_MODE_FOLDER_ACCESS_RIGHTS (FILE_DELETE_CHILD | FILE_ADD_FILE | FILE_ADD_SUBDIRECTORY | \
                                         FILE_WRITE_EA | FILE_WRITE_ATTRIBUTES | WRITE_OWNER | \
                                         GENERIC_WRITE)
#define FS_DROPBOX_MODE_FILE_ACCESS_RIGHTS (DELETE)
#define FS_DROPBOX_MODE_FOLDER_ACCESS_RIGHTS (FILE_DELETE_CHILD)

ConfigManager::ConfigManager()
    : m_logSection(L"INFO")
    , m_auditlogSection(L"BRIEF")
{
}

ConfigManager::~ConfigManager()
{
}

ConfigManager* ConfigManager::m_instance = NULL;
string ConfigManager::configfileName = L"config.xml";

ConfigManager* ConfigManager::GetInstance()
{
    if (m_instance == NULL)
    {
        m_instance = new ConfigManager();
        if (m_instance)
            m_instance->Init();
    }
    return m_instance;
}

void ConfigManager::Init()
{
    m_versionSection.ReadSectionData();
    m_dialectsSection.ReadSectionData();
    m_serverSection.ReadSectionData();
    m_sharesSection.ReadSectionData();
    m_mergeSection.ReadSectionData();
    m_rightsSection.ReadSectionData();
    m_logSection.ReadSectionData(SectionTypes::Log);
    m_auditlogSection.ReadSectionData(SectionTypes::AuditLog);
    m_databasesSection.ReadSectionData();
    m_keysSection.GetData();

    GetConfigFileModifiedTime(m_lastConfigFileModifiedTime);

    m_timer.SetInterval(30000);
    m_timer.SetElapsed(configTimerHandler, (INT_PTR)this);
    m_timer.Start();
}

void ConfigManager::SetInstance(ConfigManager *instance)
{
    m_instance = instance;
}

void ConfigManager::configTimerHandler(INT_PTR state)
{
    ConfigManager* pConfig = (ConfigManager*)state;
    if (pConfig != nullptr && pConfig->IsConfigFileModified())
    {
        pConfig->m_logSection.ReadSectionData(SectionTypes::Log);
        pConfig->m_auditlogSection.ReadSectionData(SectionTypes::AuditLog);
        pConfig->GetConfigFileModifiedTime(pConfig->m_lastConfigFileModifiedTime);
        LogMgr::Initialize();
        AuditLogManager::Initialize();
    }
}

bool ConfigManager::IsConfigFileModified()
{
    bool bIsConfigFileModified = false;

    FILETIME modifiedTime;
    GetConfigFileModifiedTime(modifiedTime);
    long value = CompareFileTime(&m_lastConfigFileModifiedTime, &modifiedTime);
    if (value == 0)
    {
        bIsConfigFileModified = false;
    }
    else
    {
        bIsConfigFileModified = true;
    }

    return bIsConfigFileModified;
}

void ConfigManager::Destroy()
{
    if (m_instance != NULL)
    {
        m_instance->m_timer.Stop();
        delete m_instance;
        m_instance = NULL;
    }
}

uint8_t ConfigManager::GetVersion()
{
    return m_versionSection.Version;
}

const DialectsSection& ConfigManager::GetDialectsSection()
{
    return m_dialectsSection;
}

ServerSection& ConfigManager::GetServerSection()
{
    return m_serverSection;
}

LogSection& ConfigManager::GetLogSection()
{
    return m_logSection;
}

LogSection& ConfigManager::GetAuditLogSection()
{
    return m_auditlogSection;
}

const SharesSection& ConfigManager::GetSharesSection()
{
    return m_sharesSection;
}

const MergeSection& ConfigManager::GetMergeSection()
{
    return m_mergeSection;
}

const AccessRightsSection& ConfigManager::GetAccessRightsSection()
{
    return m_rightsSection;
}

const KeysSection& ConfigManager::GetKeysSection()
{
    return m_keysSection;
}

const DatabasesSection& ConfigManager::GetDatabasesSection()
{
    return m_databasesSection;
}

const ShareElement* ConfigManager::GetShare(const string &shareName)
{
    string trimmed = shareName.Trim().ToLower();
    for (auto&& item : m_sharesSection.Shares)
    {
        if (trimmed == item.Name.Trim().ToLower())
        {
            return &item;
        }
    }
    return nullptr;
}

const FILETIME& ConfigManager::GetLastConfigFileModifiedTime() const
{
    return m_lastConfigFileModifiedTime;
}

bool ConfigManager::GetConfigFileModifiedTime(FILETIME &ftWrite)
{
    XMLReader reader;
    return reader.GetConfigFileModifiedTime(ftWrite);
}

bool ConfigManager::RequireMessageSigning()
{
    return (GetServerSection().RawSecurityMode & 0x02) == 0x02;
}

ConfigManager::FileShareMode ConfigManager::GetFileShareMode()
{
    const AccessRightsSection& as = GetAccessRightsSection();
    // Check access rights combinations from strongest to weakest.
    if ((as.deniedFileRights & FS_RO_MODE_FILE_ACCESS_RIGHTS) == FS_RO_MODE_FILE_ACCESS_RIGHTS && 
        (as.deniedFolderRights & FS_RO_MODE_FOLDER_ACCESS_RIGHTS) == FS_RO_MODE_FOLDER_ACCESS_RIGHTS)
    {
        return ConfigManager::FileShareMode::FS_MODE_RO;
    }
    else if ((as.deniedFileRights == FS_DROPBOX_MODE_FILE_ACCESS_RIGHTS) && 
             (as.deniedFolderRights == FS_DROPBOX_MODE_FOLDER_ACCESS_RIGHTS))
    {
        return ConfigManager::FileShareMode::FS_MODE_DROPBOX;
    }
    return ConfigManager::FileShareMode::FS_MODE_NORMAL;
}
