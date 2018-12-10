#pragma once

// The things the public CommonLibrary classes depend on
#include <stl/NrString.h>
#define WIN32_NO_STATUS 1
#include <windows.h>
#include "Utils.h"
#include <process.h>
#include <strsafe.h>
#include <stl/STLPointer.h>
#include <report\Assert.h>

// TEMP until we unfreeze MLIB
#pragma warning( push ) 
#pragma warning( disable : 4100 )
#include <thread\TraceLock.h>
#pragma warning ( pop )

// All of the public CommonLibrary classes
#include "fsdefs.h"
#include "ByteArray.h"
#include "ArrayWrapper.h"
#include "Enums.h"
#include "LockRange.h"
#include "SmbLockRange.h"
#include "SmbFileLockRange.h"
#include "FileInfoByHandleClass.h"
#include "PathManager.h"
#include "Timer.h"
#include "Stopwatch.h"
#include "CallReporter.h"
#include "Guid.h"
#include "KeyObject.h"
#include "ByteBuffer.h"
#include "DataStreamInfo.h"
#include "ErrorConvertor.h"
#include "FileAttributeData.h"
#include "IFileInformationLevel.h"
#include "FileInformation.h"
#include "FileSystemAttributeInformation.h"
#include "FileSystemControlInfo.h"
#include "FileSystemDeviceInfo.h"
#include "FileSystemObjectIdInfo.h"
#include "FileSystemSizeInfo.h"
#include "FileSystemVolume.h"
#include "FindFileInfo.h"
#include "FindFileInfos.h"
#include "FindInformationLevel.h"
#include "IManID.h"
#include "File2.h"
#include "IFile2Enumerator.h"
#include "Folder2.h"
#include "FsFileHandle2.h"
#include "FSFindFileHandle2.h"
#include "VolumeInformation.h"
#include "INotification.h"
#include "IFileSystem2.h"
#include "IFileSystem2Monitor.h"
#include "AuthInfo.h"
#include "AuthType.h"
#include "ConfigurationSection.h"
#include "ConfigEnums.h"
#include "ConfigurationElement.h"
#include "DatabasesElement.h"
#include "DatabasesSection.h"
#include "DialectElement.h"
#include "DialectsSection.h"
#include "MergeSection.h"
#include "AccessRightsSection.h"
#include "KeysSection.h"
#include "ServerSection.h"
#include "VersionSection.h"
#include "LogSection.h"
#include "ShareElement.h"
#include "SharesSection.h"
#include "ConfigManager.h"
#include "EventHandler.h"
#include "VfsFileHandle.h"
#include "VfsFindFileHandle.h"
#include "IVfs2.h"
#include "FileChangeInfo.h"
#include "SafeArrayHelper.h"
#include "LockingData.h"
#include "IAsyncResult.h"
#include "Path.h"
#include "Resources.h"
#include "Directory.h"
#include "ErrorCode.h"
#include "EnumHelper.h"
#include "SmbStatusException.h"
#include "File.h"
#include "CTracePacket.h"
#include "IAuthInfo.h"
#include "SmbLockRangeManager.h"
#include "DateTimeHelper.h"
#include "Later.h"
#include "ThreadPool.h"
#include "SmartPtr.h"
#include "ComputerName.h"
#include "PreauthIntegrityHash.h"
#include "Crypto\HmacKeyFactory.h"
#include "Crypto\CryptKey.h"
#include "Crypto\IHmacKey.h"

/// Uncomment line below to enable helper functionality for debugging in release mode
// #define DEBUG_POINTERS

#ifdef DEBUG_POINTERS

#include <fstream>

#define quotate(what) #what

class PtrLogger
{
public:
    PtrLogger(void* ptr = nullptr, const char* description = nullptr, const char* variable = nullptr, const char* file = nullptr, const char* function = "global", int line = 0)
    {
        if (ptr != nullptr)
        {
            Log(ptr, description, variable, file, function, line);
        }
    }

    void Log(void* ptr, const char* description = nullptr, const char* variable = nullptr, const char* file = nullptr, const char* function = "global", int line = 0)
    {
        try {
            std::ofstream log("D:\\pointers.log", std::ios::app);

            if (file != nullptr)
            {
                std::string name(file);
                auto pos = name.find_last_of('\\');
                if (pos == std::string::npos)
                {
                    pos = 0;
                }
                else
                {
                    ++pos;
                }

                if (description != nullptr)
                {
                    log << description << " ";
                }
                log << name.substr(pos) << ":";
            }
            if (line != 0)
            {
                log << line << " ";
            }

            log << function << " ";

            log << variable << " = " << std::hex << ptr << std::dec << std::endl;
            log.close();
        }
        catch (...) {} // This MUST not fail never ever!
    }
};

#define LOG_POINTER(ptr, description) { PtrLogger __logPtr(ptr, description, quotate(ptr),__FILE__, __FUNCTION__, __LINE__ - 1); }

#else // DEBUG_POINTERS

#define LOG_POINTER(ptr, description) /* do nothing */

#endif // DEBUG_POINTERS