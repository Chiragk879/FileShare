#pragma once

#include <ctime>
#include <verification/SystemErrorString.h>

//
// FileShare defs to ease porting from C#
//

//
// Fundamental C# types and their C++ equivalents
//
typedef signed char			sbyte;
typedef unsigned char		byte;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned __int64	ulong64;
typedef INT_PTR				IntPtr;
typedef unsigned __int64    UInt64;

//
// These structs are used internally by CIFS because they 
// relate very closely to SMB requests.  However, they were
// not exposed in the Win32 API until Vista.  Define them
// here if not compiling for Vista.
//
#if (_WIN32_WINNT < 0x0600)
typedef enum _FILE_INFO_BY_HANDLE_CLASS {
    FileBasicInfo,
    FileStandardInfo,
    FileNameInfo,
    FileRenameInfo,
    FileDispositionInfo,
    FileAllocationInfo,
    FileEndOfFileInfo,
    FileStreamInfo,
    FileCompressionInfo,
    FileAttributeTagInfo,
    FileIdBothDirectoryInfo,
    FileIdBothDirectoryRestartInfo,
    FileIoPriorityHintInfo,
    MaximumFileInfoByHandleClass
} FILE_INFO_BY_HANDLE_CLASS, *PFILE_INFO_BY_HANDLE_CLASS;

typedef struct _FILE_BASIC_INFO {
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    DWORD FileAttributes;
} FILE_BASIC_INFO, *PFILE_BASIC_INFO;

typedef struct _FILE_STANDARD_INFO {
    LARGE_INTEGER AllocationSize;
    LARGE_INTEGER EndOfFile;
    DWORD NumberOfLinks;
    BOOLEAN DeletePending;
    BOOLEAN Directory;
} FILE_STANDARD_INFO, *PFILE_STANDARD_INFO;

typedef struct _FILE_NAME_INFO {
    DWORD FileNameLength;
    WCHAR FileName[1];
} FILE_NAME_INFO, *PFILE_NAME_INFO;

typedef struct _FILE_RENAME_INFO {
    BOOLEAN ReplaceIfExists;
    HANDLE RootDirectory;
    DWORD FileNameLength;
    WCHAR FileName[1];
} FILE_RENAME_INFO, *PFILE_RENAME_INFO;

typedef struct _FILE_ALLOCATION_INFO {
    LARGE_INTEGER AllocationSize;
} FILE_ALLOCATION_INFO, *PFILE_ALLOCATION_INFO;

typedef struct _FILE_END_OF_FILE_INFO {
    LARGE_INTEGER EndOfFile;
} FILE_END_OF_FILE_INFO, *PFILE_END_OF_FILE_INFO;

typedef struct _FILE_STREAM_INFO {
    DWORD NextEntryOffset;
    DWORD StreamNameLength;
    LARGE_INTEGER StreamSize;
    LARGE_INTEGER StreamAllocationSize;
    WCHAR StreamName[1];
} FILE_STREAM_INFO, *PFILE_STREAM_INFO;

typedef struct _FILE_COMPRESSION_INFO {
    LARGE_INTEGER CompressedFileSize;
    WORD CompressionFormat;
    UCHAR CompressionUnitShift;
    UCHAR ChunkShift;
    UCHAR ClusterShift;
    UCHAR Reserved[3];
} FILE_COMPRESSION_INFO, *PFILE_COMPRESSION_INFO;

typedef struct _FILE_ATTRIBUTE_TAG_INFO {
    DWORD FileAttributes;
    DWORD ReparseTag;
} FILE_ATTRIBUTE_TAG_INFO, *PFILE_ATTRIBUTE_TAG_INFO;

typedef struct _FILE_DISPOSITION_INFO {
    BOOLEAN DeleteFile;
} FILE_DISPOSITION_INFO, *PFILE_DISPOSITION_INFO;

typedef struct _FILE_ID_BOTH_DIR_INFO {
    DWORD NextEntryOffset;
    DWORD FileIndex;
    LARGE_INTEGER CreationTime;
    LARGE_INTEGER LastAccessTime;
    LARGE_INTEGER LastWriteTime;
    LARGE_INTEGER ChangeTime;
    LARGE_INTEGER EndOfFile;
    LARGE_INTEGER AllocationSize;
    DWORD FileAttributes;
    DWORD FileNameLength;
    DWORD EaSize;
    CCHAR ShortNameLength;
    WCHAR ShortName[12];
    LARGE_INTEGER FileId;
    WCHAR FileName[1];
} FILE_ID_BOTH_DIR_INFO, *PFILE_ID_BOTH_DIR_INFO;

typedef enum _PRIORITY_HINT {
    IoPriorityHintVeryLow = 0,
    IoPriorityHintLow,
    IoPriorityHintNormal,
    MaximumIoPriorityHintType
} PRIORITY_HINT;

typedef struct _FILE_IO_PRIORITY_HINT_INFO {
    PRIORITY_HINT PriorityHint;
} FILE_IO_PRIORITY_HINT_INFO, *PFILE_IO_PRIORITY_HINT_INFO;
#endif

#define SMB2_INVALID_FILE_ID static_cast<uint64_t>(-1LL)
// value to indicate that session does not exist
#define SMB2_NOT_EXIST_SESSION_ID static_cast<uint64_t>(0)
// value to indicate that session id should be obtained from previous request of compound requests
#define SMB2_INVALID_SESSION_ID static_cast<uint64_t>(-1LL)
// value to indicate that tree id should be obtained from previous request of compound requests
#define SMB2_INVALID_TREE_ID static_cast<uint32_t>(-1L)

// Was:  C# enum
// Now:  Use status codes from ntstatus.h
typedef NTSTATUS			NtStatus;

//#define STATUS_SMB_NO_PREAUTH_INTEGRITY_HASH_OVERLAP (NtStatus) (0xC05D0000)

// Make NtStatus.OK become STATUS_SUCCESS
#define STATUS_OK			STATUS_SUCCESS

// Was:  C# enum
// Now:  Use any Win32 error code
typedef uint				ApiRet;

// Was:  C# enum
// Now:  Use std. Win32 defs, e.g., FILE_ATTRIBUTE_NORMAL
typedef uint32_t			FlagsAndAttributes;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. GENERIC_READ
typedef uint32_t			DesiredAccess;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. FILE_SHARE_READ
typedef uint32_t			ShareMode;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. OPEN_ALWAYS
typedef uint				CreationDisposition;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. LOCKFILE_EXCLUSIVE_LOCK
typedef uint				LockFileExFlags;

// Was:  C# enum
// Now:  ???
typedef uint				CompletionFilter;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. FILE_BYTE_ALIGNMENT
typedef uint				AlignmentRequirement;

// Was:  C# enum
// Now:  Use std. Win32 defs e.g. SEC_I_CONTINUE_NEEDED
typedef uint				AuthNegotiateResult;

/// <summary>
/// Set of flags used for monitoring file and directories changes
/// </summary>
typedef uint				COMPLETIONFILTER;

/// <summary>
/// The name of the file
/// </summary>
#define FileNameChange  (0x0001)
/// <summary>
/// The name of the directory
/// </summary>
#define DirectoryNameChange  (0x0002)
/// <summary>
/// The attributes of the file or folder
/// </summary>
#define AttributeChange  (0x0004)
/// <summary>
/// The size of the file or folder
/// </summary>
#define SizeChange  (0x0008)
/// <summary>
/// The date the file or folder last had anything written to it
/// </summary>
#define LastWriteChange  (0x0010)
/// <summary>
/// The date the file or folder was last opened
/// </summary>
#define LastAccessChange  (0x0020)
/// <summary>
/// The time the file or folder was created
/// </summary>
#define CreatedChange  (0x0040)
/// <summary>
/// The extended attributes of the file or folder
/// </summary>
#define EAChange  (0x0080)
/// <summary>
/// The security settings of the file or folder
/// </summary>
#define SecurityChange  (0x0100)
/// <summary>
/// The name of the stream
/// </summary>
#define StreamNameChange  (0x0200)
/// <summary>
/// The size of the stream
/// </summary>
#define StreamSizeChange  (0x0400)
/// <summary>
/// Data has been written to the stream
/// </summary>
#define StreamWrite  (0x0800)

/// <summary>
/// Maximum response size is 64KB
/// </summary>
#define MAXIMUM_RESPONSE_SIZE (65536)

/// <summary>
/// Session expiration time is 10 min specifies in seconds(600 sec)
/// </summary>
#define SESSION_EXPIRATION_TIME (600)

/// <summary>
/// Lock files expiration time is 15 sec specifies in seconds
/// </summary>
#define LOCKFILES_EXPIRATION_TIME (15)
/// <summary>
/// Timer check lock files expiration time is 5 sec specifies in milliseconds (5000 msec)
/// </summary>
#define TIMER_CHECK_LOCKFILES_EXPIRATION_TIME (5000)
/// <summary>
/// This timer has a default value of 35 seconds, but its value could be changed by
/// system policy to any range between 5 seconds and infinite (4,294,967,295 seconds).
/// </summary>
#if _DEBUG
#define TIMER_CHECK_OPLOCK_BREAK_EXPIRATION_TIME (1000)
#else
#define TIMER_CHECK_OPLOCK_BREAK_EXPIRATION_TIME (1000)
#endif
/// Timeout session expiration time is 45 sec specifies in milliseconds (45000 msec)
/// </summary>
#define TIMEOUT_SESSION_EXPIRATION_TIME (45000)
/// <summary>
/// Difference between Unix time (seconds since midnight January 1, 1970 UTC)
/// and Windows FILETIME (number of 100-nanosecond intervals since January 1, 1601 UTC)
/// </summary>
#define WIN_TIME_TO_UNIX_TIME_OFFSET_SECONDS (11644473600ULL)
/// <summary>
/// Multiplicator between Unix time (seconds since midnight January 1, 1970 UTC)
/// and Windows FILETIME (number of 100-nanosecond intervals since January 1, 1601 UTC)
/// </summary>
#define WIN_TIME_TO_UNIX_TIME_MUTIPLICATOR  (10000000)


namespace IMFS
{
    using ByteVector=std::vector<uint8_t>;
    using ByteVectorPtr=std::shared_ptr<ByteVector>;

    // Use in place of Debug.Assert
#define IMFS_ASSERT(arg) IM_ASSERT(arg)
#define ASSERT_TODO IM_ASSERT(false);

#define TO_INT64(li) li.QuadPart
#define TO_LI(li, i64) li.QuadPart=i64

    // In place of C# object in those rare places we need it
    class Object : public IM::TraceLock
    {
    public:
        Object(const wchar_t *traceLockName);
        virtual ~Object();

    private:
        Object();  // not allowed, must give trace lock name

    public:
        //
        // You may be very tempted to add this.  Think about
        // it for a long while and you'll realize why this is
        // a very bad idea for C++ code.  
        //
        // Hint: Try to implement this safely without any runtime
        //       type checking support
        //
        //virtual bool Equals(const Object& other) const = 0;

    };
    typedef Object object;

    // C# NameValueCollection redefine
    class NameValueCollection : public std::map<string, string>
    {
    public:
        void Add(const string& key, const string& val) { (*this)[key] = val; }
        virtual ~NameValueCollection() {}
    };

    // PLACEHOLDER until we figure out what to do with C# TimeSpan
    class TimeSpan
    {
        double _seconds;
    public:

        TimeSpan()
        {}

        TimeSpan(double seconds) :_seconds(seconds)
        {}

        static TimeSpan FromSeconds(double sec)
        {
            TimeSpan tm(sec);
            return tm;
        }

        double GetTotalSeconds()const
        {
            return _seconds;
        }
    };


    // PLACEHOLDER until we figure out what to do with C# FSDateTime
    // Dummy implementation Need rework.- Vishal 
    class FSDateTime
    {
        SYSTEMTIME _time;

    public:
        FSDateTime()
        {
            _time.wYear = 1970;
            _time.wMonth = 1;
            _time.wDay = 1;
            _time.wHour = 0;
            _time.wMinute = 0;
            _time.wSecond = 0;
            _time.wMilliseconds = 0;
            _time.wDayOfWeek = 0;
        }
        FSDateTime(std::time_t t)
        {
            FILETIME ft = {0};
            LONGLONG ll = t;
            ll += WIN_TIME_TO_UNIX_TIME_OFFSET_SECONDS;
            ll *= WIN_TIME_TO_UNIX_TIME_MUTIPLICATOR;
            ft.dwLowDateTime = (DWORD)ll;
            ft.dwHighDateTime = ll >> 32;
            if (!FileTimeToSystemTime(&ft, &_time))
            {
                IMLOG_DEBUG(L"Failed to convert file time to system time: %s", IM::LastErrorString().c_str());
            }
        }
        FSDateTime(SYSTEMTIME time)
        {
            _time = time;
        }
        FSDateTime(DATE comtime)
        {
            if (!VariantTimeToSystemTime(comtime, &_time))
            {
                _time.wYear = 1970;
                _time.wMonth = 1;
                _time.wDay = 1;
                _time.wHour = 0;
                _time.wMinute = 0;
                _time.wSecond = 0;
                _time.wMilliseconds = 0;
                _time.wDayOfWeek = 0;
            }
        }
        WORD GetYear(){ return _time.wYear; }
        WORD GetMonth(){ return _time.wMonth; }
        WORD GetDay(){ return _time.wDay; }
        WORD GetHour(){ return _time.wHour; }
        WORD GetMinute(){ return _time.wMinute; }
        WORD GetSecond(){ return _time.wSecond; }
        WORD GetMilliSeconds(){ return _time.wMilliseconds; }

        void SetMilliSeconds(WORD milliseconds)
        {
            _time.wMilliseconds = milliseconds;
        }

        signed __int64 ToFileTimeUtc() const
        {
            FILETIME fTime = {0};
            if(!::SystemTimeToFileTime(&_time, &fTime))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }
            const __int64 *intTime = (__int64*)&fTime;
            return *intTime;
        }

        FILETIME ToFileTimeUtcAsFileTime() const
        {
            FILETIME fTime;
            ::memset(&fTime, 0, sizeof(fTime));
            if (!::SystemTimeToFileTime(&_time, &fTime))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }
#pragma warning(suppress: 6102)
            return fTime;
        }

        DATE ToVariantTime() const
        {
            DOUBLE varianttime;
            SystemTimeToVariantTime((LPSYSTEMTIME)&_time, &varianttime);
            return varianttime;
        }

        static FSDateTime GetMinValue()
        {
            SYSTEMTIME t;
            t.wYear = 1970;
            t.wMonth = 1;
            t.wDay = 1;
            t.wHour = 0;
            t.wMinute = 0;
            t.wSecond = 0;
            t.wMilliseconds = 0;

            FSDateTime dt(t);
            return dt;
        };
        static FSDateTime GetNow()
        {
            SYSTEMTIME lt;
            ::GetLocalTime(&lt);
            FSDateTime t(lt);
            return t;
        };
        static FSDateTime GetUtcNow()
        {
            SYSTEMTIME st;
            ::GetSystemTime(&st);
            FSDateTime t(st);
            return t;
        }
        FSDateTime Add(const TimeSpan &ts)
        {

            FILETIME FileTime1 = {0}, FileTime2 = {0};
            if (!SystemTimeToFileTime(&_time, &FileTime1))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }


            double seconds = ts.GetTotalSeconds();
            double milliseconds = seconds * 1000.0f;
            *(__int64*)&FileTime2 = (__int64)milliseconds * 10000;

            FILETIME result;
            const ULARGE_INTEGER *int1 = (ULARGE_INTEGER*)&FileTime1;
            const ULARGE_INTEGER *int2 = (ULARGE_INTEGER*)&FileTime2;
            ULARGE_INTEGER *int3 = (ULARGE_INTEGER*)&(result);

            int3->QuadPart = int1->QuadPart + int2->QuadPart;

            SYSTEMTIME ttemp = {0};
            if (!FileTimeToSystemTime(&result, &ttemp))
            {
                IMLOG_DEBUG(L"Failed to convert file time to system time: %s", IM::LastErrorString().c_str());
            }
#pragma warning(suppress: 6102)
            FSDateTime t(ttemp);
            return t;
        }
        TimeSpan operator -(const FSDateTime &time)const
        {
            FILETIME FileTime1 = {0}, FileTime2 = {0};
            if (!SystemTimeToFileTime(&_time, &FileTime1))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            if (!SystemTimeToFileTime(&time._time, &FileTime2))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            const __int64 *int1 = (__int64*)&FileTime1;
            const __int64 *int2 = (__int64*)&FileTime2;

            __int64 toseconds = *int1 - *int2;

            __int64 seconds = (toseconds / 10000) / 1000;

            TimeSpan t = TimeSpan::FromSeconds((double)seconds);
            return t;
        }
        SYSTEMTIME GetTimeStruct(){ return _time; }
        void SetTimeStruct(SYSTEMTIME systime){ _time = systime; }
        bool operator!=(FSDateTime time) const
        {
            FILETIME FileTime1 = {0}, FileTime2 = {0};
            if (!SystemTimeToFileTime(&time._time, &FileTime1))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            if (!SystemTimeToFileTime(&_time, &FileTime2))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            const ULARGE_INTEGER *int1 = (ULARGE_INTEGER*)&FileTime1;
            const ULARGE_INTEGER *int2 = (ULARGE_INTEGER*)&FileTime2;

            return !(int1->QuadPart == int2->QuadPart);


        }
        bool operator==(const FSDateTime &time) const
        {
            FILETIME FileTime1 = {0}, FileTime2 = {0};
            if (!SystemTimeToFileTime(&time._time, &FileTime1))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            if (!SystemTimeToFileTime(&_time, &FileTime2))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            const ULARGE_INTEGER *int1 = (ULARGE_INTEGER*)&FileTime1;
            const ULARGE_INTEGER *int2 = (ULARGE_INTEGER*)&FileTime2;

            return (int1->QuadPart == int2->QuadPart);
        }
        bool operator<(const FSDateTime &time) const
        {
            FILETIME FileTime1 = {0}, FileTime2 = {0};

            if (!SystemTimeToFileTime(&_time, &FileTime1))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            if (!SystemTimeToFileTime(&time._time, &FileTime2))
            {
                IMLOG_DEBUG(L"Failed to convert system time to file time: %s", IM::LastErrorString().c_str());
            }

            const ULARGE_INTEGER *int1 = (ULARGE_INTEGER*)&FileTime1;
            const ULARGE_INTEGER *int2 = (ULARGE_INTEGER*)&FileTime2;

            return (int1->QuadPart < int2->QuadPart);
        }

        static FSDateTime FromFileTimeUtc(FILETIME ft)
        {
            SYSTEMTIME ttemp = {0};
            if (!FileTimeToSystemTime(&ft, &ttemp))
            {
                IMLOG_DEBUG(L"Failed to convert file time to system time: %s", IM::LastErrorString().c_str());
            }
#pragma warning(suppress: 6102)
            return ttemp;
        }

        static FSDateTime FromFileTimeUtc(signed __int64 utc)
        {
            FILETIME ft;
            ::memcpy(&ft, &utc, sizeof(FILETIME));
            return FromFileTimeUtc(ft);
        }

        FSDateTime ToUniversalTime() const
        {
            TIME_ZONE_INFORMATION tzLocal = {0};
            ::GetTimeZoneInformation(&tzLocal);

            SYSTEMTIME stUTC = {0};
#pragma warning(suppress: 6102)
            if (!::TzSpecificLocalTimeToSystemTime(&tzLocal, &_time, &stUTC))
            {
                IMLOG_DEBUG(L"Failed to convert specific local time to system time: %s",
                            IM::LastErrorString().c_str());
            }

#pragma warning(suppress: 6102)
            FSDateTime dtUTC(stUTC);
            return dtUTC;
        }

        static const std::time_t INVALID_TIME = 0;

    private:

        string ToString() const
        {
            IMFS_ASSERT(false);
            // The CIFS server shouldn't be using FSDateTime::ToString(), since 
            // the textual representation of times is highly localized, and
            // we don't know that server-side.
            return string(L"ERROR");
        }

    };

}
