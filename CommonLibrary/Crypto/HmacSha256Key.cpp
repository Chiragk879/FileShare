#include "stdafx.h"

#include "HmacSha256Key.h"

#include "..\logmgr.h"


#define _HMAC_SHA256_KEY_SIZE 32

using namespace IMFS;

const size_t HmacSha256Key::HMAC_SHA256_KEY_SIZE = _HMAC_SHA256_KEY_SIZE;

struct hmac_sha_256_key_blob_t
{
    BLOBHEADER hdr;
    DWORD dwKeySize;
    BYTE keyData[1];
};

HmacSha256Key::HmacSha256Key(HCRYPTPROV hProv, const std::vector<uint8_t>& key):
m_hKey(0)
{
    hmac_sha_256_key_blob_t* keyBlob = nullptr;

    DWORD keySize = static_cast<DWORD>(key.size());
    DWORD keyBlobSize = keySize + sizeof(hmac_sha_256_key_blob_t) - 1;
    keyBlob = static_cast<hmac_sha_256_key_blob_t*>(malloc(keyBlobSize));
    if (keyBlob == nullptr)
    {
        IMLOG_ERROR(L"%s: Error in malloc 0x%08X", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }
    memset(keyBlob, 0, keyBlobSize);
    memcpy(keyBlob->keyData, key.data(), key.size());
    keyBlob->hdr.aiKeyAlg = CALG_RC2; // nobody knows why RC2 - just works
    keyBlob->hdr.bType = PLAINTEXTKEYBLOB;
    keyBlob->hdr.bVersion = CUR_BLOB_VERSION;
    keyBlob->dwKeySize = keySize;

    // 2 - Load key and get key handle - hKey
    // CRYPT_IPSEC_HMAC_KEY - just allow loading keys longer than 128 bit
    if (!CryptImportKey(hProv, reinterpret_cast<const BYTE*>(keyBlob), keyBlobSize, 0, CRYPT_IPSEC_HMAC_KEY | CRYPT_EXPORTABLE, &m_hKey))
    {
        IMLOG_ERROR(L"%s: Error in CryptImportKey 0x%08X", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

    free(keyBlob);
    m_hProv = hProv;
    return;

ErrorExit:
    if (m_hKey)
        CryptDestroyKey(m_hKey);
    if (keyBlob)
        free(keyBlob);

    throw -1;
}


HmacSha256Key::~HmacSha256Key()
{
    if (m_hKey)
        CryptDestroyKey(m_hKey);
}

#define CHECK_SIGNATURE_SIZE        1

bool HmacSha256Key::CalcHmac(const void* data, size_t size, std::vector<uint8_t>& result)
{
    if (data == nullptr || m_hKey == 0)
        return false;

    HCRYPTHASH  m_hHmacHash = 0;
    bool retval = false;
    DWORD       dwDataLen = 0;
    HMAC_INFO   HmacInfo;

    memset(&HmacInfo, 0, sizeof(HmacInfo));
    HmacInfo.HashAlgid = CALG_SHA_256;

    // 3 - Getting HMAC handle with loaded key
    if (!CryptCreateHash(m_hProv, CALG_HMAC, m_hKey, 0, &m_hHmacHash))
    {
        IMLOG_ERROR(L"%s: Error in CryptCreateHash 0x%08X", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

    // 4 - Configure HMAC to use SHA_256 - set HmacInfo parameters to HMAC object by handle hHmacHash
    if (!CryptSetHashParam(m_hHmacHash, HP_HMAC_INFO, reinterpret_cast<const BYTE*>(&HmacInfo), 0))
    {
        IMLOG_ERROR(L"%s: Error in CryptSetHashParam 0x%08X", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

    // 5 - Calculate HMAC
    if (!CryptHashData(m_hHmacHash, static_cast<const BYTE*>(data), static_cast<DWORD>(size), 0))
    {
        IMLOG_ERROR(L"%s: Error in CryptHashData 0x%08x", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

    // 6 - Get length of result (should be 256/8=32 bytes)
    if (!CryptGetHashParam(m_hHmacHash, HP_HASHVAL, 0, &dwDataLen, 0))
    {
        IMLOG_ERROR(L"%s: Error in CryptGetHashParam 0x%08x", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

#if CHECK_SIGNATURE_SIZE
    if (dwDataLen != HMAC_SHA256_KEY_SIZE)
    {
        IMLOG_ERROR(L"%s: HMAC size should be 32 byte", __FUNCTIONW__);
        goto ErrorExit;
    }
#endif
    result.resize(dwDataLen);

    // 7 - Get value of HMAC
    if (!CryptGetHashParam(m_hHmacHash, HP_HASHVAL, result.data(), &dwDataLen, 0))
    {
        IMLOG_ERROR(L"%s: Error in CryptGetHashParam 0x%08x", __FUNCTIONW__, GetLastError());
        goto ErrorExit;
    }

    retval = true;

ErrorExit:
    if (m_hHmacHash)
        CryptDestroyHash(m_hHmacHash);

    return retval;
}

