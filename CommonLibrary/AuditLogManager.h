#pragma once
#include "string.h"
#include <mutex>
#include <comdef.h> 
#include <map>
#include <atomic>

namespace IMFS
{
    class AuditLogManager
    {
    public:
        static void Initialize();

        static bool IsEnabled(const string &user);
        static bool IsEnabled(DWORD level);
        static bool IsBriefEnabled(DWORD level);
        static bool IsDetailedEnabled(DWORD level);

        static void Log(const IMFS::string& userId, uint32_t sessionId, const wchar_t *str, const wchar_t *message, va_list _ArgList);
        static void LogStatistics(const IMFS::string& statistics);
      
        static void Start();
        static void Shutdown();

        static DWORD GetUserLevel(const string &user);

    protected:
        static int GetLevelFromString(const string& level);

    private:
        static std::atomic<long> serverLogLevel;
        static std::map<IMFS::string, int> userLevelMap;
        static DWORD undefinedUserLevel;
        static std::mutex m_lock;
    };
};

