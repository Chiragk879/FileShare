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
#include <stdint.h>
#include <vector>

#include "CryptAES.h"

#pragma comment(lib, "bcrypt.lib") 

// Since encryption algorithm BCRYPT_AES_CMAC_ALGORITHM is supported begins Windows 8
// it's workaround: The idea of implementation was seen in Microsoft compliance tests 
// in File Server Family Test Suite" (file AesCmacCrypto.cs)

namespace IMFS
{
    class AesCmac128
    {
    public:
        AesCmac128(CryptAES& encryptor);
        ~AesCmac128();

        /// <summary>
        /// Encrypt message By AES_CMAC_128
        /// </summary>
        /// <param name="src">Message to be encrypted.</param>
        /// <param name="srcSize">The number of bytes in message to encrypt.</param>
        /// <param name="signature">Message has been encrypted.</param>
        NTSTATUS GetSignature(const uint8_t* src, size_t srcSize, std::vector<uint8_t>& signature);

    private:
        /// <summary>
        /// Bitwise XOR operator
        /// </summary>
        void Xor128(const uint8_t* dataA, int32_t offsetA, const uint8_t* dataB, int32_t offsetB, uint8_t* output);
        void Xor128(const uint8_t* dataA, const uint8_t* dataB, uint8_t* output);
        /// <summary>
        /// Shift "input" one bit to the left
        /// </summary>
        void LeftshiftOnebit(const uint8_t* input, uint8_t* output);

        /// <summary>
        /// Encrypt message by AES with given secret key and key size.
        /// </summary>
        /// <param name="message">Message to be encrypted.</param>
        /// <param name="messageSize">The number of bytes in message to encrypt.</param>
        /// <param name="encryptedMessage">Message has been encrypted.</param>
        NTSTATUS EncryptMessageByAes(const uint8_t* message, size_t messageSize, uint8_t* encryptedMessage);

        /// <summary>
        /// padding is the concatenation of source data and a single '1',
        /// followed by the minimum number of '0's, so that the total length is equal to 128 bits.
        /// </summary>
        /// <param name="sourceData">The original data.</param>
        /// <param name="offset">The offset where padding starts.</param>
        /// <param name="length">Length for padding.</param>
        /// <param name="paddedData">The padded data.</param>
        void Padding(const uint8_t* sourceData, int32_t offset, int32_t length, uint8_t* paddedData);
        /// <summary>
        /// The subkey generation algorithm
        /// </summary>
        /// <param name="firstSubKey">128-bit first subkey</param>
        /// <param name="secondSubKey">128-bit second subkey</param>
        NTSTATUS GenerateSubKey(uint8_t* firstSubKey, uint8_t* secondSubKey);

    private:
        CryptAES& m_encryptor;
    };
};

