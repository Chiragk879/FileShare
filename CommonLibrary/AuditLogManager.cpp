#include "stdafx.h"
#include "AuditLogManager.h"
#include "trace.h"

using namespace IMFS;

std::atomic<long> AuditLogManager::serverLogLevel = static_cast<long>(AuditTracer::AuditLevelsEnum::LVL_BRIEF);
std::map<IMFS::string, int> AuditLogManager::userLevelMap;
DWORD AuditLogManager::undefinedUserLevel = static_cast<DWORD>(AuditTracer::AuditLevelsEnum::LVL_UNDEFINED);
std::mutex AuditLogManager::m_lock;

void AuditLogManager::Start()
{
    ConfigManager *mgr = ConfigManager::GetInstance();
    if (mgr != NULL)
    {
        Initialize();
    }
}

void AuditLogManager::Initialize()
{
    IMFS::ConfigManager *mgr = ConfigManager::GetInstance();

    if (mgr != NULL)
    {
        {
            std::lock_guard<std::mutex> lock(m_lock);
            userLevelMap.clear();
            std::map<string, string> templevels = mgr->GetAuditLogSection().UserLoggingLevel;
            for (auto level: templevels)
            {
                int userLoggingLevel = AuditTracer::AuditLevelsEnum::LVL_BRIEF;
                userLoggingLevel = GetLevelFromString(level.second);
                string user = level.first;
                userLevelMap[user.ToUpper()] = userLoggingLevel;
            }
        }

        AuditTracer::AuditLevelsEnum traceLevel = AuditTracer::AuditLevelsEnum::LVL_BRIEF;
        traceLevel = static_cast<AuditTracer::AuditLevelsEnum>(GetLevelFromString(mgr->GetAuditLogSection().LoggingLevel));
        AuditTracer::GetInstance().SetLoggingLevel(traceLevel);
        AuditTracer::GetInstance().SetLogFileSize(mgr->GetAuditLogSection().LogFileSize);
    }
    if (serverLogLevel != static_cast<long>(AuditTracer::GetInstance().GetLoggingLevel()))
    {
        serverLogLevel = static_cast<long>(AuditTracer::GetInstance().GetLoggingLevel());
    }
}

void AuditLogManager::Shutdown()
{
}

bool AuditLogManager::IsEnabled(const string &user)
{
    return IsEnabled(GetUserLevel(user));
}

bool AuditLogManager::IsEnabled(DWORD level)
{
    bool isEnabled = false;

    if (serverLogLevel < AuditTracer::LVL_NONE)
        isEnabled = true;
    else
    {
        if (level < AuditTracer::LVL_NONE)
            isEnabled = true;
    }
    return isEnabled;
}

bool AuditLogManager::IsDetailedEnabled(DWORD level)
{
    bool isEnabled = false;

    if (serverLogLevel <= AuditTracer::LVL_DETAILED)
        isEnabled = true;
    else
    {
        if (level <= AuditTracer::LVL_DETAILED)
            isEnabled = true;
    }
    return isEnabled;
}

bool AuditLogManager::IsBriefEnabled(DWORD level)
{
    bool isEnabled = false;

    if (serverLogLevel <= AuditTracer::LVL_BRIEF)
        isEnabled = true;
    else
    {
        if (level <= AuditTracer::LVL_BRIEF)
            isEnabled = true;
    }
    return isEnabled;
}

void AuditLogManager::Log(const IMFS::string& userId, uint32_t sessionId, const wchar_t *str, const wchar_t *message, va_list _ArgList)
{
    std::lock_guard<std::mutex> lock(m_lock);
    AuditTracer::GetInstance().Trace(userId.c_str(), sessionId, str, message, _ArgList);
}

void AuditLogManager::LogStatistics(const IMFS::string& statistics)
{
    std::lock_guard<std::mutex> lock(m_lock);
    AuditTracer::GetInstance().Trace(statistics.c_str());
}

DWORD AuditLogManager::GetUserLevel(const string &userOrig)
{
    string user = userOrig;
    DWORD userlevel = 0;
    int index = (int)user.find(L"\\");
    if (index > 0)
        user = user.Substring(index + 1);

    {
        std::lock_guard<std::mutex> lock(m_lock);

        std::map<IMFS::string, int>::iterator itr = userLevelMap.find(user.ToUpper());

        if (itr != userLevelMap.end())
        {
            userlevel = (DWORD)itr->second;
        }
        else
            userlevel = undefinedUserLevel;//not found
    }

    return userlevel;
}

int AuditLogManager::GetLevelFromString(const string& level)
{
    int LoggingLevel = AuditTracer::AuditLevelsEnum::LVL_BRIEF;

    if (level.CompareIgnoreCase(L"DETAILED") == 0)
    {
        LoggingLevel = AuditTracer::AuditLevelsEnum::LVL_DETAILED;
    }
    else if (level.CompareIgnoreCase(L"NONE") == 0)
    {
        LoggingLevel = AuditTracer::AuditLevelsEnum::LVL_NONE;
    }
    return LoggingLevel;
}


