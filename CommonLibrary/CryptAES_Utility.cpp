#include "stdafx.h"
#include "CryptAES_Utility.h"
#include "crypto\HmacKeyFactory.h"

#include <random>

using namespace IMFS;

NTSTATUS CryptAES_Utility::GenerateKey(Algorithm algorithm, AESModeOperation mode, const uint8_t* blob, size_t blobSize, std::string label, std::string context, std::vector<uint8_t>& key)
{
    // transform context string to byte array with terminating symbols
    std::vector<uint8_t> c;
    c.assign(context.begin(), context.end());
    c.push_back('\0'); /// + 1 (terminating symbol)
    return CryptAES_Utility::GenerateKey(algorithm, mode, blob, blobSize, label, c, key);
}

NTSTATUS CryptAES_Utility::GenerateKey(Algorithm algorithm, AESModeOperation /*unused*/, const uint8_t* blob, size_t blobSize, std::string label, const std::vector<uint8_t>& context, std::vector<uint8_t>& key)
{
    if (algorithm != SP800108_CTR_HMAC_ALGORITHM)
    {
        IMLOG_ERROR(L"Requested algorithm not supported.");
        return STATUS_UNSUCCESSFUL;
    }
    // transform label strings to byte array with terminating symbol
    std::vector<uint8_t> l,b;
    l.assign(label.begin(), label.end());
    l.push_back('\0'); /// + 1 (terminating symbol)
    b.assign(blob, blob+blobSize);
    return GenerateKeyBySP800108_CTR_HMAC_ALGORITHM(b, l, context, key);
}

NTSTATUS CryptAES_Utility::GenerateKeyBySP800108_CTR_HMAC_ALGORITHM(const std::vector<uint8_t>& blob, const std::vector<uint8_t>& label, const std::vector<uint8_t>& context, std::vector<uint8_t>& key)
{
    const auto factory = HmacKeyFactory::GetInstance();
    if (!factory)
    {
        IMLOG_ERROR(L"HmacKeyFactory instance unavailable.");
        return STATUS_UNSUCCESSFUL;
    }

    auto hmacsha256 = factory->CreateKey(HmacKeyType::HMAC_SHA256, blob);

    std::vector<uint8_t> in, out;
    in.insert(in.end(), { 0, 0, 0, 1 });
    in.insert(in.end(), label.begin(), label.end());
    in.push_back(0x00); /// 0x00 as delimiter
    in.insert(in.end(), context.begin(), context.end());
    in.insert(in.end(), { 0, 0, 0, 128 });

    if (!hmacsha256->CalcHmac(in.data(), in.size(), out))
    {
        IMLOG_ERROR(L"HmacKeyType: Cannot calculate HMAC_SHA256.");
        return STATUS_UNSUCCESSFUL;
    }

    key.resize(16, 0);

    std::copy(out.begin(), out.begin() + key.size(), key.begin());
    return STATUS_SUCCESS;
}

NTSTATUS CryptAES_Utility::Decrypt(AESModeOperation mode, const uint8_t* key, size_t keySize,
    const uint8_t* src, size_t srcSize,
    uint8_t* target, size_t& len,
    const uint8_t* nonce, size_t nonceSize,
    const uint8_t* addData, size_t addDataSize,
    const uint8_t* signature, size_t signatureSize)
{
    CryptAES cryptAES;
    // Create Algorytm
    NTSTATUS status = cryptAES.CreateAlgorytm(BCRYPT_AES_ALGORITHM, mode);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"Failed to open AES algorithm %s provider: 0x%08X", BCRYPT_AES_ALGORITHM, status);
        return status;
    }
    // Import Key
    status = cryptAES.ImportKey(key, keySize);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"СryptAES ImportKey failed: NTSTATUS = 0x%08X", status);
        return status;
    }
    // Decrypt message
    status = cryptAES.Decrypt(src, srcSize, target, len, nonce, nonceSize, addData, addDataSize, signature, signatureSize);
    if (status != STATUS_SUCCESS)
        IMLOG_ERROR(L"CCM mode decryption failed: NTSTATUS = 0x%08X", status);

    return status;
}

NTSTATUS CryptAES_Utility::Encrypt(AESModeOperation mode, const uint8_t* key, size_t keySize,
    const uint8_t* src, size_t srcSize,
    uint8_t* target, size_t& len,
    const uint8_t* nonce, size_t nonceSize,
    const uint8_t* addData, size_t addDataSize,
    uint8_t* signature, size_t signatureSize)
{
    CryptAES cryptAES;
    // Create Algorytm
    NTSTATUS status = cryptAES.CreateAlgorytm(BCRYPT_AES_ALGORITHM, mode);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"Failed to open AES algorithm %s provider: 0x%08X", BCRYPT_AES_ALGORITHM, status);
        return status;
    }
    // Import Key
    status = cryptAES.ImportKey(key, keySize);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"СryptAES ImportKey failed: NTSTATUS = 0x%08X", status);
        return status;
    }
    // Encrypt message
    status = cryptAES.Encrypt(src, srcSize, target, len, nonce, nonceSize, addData, addDataSize, signature, signatureSize);
    if (status != STATUS_SUCCESS)
        IMLOG_ERROR(L"CCM mode encryption failed: NTSTATUS = 0x%08X", status);

    return status;
}

NTSTATUS CryptAES_Utility::GetSignature(const uint8_t* key, size_t keySize, const uint8_t* src, size_t srcSize, std::vector<uint8_t>& signature)
{
    CryptAES cryptAES;
    NTSTATUS status = STATUS_SUCCESS;

#if 0 //Windows Server 2012 does not support the algorithm BCRYPT_AES_CMAC_ALGORITHM March 2017
    // Create Algorytm
    status = cryptAES.CreateAlgorytm(BCRYPT_AES_CMAC_ALGORITHM, AESModeOperation::AESMO_NA, BCRYPT_ALG_HANDLE_HMAC_FLAG);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"Failed to open AES algorithm %s provider: 0x%08X", BCRYPT_AES_CMAC_ALGORITHM, status);
        return status;
    }
    // Get Signature
    status = cryptAES.GetSignature(key, keySize, src, srcSize, signature);
    if (status != STATUS_SUCCESS)
        IMLOG_ERROR(L"СryptAES GetSignature failed: NTSTATUS = 0x%08X", status);

#else
    // Create Algorytm
    status = cryptAES.CreateAlgorytm(BCRYPT_AES_ALGORITHM);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"Failed to open AES algorithm %s provider: 0x%08X", BCRYPT_AES_ALGORITHM, status);
        return status;
    }
    // Import Key
    status = cryptAES.ImportKey(key, keySize);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"СryptAES ImportKey failed: NTSTATUS = 0x%08X", status);
        return status;
    }

    AesCmac128 aesCmac(cryptAES);
    status = aesCmac.GetSignature(src, srcSize, signature);
    if (status != STATUS_SUCCESS)
    {
        IMLOG_ERROR(L"СryptAES GetSignature failed: NTSTATUS = 0x%08X", status);
    }
#endif

    return status;
}

void CryptAES_Utility::GenerateSalt(std::vector<uint8_t>& salt)
{
    size_t length = salt.size();
    if (length == 0)
        return;
    byte* genSalt = (byte*)salt.data();
    std::independent_bits_engine<std::mt19937, 64, uint64_t> engineNonce;
    std::generate(genSalt, genSalt + length, [&]() {return static_cast<uint8_t>(engineNonce()); });
}

