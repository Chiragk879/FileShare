#include "stdafx.h"

using namespace IMFS;

AuthInfo :: AuthInfo()
{
	LoginName = NULL;
	AccessToken = 0;
}

AuthInfo :: ~AuthInfo()
{
	if (LoginName != NULL)
	{
		::SysFreeString(LoginName);
		LoginName = NULL;
	}
}

AuthInfo& 
AuthInfo :: operator=(const AuthInfo& copy)
{
	AccessToken = copy.AccessToken;

	if (LoginName != NULL)
	{
		::SysFreeString(LoginName);
		LoginName = NULL;
	}

	if (copy.LoginName != NULL)
	{
		LoginName = ::SysAllocString(copy.LoginName);
	}

	SessionKey = copy.SessionKey;

	return *this;
}
