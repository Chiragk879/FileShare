#pragma once

namespace IMFS
{
    /// Represents a dialect configuration element within the configuration file.
    class DialectElement : public ConfigurationElement
    {
    public:
        /// Gets the id of dialect.
        int Id = 0;

        /// Get dialect enabled state.
        bool Enabled = false;

        /// Gets the dialect name.
        string Name = L"";

        /// Gets the dialect MaxTransactSize
        uint32_t MaxTransactSize = 65536;

        /// Gets the dialect MaxReadSize
        uint32_t MaxReadSize = 65536;

        /// Gets the dialect MaxWriteSize
        uint32_t MaxWriteSize = 65536;

        uint32_t DialectCapabilities = SMB2_GLOBAL_CAP_NONE;

        /// Support Handle Cashing for leases
        bool SupportHandleCashing = true;

        /// A Boolean that, if set, indicates that the server will reject any unencrypted messages. 
        /// This flag is applicable only if EncryptData is TRUE or if Share.EncryptData (as defined in section 3.3.1.6) is TRUE.
        bool RejectUnencryptedAccess = true;

        /// Gets the dialect element's key string value.
        string ToString();

    public:
        DialectElement() = default;
        virtual ~DialectElement() = default;
    };
}
