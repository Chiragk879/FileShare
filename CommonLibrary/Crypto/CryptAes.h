#pragma once

//
// Include ntstatus before Windows.h is included then define
// WIN32_NO_STATUS so that there is no conflict between NT DDK
// status codes and Win32

#undef WIN32_NO_STATUS
#include <ntstatus.h>
#define WIN32_NO_STATUS 1
#include <Windows.h>

#include <bcrypt.h>
#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>

#pragma comment(lib, "bcrypt.lib") 

namespace IMFS
{
    class AESKeyState {
    public:

        AESKeyState(size_t len) : handle(0) {
            keyObj = new uint8_t[len];
        }

        ~AESKeyState() {
            // Must destroy the handle BEFORE freeing the key object
            if (handle) {
                BCryptDestroyKey(handle);
            }
            delete[] keyObj;
        }

        BCRYPT_KEY_HANDLE handle = NULL;
        uint8_t* keyObj = NULL;
    private:
        /// <summary>
        /// Copy constructor
        /// @param src AESKeyState to be copied.
        /// </summary>
        AESKeyState(const AESKeyState& src) {/* private copy constructor to prevent copying */ }
        /// <summary>
        /// Assignment operator
        /// @param src source AESKeyState
        /// @return copy of AESKeyState
        /// </summary>
        AESKeyState& operator=(const AESKeyState& src) { return *this; }
    };

    enum AESModeOperation
    {
        AESMO_NA = 0,
        AESMO_GCM = 1,
        AESMO_CCM = 2
    };

    class CryptAES
    {
    public:
        CryptAES() = default;
        ~CryptAES();
        /// <summary>
        /// Create Algorithm Provider
        /// </summary>
        NTSTATUS CreateAlgorytm(LPCWSTR pszAlgId, AESModeOperation mode = AESModeOperation::AESMO_NA, ULONG flag = 0);
        /// <summary>
        /// Import Key for Algorithm Provider
        /// </summary>
        NTSTATUS ImportKey(const uint8_t* key, size_t sizeKey);
        /// <summary>
        /// Decrypt data
        /// </summary>
        NTSTATUS Decrypt(const uint8_t* src, size_t srcSize, uint8_t* target, size_t& len, const uint8_t* nonce,
            size_t nonceSize, const uint8_t* addData, size_t addDataSize, const uint8_t* tag, size_t tagSize);
        /// <summary>
        /// Encrypt data
        /// </summary>
        NTSTATUS Encrypt(const uint8_t* src, size_t srcSize, uint8_t* target, size_t& len, const uint8_t* nonce,
            size_t nonceSize, const uint8_t* addData, size_t addDataSize, uint8_t* signature, size_t signatureSize);
        /// <summary>
        /// Get Signature
        /// </summary>
        // Use workaround based on algorithm BCRYPT_AES_ALGORITHM
        NTSTATUS GetSignature(const uint8_t* src, size_t srcSize, uint8_t* signature);
        // Use Algorithm - BCRYPT_AES_CMAC_ALGORITHM
        NTSTATUS GetSignature(const uint8_t* key, size_t keySize, const uint8_t* src, size_t srcSize, std::vector<uint8_t>& signature);

    protected:
        /// <summary>
        /// Get Property
        /// </summary>
        NTSTATUS CryptGetProperty(LPCWSTR pszProperty, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult);
        BCRYPT_ALG_HANDLE m_alg_handle = NULL;
        AESModeOperation m_mode = AESModeOperation::AESMO_NA;
        std::shared_ptr<AESKeyState> m_pkeyState = nullptr;
    };
}
