#include "stdafx.h"
#include "AesCmac128.h"

#include <memory>

using namespace IMFS;

AesCmac128::AesCmac128(CryptAES& encryptor) 
    : m_encryptor(encryptor)
{
}

AesCmac128::~AesCmac128()
{
}

void AesCmac128::Xor128(const uint8_t* dataA, int32_t offsetA, const uint8_t* dataB, int32_t offsetB, uint8_t* output)
{
    for (int32_t i = 0; i < 16; i++)
    {
        output[i] = (uint8_t)(dataA[offsetA + i] ^ dataB[offsetB + i]);
    }
}

void AesCmac128::Xor128(const uint8_t* dataA, const uint8_t* dataB, uint8_t* output)
{
    Xor128(dataA, 0, dataB, 0, output);
}

void AesCmac128::LeftshiftOnebit(const uint8_t* input, uint8_t* output)
{
    uint8_t overflow = 0;
    for (int32_t i = 15; i >= 0; i--)
    {
        output[i] = (uint8_t)(input[i] << 1);
        output[i] |= overflow;
        overflow = (uint8_t)((input[i] & 0x80) == 0x80 ? 1 : 0);
    }
}

NTSTATUS AesCmac128::EncryptMessageByAes(const uint8_t* message, size_t messageSize, uint8_t* encryptedMessage)
{
    // Encrypt message
    return m_encryptor.GetSignature(message, messageSize, encryptedMessage);
}

NTSTATUS AesCmac128::GenerateSubKey(uint8_t* firstSubKey, uint8_t* secondSubKey)
{
    uint8_t L[16];
    // For CMAC Calculation
    // const_Zero is 0x00000000000000000000000000000000     
    // const_Rb   is 0x00000000000000000000000000000087
    uint8_t const_Zero[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
    uint8_t const_Rb[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87 };
    uint8_t tmp[16];


    NTSTATUS status = EncryptMessageByAes(const_Zero, 16, L); // AES-128 with key K is applied to an all-zero input block
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    if ((L[0] & 0x80) == 0)
    { /* If MSB(L) = 0, then K1 = L << 1 */
        LeftshiftOnebit(L, firstSubKey);
    }
    else
    {    /* Else K1 = ( L << 1 ) (+) Rb */
        LeftshiftOnebit(L, tmp);
        Xor128(tmp, const_Rb, firstSubKey);
    }

    if ((firstSubKey[0] & 0x80) == 0)
    { // If MSB(K1) = 0, then K2 = L << 1 
        LeftshiftOnebit(firstSubKey, secondSubKey);
    }
    else
    { // Else K2 ( L << 1 ) (+) Rb 
        LeftshiftOnebit(firstSubKey, tmp);
        Xor128(tmp, const_Rb, secondSubKey);
    }

    return status;
}

void AesCmac128::Padding(const uint8_t* sourceData, int32_t offset, int32_t length, uint8_t* paddedData)
{
    /* original last block */
    for (int32_t i = 0; i < 16; i++)
    {
        if (i < length)
        {
            paddedData[i] = sourceData[offset + i];
        }
        else if (i == length)
        {
            paddedData[i] = 0x80;
        }
        else
        {
            paddedData[i] = 0x00;
        }
    }
}

NTSTATUS AesCmac128::GetSignature(const uint8_t* message, size_t messageSize, std::vector<uint8_t>& signature)
{
    NTSTATUS status = STATUS_SUCCESS;
    int32_t length = static_cast<int32_t>(messageSize);

    uint8_t X[16];
    uint8_t Y[16];
    uint8_t M_last[16];
    uint8_t padded[16];
    uint8_t K1[16];
    uint8_t K2[16];

    int32_t n = 0;
    int32_t i = 0;
    int32_t flag = 0;

    if ((status = GenerateSubKey(K1, K2)) != STATUS_SUCCESS)
    {
        return status;
    }

    n = (length + 15) / 16;       /* n is number of rounds */

    if (n == 0)
    {
        n = 1;
        flag = 0;
    }
    else
    {
        if ((length % 16) == 0)
        { /* last block is a complete block */
            flag = 1;
        }
        else
        { /* last block is not complete block */
            flag = 0;
        }
    }

    if (flag != 0)
    { /* last block is complete block */
        Xor128(message, 16 * (n - 1), K1, 0, M_last);
    }
    else
    {
        Padding(message, 16 * (n - 1), length % 16, padded);
        Xor128(padded, K2, M_last);
    }

    for (i = 0; i < 16; i++)
    {
        X[i] = 0;
    }

    for (i = 0; i < n - 1; i++)
    {
        Xor128(X, 0, message, 16 * i, Y);
        if ((status = EncryptMessageByAes(Y, 16, X)) != STATUS_SUCCESS)
        {
            return status;
        }
    }

    Xor128(X, M_last, Y);
    if ((status = EncryptMessageByAes(Y, 16, X)) != STATUS_SUCCESS)
    {
        return status;
    }

    if (signature.size() < 16)
    {
        signature.resize(16);
    }

    for (i = 0; i < 16; i++)
    {
        signature[i] = X[i];
    }

    return status;
}

