#include "stdafx.h"
#include "verification\SystemErrorString.h"

using namespace IMFS;

int64_t DateTimeHelper::GetSmbTimeZone()
{
    TIME_ZONE_INFORMATION info;
    ::memset(&info, 0, sizeof(info));
    ::GetTimeZoneInformation(&info);

#pragma warning(suppress: 6102)
    return (info.Bias + info.DaylightBias) * 60;
}

__int64 DateTimeHelper::GetCurrentSmbTime()
{
    SYSTEMTIME st;
    FILETIME ft;
    ::GetSystemTime(&st);
    ::SystemTimeToFileTime(&st, &ft);

    ULARGE_INTEGER result;
#pragma warning(suppress: 6102)
    result.LowPart = ft.dwLowDateTime;
    result.HighPart = ft.dwHighDateTime;
    return result.QuadPart;
}

__int64 DateTimeHelper::GetSmbTime(const time_t& time)
{
    LONGLONG ll = time;
    ll += WIN_TIME_TO_UNIX_TIME_OFFSET_SECONDS;
    ll *= WIN_TIME_TO_UNIX_TIME_MUTIPLICATOR;
    ULARGE_INTEGER result;
    result.LowPart = (DWORD)ll;
    result.HighPart = ll >> 32;
    return result.QuadPart;
}

std::time_t DateTimeHelper::FileTime2TimeT(const FILETIME& ts)
{
    uint64_t t = ((static_cast<uint64_t>(ts.dwHighDateTime)) << 32) + ts.dwLowDateTime;
    return t / WIN_TIME_TO_UNIX_TIME_MUTIPLICATOR - WIN_TIME_TO_UNIX_TIME_OFFSET_SECONDS;
}

std::time_t DateTimeHelper::FileTime2TimeT(const LARGE_INTEGER& ts)
{
    return (ts.QuadPart) / WIN_TIME_TO_UNIX_TIME_MUTIPLICATOR - WIN_TIME_TO_UNIX_TIME_OFFSET_SECONDS;
}

IMFS::string DateTimeHelper::TimeToStr(const std::time_t& ts)
{
    // Can't use std::localtime if ts is large - first convert to FILETIME and use FileTimeToSystemTime
    IMFS::string s;
    __int64 t = GetSmbTime(ts);
    FILETIME ft;
    ft.dwHighDateTime = t >> 32;
    ft.dwLowDateTime = (DWORD)t;
    SYSTEMTIME st = {0};
    if (FileTimeToSystemTime(&ft, &st) == TRUE)
    {
        s = IMFS::string::Format(L"%d.%d.%d %02d:%02d:%02d.%d",
            st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    }
    return s;
}

void DateTimeHelper::DosTime2DateTime(ushort date, ushort time, FSDateTime& outTime)
{
    FILETIME fileTime;
    DosDateTimeToFileTime(date, time, &fileTime);
    SYSTEMTIME systemTime = {0};
    if (!FileTimeToSystemTime(&fileTime, &systemTime))
    {
        IMLOG_ERROR(L"Failed to convert file time to system time %s", IM::LastErrorString().c_str());
    }

#pragma warning(suppress: 6102)
    outTime.SetTimeStruct(systemTime);
}

void DateTimeHelper::FileTimeToDateTime(FILETIME& fileTime, FSDateTime& outDateTime)
{
    SYSTEMTIME systemTime = {0};
    if (!FileTimeToSystemTime(&fileTime, &systemTime))
    {
        IMLOG_ERROR(L"Failed to convert file time to system time %s", IM::LastErrorString().c_str());
    }

#pragma warning(suppress: 6102)
    outDateTime.SetTimeStruct(systemTime);
}

void DateTimeHelper::FileTime2LocalFileTime(FILETIME &fileTime, FILETIME &outFileTime)
{
    FileTimeToLocalFileTime(&fileTime, &outFileTime);
}

ushort DateTimeHelper::GetDate(FILETIME& ft)
{
    WORD date, time;
    FileTimeToDosDateTime(&ft, &date, &time);

    return date;
}

ushort DateTimeHelper::GetTime(FILETIME& ft)
{
    WORD date, time;
    FileTimeToDosDateTime(&ft, &date, &time);

    return time;
}

void DateTimeHelper::Long2FileTime(__int64 fileTime, FILETIME& outFileTime)
{
    *(__int64*)&outFileTime = fileTime;
}

uint64_t DateTimeHelper::FileTime2Long(const FILETIME& fileTime)
{
    ULARGE_INTEGER tmp;
    tmp.HighPart = fileTime.dwHighDateTime;
    tmp.LowPart = fileTime.dwLowDateTime;
    return TO_INT64(tmp);
}

FILETIME DateTimeHelper::DateTime2FileTimeUtc(const FSDateTime& dateTime)
{
    LARGE_INTEGER li;
    li.QuadPart = dateTime.ToFileTimeUtc();

    FILETIME time;
    time.dwLowDateTime = li.LowPart;
    time.dwHighDateTime = li.HighPart;

    return time;
}

FILETIME DateTimeHelper::ClearMilliseconds(const FSDateTime& fsDateTime)
{
    FILETIME fileTime = fsDateTime.ToFileTimeUtcAsFileTime();
    SYSTEMTIME systemTime = {0};
    if (!FileTimeToSystemTime(&fileTime, &systemTime))
    {
        IMLOG_ERROR(L"Failed to convert file time to system time %s", IM::LastErrorString().c_str());
    }
    systemTime.wMilliseconds = 0;
    SystemTimeToFileTime(&systemTime, &fileTime);
#pragma warning(suppress: 6102)
    return fileTime;
}

IMFS::string DateTimeHelper::LargeIntegerFileTimeToStr(const LARGE_INTEGER& fileTime)
{
    FILETIME ft;
    ft.dwHighDateTime = fileTime.HighPart;
    ft.dwLowDateTime = fileTime.LowPart;
    return FileTimeToStr(ft);
}

IMFS::string DateTimeHelper::FileTimeToStr(const FILETIME& fileTime)
{
    SYSTEMTIME stLocal = {0};
    if (!FileTimeToSystemTime(&fileTime, &stLocal))
    {
        IMLOG_DEBUG(L"Failed to convert file time to system time %s", IM::LastErrorString().c_str());
        return L"";
    }

    return string::Format(L"@GMT-%hu.%02hu.%02hu-%02hu.%02hu.%02hu",
                          stLocal.wYear, stLocal.wMonth, stLocal.wDay,
                          stLocal.wHour, stLocal.wMinute, stLocal.wSecond);
}
