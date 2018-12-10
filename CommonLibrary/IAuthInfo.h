#pragma once

namespace IMFS
{
    class IAuthInfo
    {
    public:
        virtual ~IAuthInfo() = default;

        /// <summary>
        /// Get handle of access token associated with authenticated user context.
        /// </summary>
        virtual HANDLE GetAccessToken() const = 0;

        /// <summary>
        /// Return string with authenticated user login.
        /// </summary>
        virtual IMFS::string GetUserLogin() const = 0;

        /// <summary>
        /// Impersonates context.
        /// </summary>
        virtual bool ImpersonateContext() = 0;

        /// <summary>
        /// Reverts impersonation.
        /// </summary>
        virtual bool RevertContext() = 0;
    };
}
