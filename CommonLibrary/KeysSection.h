#pragma once

namespace IMFS
{
    /// <summary>
    /// Represents service password section within the configuration.
    /// </summary>
    class KeysSection : public ConfigurationSection
    {
        /// <summary>
        /// Gets a configuration element containing a service passwords.
        /// </summary>
    public:
        KeysSection();
        virtual ~KeysSection();
        /// <summary>
        /// Get data form Credential Manager.
        /// </summary>
        void GetData();
        /// <summary>
        /// Get credential for unlock files.
        /// </summary>
        void GetUnlockCredentials(string& UserName, string& Password) const;
        /// <summary>
        /// Get impersonation password.
        /// </summary>
        string GetImpersonationPassword() const { return m_ImpersonationPassword; }
        /// <summary>
        /// Check valid credentials.
        /// </summary>
        bool IsValidUnlockCredentials() const { return m_validUnlockKey; }
        bool IsValidImpersonationCredentials() const { return m_validImpersonationKey; }
    protected:
        string m_UnlockUserName = L"";
        string m_UnlockPassword = L"";
        string m_ImpersonationPassword = L"";

        bool m_validUnlockKey = false;
        bool m_validImpersonationKey = false;
    };
}
