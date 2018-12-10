#pragma once

#include "crypto\CryptAes.h"
#include "crypto\AesCmac128.h"

// Label for generate Session.SigningKey
// SMB311
#define SMBSigningKey "SMBSigningKey"
// otherwise
// Label
#define SMB2AESCMAC "SMB2AESCMAC"
// context
#define SmbSign "SmbSign"

// Label for generate Session.EncryptionKey
// SMB311
#define SMBC2SCipherKey "SMBC2SCipherKey"
// otherwise
// Label
#define SMB2AESCCM "SMB2AESCCM"
// context
#define ServerIn "ServerIn "

// Label for generate Session.DecryptionKey
// SMB311
#define SMBS2CCipherKey "SMBS2CCipherKey"
// otherwise
// Label the same as for Session.EncryptionKey
// context
#define ServerOut "ServerOut"

// Label for generate Session.ApplicationKey
// SMB311
#define SMBAppKey "SMBAppKey"
// otherwise
// Label 
#define SMB2APP "SMB2APP"
// context
#define SmbRpc "SmbRpc"

namespace IMFS
{
    class CryptAES_Utility
    {
    public:
        enum Algorithm { SP800108_CTR_HMAC_ALGORITHM };
        /// <summary>
        /// Generate Key
        /// </summary>
        static NTSTATUS GenerateKey(Algorithm algorithm, AESModeOperation mode, const uint8_t* blob, size_t blobSize, std::string label, std::string context, std::vector<uint8_t>& key);
        static NTSTATUS GenerateKey(Algorithm algorithm, AESModeOperation mode, const uint8_t* blob, size_t blobSize, std::string label, const std::vector<uint8_t>& context, std::vector<uint8_t>& key);
        /// <summary>
        /// Decrypt data with use Algorithm - BCRYPT_AES_ALGORITHM on CCM mode
        /// </summary>
        static NTSTATUS Decrypt(AESModeOperation mode, const uint8_t* key, size_t keySize,
            const uint8_t* src, size_t srcSize,
            uint8_t* target, size_t& len,
            const uint8_t* nonce, size_t nonceSize,
            const uint8_t* addData, size_t addDataSize,
            const uint8_t* signature, size_t signatureSize);
        /// <summary>
        /// Encrypt data with use Algorithm - BCRYPT_AES_ALGORITHM on CCM mode
        /// </summary>
        static NTSTATUS Encrypt(AESModeOperation mode, const uint8_t* key, size_t keySize,
            const uint8_t* src, size_t srcSize,
            uint8_t* target, size_t& len,
            const uint8_t* nonce, size_t nonceSize,
            const uint8_t* addData, size_t addDataSize,
            uint8_t* signature, size_t signatureSize);
        /// <summary>
        /// Get Signature with use Algorithm - BCRYPT_AES_CMAC_ALGORITHM
        /// </summary>
        static NTSTATUS GetSignature(const uint8_t* key, size_t keySize, const uint8_t* src, size_t srcSize, std::vector<uint8_t>& signature);

        /// <summary>
        /// Get Salt for SMB2_PREAUTH_INTEGRITY_CAPABILITIES negotiate context with use Algorithm - PROV_RSA_FULL
        /// </summary>
        static void GenerateSalt(std::vector<uint8_t>& salt);
    protected:
        static NTSTATUS GenerateKeyBySP800108_CTR_HMAC_ALGORITHM(const std::vector<uint8_t>& blob, const std::vector<uint8_t>& label, const std::vector<uint8_t>& context, std::vector<uint8_t>& key);
    };
}
