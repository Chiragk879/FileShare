#include "stdafx.h"
#include "ComputerName.h"

IMFS::string m_computerName;

const IMFS::string& ComputerName()
{
    if (m_computerName.empty())
    {
        _TCHAR computerName[MAX_COMPUTERNAME_LENGTH + 1];
        DWORD dwSize = sizeof(computerName);
#pragma warning(suppress: 6386)
        GetComputerName(computerName, &dwSize);

        m_computerName = computerName;
    }
    return m_computerName;
}
