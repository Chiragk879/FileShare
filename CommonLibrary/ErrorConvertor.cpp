#include "stdafx.h"

using namespace IMFS;

std::map<NtStatus, uint> ErrorConvertor::ntStatus2DosError;
std::map<ApiRet, NtStatus> ErrorConvertor::apiRet2NtStatus;
ErrorConvertor ErrorConvertor::ms_instance;

ErrorConvertor::ErrorConvertor()
{
    InitializeNtStatus2DosError();
    InitializeApiRet2NtStatus();
}

ErrorConvertor :: ~ErrorConvertor()
{
}

/// <summary>
/// Get DosError error code from a <see cref="NtStatus"/> error code
/// </summary>
/// <param name="status">Error code in <see cref="NtStatus"/> format</param>
/// <returns>DosError error code</returns>
uint ErrorConvertor::DosError(NtStatus status)
{
    return ntStatus2DosError[status];
}

/// <summary>
/// Get <see cref="NtStatus"/> from a <see cref="ApiRet"/> error code
/// </summary>
/// <param name="apiRet">Error code in <see cref="ApiRet"/> format</param>
/// <returns><see cref="NtStatus"/> error code</returns>
NtStatus ErrorConvertor::ApiRet2NtStatus(ApiRet apiRet)
{
    if (apiRet == ERROR_SUCCESS)
        return STATUS_SUCCESS;

    if (apiRet2NtStatus.find(apiRet) == apiRet2NtStatus.end())
    {
        IMLOG_DEBUG(L"Windows error code is not mapped with and NT_STATUS code: %d", (uint)apiRet);
        return STATUS_OBJECT_PATH_NOT_FOUND;
    }
    return apiRet2NtStatus[apiRet];
}

/// <summary>
/// Is dos code
/// </summary>
/// <param name="status">Status</param>
bool ErrorConvertor::IsDosCode(NtStatus status)
{
    return ((uint)status & 0xFF000000) == 0xF1000000;
}

/// <summary>
/// Pack dos in nt status
/// </summary>
/// <param name="dosClass">Dos class</param>
/// <param name="dosCode">Dos code</param>
NtStatus ErrorConvertor::PackDosInNtStatus(byte dosClass, ushort dosCode)
{
    return (NtStatus)(((uint)0xF1000000) | (uint)((byte)dosClass << 16) | (uint)dosCode);
}

/// <summary>
/// Unpack dos error class
/// </summary>
/// <param name="status">Status</param>
byte ErrorConvertor::UnpackDosErrorClass(NtStatus status)
{
    return (byte)(((uint)status >> 16) & 0xFF);
}

/// <summary>
/// Unpack dos error code
/// </summary>
/// <param name="status">Status</param>
ushort ErrorConvertor::UnpackDosErrorCode(NtStatus status)
{
    return (ushort)((uint)status & 0xFFFF);
}

void ErrorConvertor::InitializeNtStatus2DosError()
{
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OK, ((uint)0 << 16) | ((uint)ERRsuccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNSUCCESSFUL, ((uint)ERRDOS << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_IMPLEMENTED, ((uint)ERRDOS << 16) | ((uint)ERRbadfunc)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_INFO_CLASS, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INFO_LENGTH_MISMATCH, ((uint)ERRDOS << 16) | ((uint)24)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCESS_VIOLATION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IN_PAGE_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PAGEFILE_QUOTA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_HANDLE, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_INITIAL_STACK, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_INITIAL_PC, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_CID, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TIMER_NOT_CANCELED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER, ((uint)ERRDOS << 16) | ((uint)ERRinvalidparam)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_DEVICE, ((uint)ERRDOS << 16) | ((uint)ERRbadfile)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_FILE, ((uint)ERRDOS << 16) | ((uint)ERRbadfile)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_DEVICE_REQUEST, ((uint)ERRDOS << 16) | ((uint)ERRbadfunc)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_END_OF_FILE, ((uint)ERRDOS << 16) | ((uint)38)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_WRONG_VOLUME, ((uint)ERRDOS << 16) | ((uint)34)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_MEDIA_IN_DEVICE, ((uint)ERRDOS << 16) | ((uint)21)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNRECOGNIZED_MEDIA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NONEXISTENT_SECTOR, ((uint)ERRDOS << 16) | ((uint)27)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_MEMORY, ((uint)ERRDOS << 16) | ((uint)ERRnomem)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONFLICTING_ADDRESSES, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_MAPPED_VIEW, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNABLE_TO_FREE_VM, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNABLE_TO_DELETE_SECTION, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_SYSTEM_SERVICE, ((uint)ERRDOS << 16) | ((uint)2142)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILLEGAL_INSTRUCTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LOCK_SEQUENCE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_VIEW_SIZE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_FILE_FOR_SECTION, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ALREADY_COMMITTED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCESS_DENIED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BUFFER_TOO_SMALL, ((uint)ERRDOS << 16) | ((uint)111)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_TYPE_MISMATCH, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NONCONTINUABLE_EXCEPTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_DISPOSITION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNWIND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_STACK, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_UNWIND_TARGET, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_LOCKED, ((uint)ERRDOS << 16) | ((uint)158)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PARITY_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNABLE_TO_DECOMMIT_VM, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_COMMITTED, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PORT_ATTRIBUTES, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PORT_MESSAGE_TOO_LONG, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_MIX, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_QUOTA_LOWER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DISK_CORRUPT_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_NAME_INVALID, ((uint)ERRDOS << 16) | ((uint)ERRinvalidname)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_NAME_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)ERRbadfile)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_NAME_COLLISION, ((uint)ERRDOS << 16) | ((uint)183)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PORT_DISCONNECTED, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_ALREADY_ATTACHED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_PATH_INVALID, ((uint)ERRDOS << 16) | ((uint)ERRinvalidpath)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_PATH_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)ERRbadpath)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECT_PATH_SYNTAX_BAD, ((uint)ERRDOS << 16) | ((uint)ERRinvalidpath)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DATA_OVERRUN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DATA_LATE_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DATA_ERROR, ((uint)ERRDOS << 16) | ((uint)23)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CRC_ERROR, ((uint)ERRDOS << 16) | ((uint)23)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SECTION_TOO_BIG, ((uint)ERRDOS << 16) | ((uint)ERRnomem)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PORT_CONNECTION_REFUSED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PORT_HANDLE, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SHARING_VIOLATION, ((uint)ERRDOS << 16) | ((uint)ERRbadshare)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_QUOTA_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PAGE_PROTECTION, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MUTANT_NOT_OWNED, ((uint)ERRDOS << 16) | ((uint)288)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SEMAPHORE_LIMIT_EXCEEDED, ((uint)ERRDOS << 16) | ((uint)298)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PORT_ALREADY_SET, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SECTION_NOT_IMAGE, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SUSPEND_COUNT_EXCEEDED, ((uint)ERRDOS << 16) | ((uint)156)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_THREAD_IS_TERMINATING, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_WORKING_SET_LIMIT, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INCOMPATIBLE_FILE_MAP, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SECTION_PROTECTION, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EAS_NOT_SUPPORTED, ((uint)ERRDOS << 16) | ((uint)282)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EA_TOO_LARGE, ((uint)ERRDOS << 16) | ((uint)255)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NONEXISTENT_EA_ENTRY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_EAS_ON_FILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EA_CORRUPT_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_LOCK_CONFLICT, ((uint)ERRDOS << 16) | ((uint)ERRlock)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOCK_NOT_GRANTED, ((uint)ERRDOS << 16) | ((uint)ERRlock)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DELETE_PENDING, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CTL_FILE_NOT_SUPPORTED, ((uint)ERRDOS << 16) | ((uint)ERRunsup)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNKNOWN_REVISION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REVISION_MISMATCH, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_OWNER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PRIMARY_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_IMPERSONATION_TOKEN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANT_DISABLE_MANDATORY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_LOGON_SERVERS, ((uint)ERRDOS << 16) | ((uint)2215)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_LOGON_SESSION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_PRIVILEGE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PRIVILEGE_NOT_HELD, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ACCOUNT_NAME, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_USER_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_USER, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_GROUP_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMBER_IN_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMBER_NOT_IN_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LAST_ADMIN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_WRONG_PASSWORD, ((uint)ERRSRV << 16) | ((uint)ERRbadpw)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILL_FORMED_PASSWORD, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PASSWORD_RESTRICTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_FAILURE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCOUNT_RESTRICTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LOGON_HOURS, ((uint)ERRSRV << 16) | ((uint)2241)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_WORKSTATION, ((uint)ERRSRV << 16) | ((uint)2240)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PASSWORD_EXPIRED, ((uint)ERRSRV << 16) | ((uint)2242)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCOUNT_DISABLED, ((uint)ERRSRV << 16) | ((uint)2239)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NONE_MAPPED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_LUIDS_REQUESTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LUIDS_EXHAUSTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_SUB_AUTHORITY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ACL, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_SID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_SECURITY_DESCR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROCEDURE_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)127)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_FORMAT, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_TOKEN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_INHERITANCE_ACL, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RANGE_NOT_LOCKED, ((uint)ERRDOS << 16) | ((uint)158)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DISK_FULL, ((uint)ERRDOS << 16) | ((uint)112)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SERVER_DISABLED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SERVER_NOT_DISABLED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_GUIDS_REQUESTED, ((uint)ERRDOS << 16) | ((uint)68)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_GUIDS_EXHAUSTED, ((uint)ERRDOS << 16) | ((uint)259)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ID_AUTHORITY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_AGENTS_EXHAUSTED, ((uint)ERRDOS << 16) | ((uint)259)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_VOLUME_LABEL, ((uint)ERRDOS << 16) | ((uint)154)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SECTION_NOT_EXTENDED, ((uint)ERRDOS << 16) | ((uint)ERRres)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_MAPPED_DATA, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RESOURCE_DATA_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RESOURCE_TYPE_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RESOURCE_NAME_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ARRAY_BOUNDS_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_DENORMAL_OPERAND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_DIVIDE_BY_ZERO, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_INEXACT_RESULT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_INVALID_OPERATION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_OVERFLOW, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_STACK_CHECK, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOAT_UNDERFLOW, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INTEGER_DIVIDE_BY_ZERO, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INTEGER_OVERFLOW, ((uint)ERRDOS << 16) | ((uint)534)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PRIVILEGED_INSTRUCTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_PAGING_FILES, ((uint)ERRDOS << 16) | ((uint)ERRnomem)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_INVALID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ALLOTTED_SPACE_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INSUFFICIENT_RESOURCES, ((uint)ERRDOS << 16) | ((uint)ERRnomem)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DFS_EXIT_PATH_FOUND, ((uint)ERRDOS << 16) | ((uint)ERRbadpath)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_DATA_ERROR, ((uint)ERRDOS << 16) | ((uint)23)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_NOT_CONNECTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_POWER_FAILURE, ((uint)ERRDOS << 16) | ((uint)21)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FREE_VM_NOT_AT_BASE, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMORY_NOT_ALLOCATED, ((uint)ERRDOS << 16) | ((uint)487)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_WORKING_SET_QUOTA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEDIA_WRITE_PROTECTED, ((uint)ERRDOS << 16) | ((uint)19)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_NOT_READY, ((uint)ERRDOS << 16) | ((uint)21)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_GROUP_ATTRIBUTES, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_IMPERSONATION_LEVEL, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANT_OPEN_ANONYMOUS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_VALIDATION_CLASS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_TOKEN_TYPE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_MASTER_BOOT_RECORD, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INSTRUCTION_MISALIGNMENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INSTANCE_NOT_AVAILABLE, ((uint)ERRDOS << 16) | ((uint)ERRpipebusy)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_NOT_AVAILABLE, ((uint)ERRDOS << 16) | ((uint)ERRpipebusy)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PIPE_STATE, ((uint)ERRDOS << 16) | ((uint)ERRbadpipe)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_BUSY, ((uint)ERRDOS << 16) | ((uint)ERRpipebusy)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILLEGAL_FUNCTION, ((uint)ERRDOS << 16) | ((uint)ERRbadfunc)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_DISCONNECTED, ((uint)ERRDOS << 16) | ((uint)ERRnotconnected)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_CLOSING, ((uint)ERRDOS << 16) | ((uint)ERRpipeclosing)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_CONNECTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_LISTENING, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_READ_MODE, ((uint)ERRDOS << 16) | ((uint)ERRbadpipe)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IO_TIMEOUT, ((uint)ERRDOS << 16) | ((uint)121)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_FORCED_CLOSED, ((uint)ERRDOS << 16) | ((uint)38)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROFILING_NOT_STARTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROFILING_NOT_STOPPED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_COULD_NOT_INTERPRET, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_IS_A_DIRECTORY, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_SUPPORTED, ((uint)ERRDOS << 16) | ((uint)ERRunsup)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REMOTE_NOT_LISTENING, ((uint)ERRDOS << 16) | ((uint)51)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DUPLICATE_NAME, ((uint)ERRDOS << 16) | ((uint)52)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_NETWORK_PATH, ((uint)ERRDOS << 16) | ((uint)53)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETWORK_BUSY, ((uint)ERRDOS << 16) | ((uint)54)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_DOES_NOT_EXIST, ((uint)ERRDOS << 16) | ((uint)55)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_COMMANDS, ((uint)ERRDOS << 16) | ((uint)56)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ADAPTER_HARDWARE_ERROR, ((uint)ERRDOS << 16) | ((uint)57)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_NETWORK_RESPONSE, ((uint)ERRDOS << 16) | ((uint)58)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNEXPECTED_NETWORK_ERROR, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_REMOTE_ADAPTER, ((uint)ERRDOS << 16) | ((uint)60)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PRINT_QUEUE_FULL, ((uint)ERRDOS << 16) | ((uint)61)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SPOOL_SPACE, ((uint)ERRDOS << 16) | ((uint)62)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PRINT_CANCELLED, ((uint)ERRDOS << 16) | ((uint)63)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETWORK_NAME_DELETED, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETWORK_ACCESS_DENIED, ((uint)ERRDOS << 16) | ((uint)65)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_DEVICE_TYPE, ((uint)ERRDOS << 16) | ((uint)66)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_NETWORK_NAME, ((uint)ERRDOS << 16) | ((uint)ERRnosuchshare)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_NAMES, ((uint)ERRDOS << 16) | ((uint)68)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_SESSIONS, ((uint)ERRDOS << 16) | ((uint)69)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SHARING_PAUSED, ((uint)ERRDOS << 16) | ((uint)70)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REQUEST_NOT_ACCEPTED, ((uint)ERRDOS << 16) | ((uint)71)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REDIRECTOR_PAUSED, ((uint)ERRDOS << 16) | ((uint)72)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NET_WRITE_FAULT, ((uint)ERRDOS << 16) | ((uint)88)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROFILING_AT_LIMIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_SAME_DEVICE, ((uint)ERRDOS << 16) | ((uint)ERRdiffdevice)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_RENAMED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_VIRTUAL_CIRCUIT_CLOSED, ((uint)ERRDOS << 16) | ((uint)240)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SECURITY_ON_OBJECT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANT_WAIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_EMPTY, ((uint)ERRDOS << 16) | ((uint)ERRpipeclosing)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANT_ACCESS_DOMAIN_INFO, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANT_TERMINATE_SELF, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_SERVER_STATE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_DOMAIN_STATE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_DOMAIN_ROLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_DOMAIN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DOMAIN_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DOMAIN_LIMIT_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OPLOCK_NOT_GRANTED, ((uint)ERRDOS << 16) | ((uint)300)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_OPLOCK_PROTOCOL, ((uint)ERRDOS << 16) | ((uint)301)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INTERNAL_DB_CORRUPTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INTERNAL_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_GENERIC_NOT_MAPPED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_DESCRIPTOR_FORMAT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_USER_BUFFER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNEXPECTED_IO_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNEXPECTED_MM_CREATE_ERR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNEXPECTED_MM_MAP_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNEXPECTED_MM_EXTEND_ERR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_LOGON_PROCESS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_SESSION_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_1, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_2, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_3, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_4, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_5, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_6, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_7, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_8, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_9, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_10, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_11, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PARAMETER_12, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REDIRECTOR_NOT_STARTED, ((uint)ERRDOS << 16) | ((uint)ERRbadpath)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REDIRECTOR_STARTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_STACK_OVERFLOW, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_PACKAGE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_FUNCTION_TABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000100, ((uint)ERRDOS << 16) | ((uint)203)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DIRECTORY_NOT_EMPTY, ((uint)ERRDOS << 16) | ((uint)145)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_CORRUPT_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_A_DIRECTORY, ((uint)ERRDOS << 16) | ((uint)ERRbaddirectory)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_LOGON_SESSION_STATE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_SESSION_COLLISION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NAME_TOO_LONG, ((uint)ERRDOS << 16) | ((uint)206)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILES_OPEN, ((uint)ERRDOS << 16) | ((uint)2401)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_IN_USE, ((uint)ERRDOS << 16) | ((uint)2404)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MESSAGE_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROCESS_IS_TERMINATING, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LOGON_TYPE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_GUID_TRANSLATION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANNOT_IMPERSONATE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IMAGE_ALREADY_LOADED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_NOT_PRESENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_LID_NOT_EXIST, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_LID_ALREADY_OWNED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_NOT_LID_OWNER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_INVALID_COMMAND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_INVALID_LID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_SELECTOR_NOT_AVAILABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ABIOS_INVALID_SELECTOR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_LDT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LDT_SIZE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LDT_OFFSET, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LDT_DESCRIPTOR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_NE_FORMAT, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RXACT_INVALID_STATE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RXACT_COMMIT_FAILURE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MAPPED_FILE_SIZE_ZERO, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_OPENED_FILES, ((uint)ERRDOS << 16) | ((uint)ERRnofids)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANCELLED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANNOT_DELETE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_COMPUTER_NAME, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_DELETED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SPECIAL_ACCOUNT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SPECIAL_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SPECIAL_USER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMBERS_PRIMARY_GROUP, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_CLOSED, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_THREADS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_THREAD_NOT_IN_PROCESS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOKEN_ALREADY_IN_USE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PAGEFILE_QUOTA_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_COMMITMENT_LIMIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_LE_FORMAT, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_NOT_MZ, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_PROTECT, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_IMAGE_WIN_16, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_SERVER_CONFLICT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TIME_DIFFERENCE_AT_DC, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SYNCHRONIZATION_REQUIRED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DLL_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)126)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OPEN_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IO_PRIVILEGE_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ORDINAL_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)182)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ENTRYPOINT_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)127)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONTROL_C_EXIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOCAL_DISCONNECT, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REMOTE_DISCONNECT, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REMOTE_RESOURCES, ((uint)ERRDOS << 16) | ((uint)51)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LINK_FAILED, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LINK_TIMEOUT, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_CONNECTION, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ADDRESS, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DLL_INIT_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MISSING_SYSTEMFILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNHANDLED_EXCEPTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_APP_INIT_FAILURE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PAGEFILE_CREATE_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_PAGEFILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_LEVEL, ((uint)ERRDOS << 16) | ((uint)ERRunknownlevel)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_WRONG_PASSWORD_CORE, ((uint)ERRDOS << 16) | ((uint)86)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILLEGAL_FLOAT_CONTEXT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PIPE_BROKEN, ((uint)ERRDOS << 16) | ((uint)109)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REGISTRY_CORRUPT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REGISTRY_IO_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_EVENT_PAIR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNRECOGNIZED_VOLUME, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SERIAL_NO_DEVICE_INITED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_ALIAS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMBER_NOT_IN_ALIAS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MEMBER_IN_ALIAS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ALIAS_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_NOT_GRANTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_SECRETS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SECRET_TOO_LONG, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INTERNAL_DB_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FULLSCREEN_MODE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_CONTEXT_IDS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGON_TYPE_NOT_GRANTED, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_REGISTRY_FILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NT_CROSS_ENCRYPTION_REQUIRED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DOMAIN_CTRLR_CONFIG_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FT_MISSING_MEMBER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILL_FORMED_SERVICE_ENTRY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ILLEGAL_CHARACTER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNMAPPABLE_CHARACTER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNDEFINED_CHARACTER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOPPY_VOLUME, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOPPY_ID_MARK_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOPPY_WRONG_CYLINDER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOPPY_UNKNOWN_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FLOPPY_BAD_REGISTERS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DISK_RECALIBRATE_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DISK_OPERATION_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DISK_RESET_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SHARED_IRQ_BUSY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FT_ORPHANING, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000016e, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000016f, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000170, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000171, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PARTITION_FAILURE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_BLOCK_LENGTH, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_NOT_PARTITIONED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNABLE_TO_LOCK_MEDIA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNABLE_TO_UNLOAD_MEDIA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EOM_OVERFLOW, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_MEDIA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000179, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_SUCH_MEMBER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_MEMBER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_KEY_DELETED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_LOG_SPACE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_SIDS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LM_CROSS_ENCRYPTION_REQUIRED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_KEY_HAS_CHILDREN, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CHILD_MUST_BE_VOLATILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_CONFIGURATION_ERROR, ((uint)ERRDOS << 16) | ((uint)87)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DRIVER_INTERNAL_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_DEVICE_STATE, ((uint)ERRDOS << 16) | ((uint)22)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IO_DEVICE_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEVICE_PROTOCOL_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BACKUP_CONTROLLER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOG_FILE_FULL, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_LATE, ((uint)ERRDOS << 16) | ((uint)19)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_TRUST_LSA_SECRET, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_TRUST_SAM_ACCOUNT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRUSTED_DOMAIN_FAILURE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRUSTED_RELATIONSHIP_FAILURE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EVENTLOG_FILE_CORRUPT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EVENTLOG_CANT_START, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRUST_FAILURE, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MUTANT_LIMIT_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETLOGON_NOT_STARTED, ((uint)ERRDOS << 16) | ((uint)ERRinvgroup)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCOUNT_EXPIRED, ((uint)ERRSRV << 16) | ((uint)2239)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_POSSIBLE_DEADLOCK, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETWORK_CREDENTIAL_CONFLICT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REMOTE_SESSION_LIMIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_EVENTLOG_FILE_CHANGED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOLOGON_WORKSTATION_TRUST_ACCOUNT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOLOGON_SERVER_TRUST_ACCOUNT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DOMAIN_TRUST_INCONSISTENT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FS_DRIVER_REQUIRED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_USER_SESSION_KEY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_USER_SESSION_DELETED, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RESOURCE_LANG_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INSUFF_SERVER_RESOURCES, ((uint)ERRDOS << 16) | ((uint)ERRnomem)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_BUFFER_SIZE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ADDRESS_COMPONENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_ADDRESS_WILDCARD, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_ADDRESSES, ((uint)ERRDOS << 16) | ((uint)68)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ADDRESS_ALREADY_EXISTS, ((uint)ERRDOS << 16) | ((uint)52)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ADDRESS_CLOSED, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_DISCONNECTED, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_RESET, ((uint)ERRDOS << 16) | ((uint)64)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_NODES, ((uint)ERRDOS << 16) | ((uint)68)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_ABORTED, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_TIMED_OUT, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_NO_RELEASE, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_NO_MATCH, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_RESPONDED, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_INVALID_ID, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TRANSACTION_INVALID_TYPE, ((uint)ERRDOS << 16) | ((uint)59)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_SERVER_SESSION, ((uint)ERRDOS << 16) | ((uint)ERRunsup)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_CLIENT_SESSION, ((uint)ERRDOS << 16) | ((uint)ERRunsup)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CANNOT_LOAD_REGISTRY_FILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DEBUG_ATTACH_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_SYSTEM_PROCESS_TERMINATED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DATA_NOT_ACCEPTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_BROWSER_SERVERS_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_VDM_HARD_ERROR, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DRIVER_CANCEL_TIMEOUT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REPLY_MESSAGE_MISMATCH, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MAPPED_ALIGNMENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IMAGE_CHECKSUM_MISMATCH, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOST_WRITEBEHIND_DATA, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CLIENT_SERVER_PARAMETERS_INVALID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PASSWORD_MUST_CHANGE, ((uint)ERRSRV << 16) | ((uint)2242)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NOT_TINY_STREAM, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RECOVERY_FAILURE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_STACK_OVERFLOW_READ, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FAIL_CHECK, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DUPLICATE_OBJECTID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_OBJECTID_EXISTS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONVERT_TO_LARGE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RETRY, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FOUND_OUT_OF_SCOPE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ALLOCATE_BUCKET, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROPSET_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_MARSHALL_OVERFLOW, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_VARIANT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DOMAIN_CONTROLLER_NOT_FOUND, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ACCOUNT_LOCKED_OUT, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_HANDLE_NOT_CLOSABLE, ((uint)ERRDOS << 16) | ((uint)ERRbadfid)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_REFUSED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_GRACEFUL_DISCONNECT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ADDRESS_ALREADY_ASSOCIATED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_ADDRESS_NOT_ASSOCIATED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_INVALID, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_ACTIVE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NETWORK_UNREACHABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_HOST_UNREACHABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PROTOCOL_UNREACHABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PORT_UNREACHABLE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REQUEST_ABORTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_ABORTED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_COMPRESSION_BUFFER, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_USER_MAPPED_FILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_AUDIT_FAILED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TIMER_RESOLUTION_NOT_SET, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_CONNECTION_COUNT_LIMIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGIN_TIME_RESTRICTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LOGIN_WKSTA_RESTRICTION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IMAGE_MP_UP_MISMATCH, ((uint)ERRDOS << 16) | ((uint)193)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024a, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024b, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024c, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024d, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024e, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000024f, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INSUFFICIENT_LOGON_INFO, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_DLL_ENTRYPOINT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_BAD_SERVICE_ENTRYPOINT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LPC_REPLY_LOST, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IP_ADDRESS_CONFLICT1, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_IP_ADDRESS_CONFLICT2, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_REGISTRY_QUOTA_LIMIT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PATH_NOT_COVERED, ((uint)ERRSRV << 16) | ((uint)ERRbadtype)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_NO_CALLBACK_ACTIVE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_LICENSE_QUOTA_EXCEEDED, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PWD_TOO_SHORT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PWD_TOO_RECENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PWD_HISTORY_CONFLICT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000025d, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_PLUGPLAY_NO_DEVICE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_UNSUPPORTED_COMPRESSION, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_HW_PROFILE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_INVALID_PLUGPLAY_DEVICE_PATH, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DRIVER_ORDINAL_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)182)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_DRIVER_ENTRYPOINT_NOT_FOUND, ((uint)ERRDOS << 16) | ((uint)127)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_RESOURCE_NOT_OWNED, ((uint)ERRDOS << 16) | ((uint)288)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_TOO_MANY_LINKS, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_QUOTA_LIST_INCONSISTENT, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>(STATUS_FILE_IS_OFFLINE, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000026e, ((uint)ERRDOS << 16) | ((uint)21)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000281, ((uint)ERRDOS << 16) | ((uint)161)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028a, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028b, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028c, ((uint)ERRHRD << 16) | ((uint)ERRgeneral)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028d, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028e, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000028f, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc0000290, ((uint)ERRDOS << 16) | ((uint)ERRnoaccess)));
    ntStatus2DosError.insert(std::make_pair<NtStatus, uint>((NtStatus)0xc000029c, ((uint)ERRDOS << 16) | ((uint)ERRbadfunc)));
}

void ErrorConvertor::InitializeApiRet2NtStatus()
{
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_SUCCESS, STATUS_OK));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_FILE_NOT_FOUND, STATUS_OBJECT_NAME_NOT_FOUND));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_PATH_NOT_FOUND, STATUS_OBJECT_PATH_NOT_FOUND));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_ACCESS_DENIED, STATUS_ACCESS_DENIED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_SHARING_VIOLATION, STATUS_SHARING_VIOLATION));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_LOCK_VIOLATION, STATUS_LOCK_NOT_GRANTED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_INVALID_HANDLE, STATUS_INVALID_HANDLE));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_FILE_EXISTS, STATUS_OBJECT_NAME_COLLISION));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_INVALID_PARAMETER, STATUS_INVALID_PARAMETER));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_INVALID_NAME, STATUS_OBJECT_NAME_INVALID));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_DIR_NOT_EMPTY, STATUS_DIRECTORY_NOT_EMPTY));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_INVALID_FUNCTION, STATUS_ILLEGAL_FUNCTION));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_NOT_LOCKED, STATUS_RANGE_NOT_LOCKED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_ALREADY_EXISTS, STATUS_OBJECT_NAME_COLLISION));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_PRIVILEGE_NOT_HELD, STATUS_PRIVILEGE_NOT_HELD));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_EA_LIST_INCONSISTENT, STATUS_EA_LIST_INCONSISTENT));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_DIRECTORY, STATUS_NOT_A_DIRECTORY));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_NOT_A_REPARSE_POINT, STATUS_NOT_A_REPARSE_POINT));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_NO_MORE_FILES, STATUS_NO_MORE_FILES));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_IO_PENDING, STATUS_PENDING));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_HANDLE_EOF, STATUS_END_OF_FILE));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_NOT_SUPPORTED, STATUS_NOT_SUPPORTED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_OUTOFMEMORY, STATUS_NO_MEMORY));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_CANCELLED, STATUS_CANCELLED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_LOCK_VIOLATION, STATUS_FILE_LOCK_CONFLICT));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_CHECKOUT_REQUIRED, STATUS_CHECKOUT_REQUIRED));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_LABEL_TOO_LONG, STATUS_NAME_TOO_LONG));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_FUNCTION_FAILED, STATUS_UNSUCCESSFUL));
    apiRet2NtStatus.insert(std::make_pair<ApiRet, NtStatus>(ERROR_CONNECTION_INVALID, STATUS_CONNECTION_INVALID));
}
