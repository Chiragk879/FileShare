#include "stdafx.h"
#include "KeysSection.h"
#include "..\CommonFileSystem\PasswordsManager.h"

#include <Lmcons.h>

using namespace IMFS;

KeysSection::KeysSection()
{
}

KeysSection::~KeysSection()
{
}

void KeysSection::GetData()
{
    TCHAR name[UNLEN + 1];
    DWORD size = UNLEN + 1;
    if (GetUserName((TCHAR*)name, &size))
    {
        IMLOG_INFO(L"The user '%s' reads the credentials.", name);
    }

    if (ERROR_SUCCESS != PasswordsManager::GetCredential(PasswordsManager::Unlock, m_UnlockUserName, m_UnlockPassword) || m_UnlockUserName.empty() || m_UnlockPassword.empty())
    {
        IMLOG_WARNING(L"Credentials for unlocking files not found.");
        m_validUnlockKey = false;
    }
    else
    {
        m_validUnlockKey = true;
    }


    string userName = L"";
    if (ERROR_SUCCESS != PasswordsManager::GetCredential(PasswordsManager::Impersonation, userName, m_ImpersonationPassword) || m_ImpersonationPassword.empty())
    {
        IMLOG_WARNING(L"Impersonation credentials not found.");
        m_validImpersonationKey = false;
    }
    else
    {
        m_validImpersonationKey = true;
    }
    if (m_validUnlockKey && m_validImpersonationKey)
        IMLOG_INFO(L"Reading credentials was successful from the Credential Manager.");
}

void KeysSection::GetUnlockCredentials(string& UserName, string& Password) const
{
    UserName = m_UnlockUserName;
    Password = m_UnlockPassword;
}
