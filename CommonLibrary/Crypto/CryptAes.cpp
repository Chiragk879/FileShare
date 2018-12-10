#include "stdafx.h"
#include "CryptAES.h"

using namespace IMFS;

CryptAES::~CryptAES()
{
    if (m_alg_handle)
    {
        BCryptCloseAlgorithmProvider(m_alg_handle, 0);
    }
}

NTSTATUS CryptAES::CreateAlgorytm(LPCWSTR pszAlgId, AESModeOperation mode, ULONG flag)
{
    m_mode = mode;
    NTSTATUS status = STATUS_SUCCESS;
    m_alg_handle = NULL;

    status = BCryptOpenAlgorithmProvider(&m_alg_handle, pszAlgId, MS_PRIMITIVE_PROVIDER, flag);
    if (status != STATUS_SUCCESS)
        return status;

    if (m_alg_handle == NULL)
        return STATUS_INVALID_HANDLE;

    if (mode == AESMO_CCM)
    {
        // Enable CCM
        status = BCryptSetProperty( m_alg_handle, 
                                    BCRYPT_CHAINING_MODE, 
                                    (PUCHAR)BCRYPT_CHAIN_MODE_CCM, 
                                    sizeof(BCRYPT_CHAIN_MODE_CCM), 
                                    0);
    }
    else if (mode == AESMO_GCM)
    {
        // Enable GCM
        status = BCryptSetProperty(m_alg_handle,
                                   BCRYPT_CHAINING_MODE,
                                   (PUCHAR)BCRYPT_CHAIN_MODE_GCM,
                                   sizeof(BCRYPT_CHAIN_MODE_GCM),
                                   0);
    }
    return status;
}

NTSTATUS CryptAES::ImportKey(const uint8_t* key, size_t sizeKey)
{
    NTSTATUS status = STATUS_SUCCESS;
    if (m_alg_handle == NULL)
    {
        return STATUS_INVALID_HANDLE;
    }
    // Initialize a BCRYPT key blob with the key
    size_t kbhLen = sizeof(BCRYPT_KEY_DATA_BLOB_HEADER) + sizeKey;

    std::vector<BYTE> keyDataBlobHeader(kbhLen);

    BCRYPT_KEY_DATA_BLOB_HEADER* kbh = (BCRYPT_KEY_DATA_BLOB_HEADER*)keyDataBlobHeader.data();
    kbh->dwMagic = BCRYPT_KEY_DATA_BLOB_MAGIC;
    kbh->dwVersion = BCRYPT_KEY_DATA_BLOB_VERSION1;
    kbh->cbKeyData = (ULONG)sizeKey;
    memcpy(kbh + 1, key, sizeKey);

    // Get length of key object and allocate the object
    DWORD got;
    ULONG keyObjLen;
    status = CryptGetProperty(BCRYPT_OBJECT_LENGTH, (PBYTE)&keyObjLen, sizeof(ULONG), &got);
    if (status == STATUS_SUCCESS)
    {
        m_pkeyState = std::shared_ptr<AESKeyState>(new AESKeyState(keyObjLen));
        status = BCryptImportKey(m_alg_handle,
                                NULL,
                                BCRYPT_KEY_DATA_BLOB,
                                &m_pkeyState->handle,
                                m_pkeyState->keyObj,
                                keyObjLen,
                                (PUCHAR)kbh,
                                (ULONG)kbhLen,
                                0);
    }

    return status;
}

NTSTATUS CryptAES::Decrypt(const uint8_t* src, size_t srcSize, uint8_t* target, size_t& len, const uint8_t* nonce, size_t nonceSize, 
    const uint8_t* addData, size_t addDataSize, const uint8_t* tag, size_t tagSize)
{
    // Check we are initialized
    if (m_alg_handle == NULL || m_pkeyState == nullptr || m_pkeyState->handle == NULL)
    {
        return STATUS_INVALID_HANDLE;
    }

    // Check we are initialized for CCM
    size_t nLen = nonceSize;
    if (nLen < 11 || nLen > 14)
    {
        return STATUS_INVALID_PARAMETER;
    }
    uint8_t authLen = (uint8_t)tagSize;
    if ((authLen < 4) || (authLen > 16))
    {
        return STATUS_INVALID_PARAMETER;
    }

    // Set CCM cipher mode info
    BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO cmi;
    BCRYPT_INIT_AUTH_MODE_INFO(cmi);

    // nonce to a minimum size of 11 bytes.
    cmi.pbNonce = (PUCHAR)nonce;
    cmi.cbNonce = (ULONG)nLen;

    cmi.pbAuthData = (PUCHAR)addData;
    cmi.cbAuthData = (ULONG)addDataSize;
    cmi.pbTag = (PUCHAR)tag;
    cmi.cbTag = (ULONG)tagSize;
    cmi.pbMacContext = NULL;
    cmi.cbMacContext = 0;
    cmi.cbAAD = 0;
    cmi.cbData = 0;
    cmi.dwFlags = 0;

    ULONG clen;
    return BCryptDecrypt(m_pkeyState->handle, (PUCHAR)(src), (ULONG)(len), &cmi, NULL, 0, (PUCHAR)(target), (ULONG)len, &clen, 0);
}

NTSTATUS CryptAES::Encrypt(const uint8_t* src, size_t srcSize, uint8_t* target, size_t& len, const uint8_t* nonce, size_t nonceSize,
    const uint8_t* addData, size_t addDataSize, uint8_t* signature, size_t signatureSize)
{
    NTSTATUS status = STATUS_SUCCESS;

    if (m_alg_handle == NULL || m_pkeyState == nullptr || m_pkeyState->handle == NULL)
    {
        return STATUS_INVALID_HANDLE;
    }
    
    // Check we are initialized for CCM
    size_t nLen = nonceSize;
    if (nLen < 11 || nLen > 14)
    {
        return STATUS_INVALID_PARAMETER;
    }
    uint8_t authLen = (uint8_t)signatureSize;
    if ((authLen < 4) || (authLen > 16))
    {
        return STATUS_INVALID_PARAMETER;
    }
    // Set CCM cipher mode info
    BCRYPT_AUTHENTICATED_CIPHER_MODE_INFO cmi;
    BCRYPT_INIT_AUTH_MODE_INFO(cmi);

    //nonce to a minimum size of 11 bytes.
    cmi.pbNonce = (PUCHAR)nonce;
    cmi.cbNonce = (ULONG)nLen;

    cmi.pbAuthData = (PUCHAR)addData;
    cmi.cbAuthData = (ULONG)addDataSize;
    cmi.pbTag = (PUCHAR)signature;
    cmi.cbTag = (ULONG)signatureSize;
    cmi.pbMacContext = NULL;
    cmi.cbMacContext = 0;
    cmi.cbAAD = 0;
    cmi.cbData = 0;
    cmi.dwFlags = 0;

    ULONG clen;
    return BCryptEncrypt(m_pkeyState->handle, (PUCHAR)(src), (ULONG)(len), &cmi, NULL, 0, (PUCHAR)(target), (ULONG)len, &clen, 0);
}

NTSTATUS CryptAES::CryptGetProperty(LPCWSTR pszProperty, PUCHAR pbOutput, ULONG cbOutput, ULONG* pcbResult)
{
    if (m_alg_handle == NULL)
        return STATUS_INVALID_HANDLE;

    return BCryptGetProperty( m_alg_handle, pszProperty, pbOutput, cbOutput, pcbResult, 0);
}

NTSTATUS CryptAES::GetSignature(const uint8_t* src, size_t srcSize, uint8_t* signature)
{
    NTSTATUS status = STATUS_SUCCESS;

    // Check we are initialized
    if (m_alg_handle == NULL || m_pkeyState == nullptr || m_pkeyState->handle == NULL)
    {
        return STATUS_INVALID_HANDLE;
    }

    static const uint8_t rgbIV[] =
    {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    DWORD cbData = 0;
    DWORD cbBlockLen = 0;

    // Calculate the block length for the IV.
    status = CryptGetProperty(BCRYPT_BLOCK_LENGTH, (PBYTE)&cbBlockLen, sizeof(DWORD), &cbData);
    if (status != STATUS_SUCCESS)
    {
        return status;
    }

    // Determine whether the cbBlockLen is not longer than the IV length.
    if (cbBlockLen > sizeof(rgbIV))
    {
        return STATUS_INVALID_PARAMETER;
    }

    PBYTE pbIV = NULL;

    // Allocate a buffer for the IV. The buffer is consumed during the encrypt/decrypt process.
    pbIV = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbBlockLen);
    if (NULL == pbIV)
    {
        status = STATUS_MEMORY_NOT_ALLOCATED;
        goto CleanData;
    }
    memcpy(pbIV, rgbIV, cbBlockLen);

    DWORD cbCipherText = 0;
    PBYTE pbCipherText = NULL;

    status = BCryptEncrypt(m_pkeyState->handle, (PUCHAR)(src), (ULONG)(srcSize), NULL, pbIV, cbBlockLen, NULL, 0, &cbCipherText, BCRYPT_BLOCK_PADDING);
    if (status != STATUS_SUCCESS)
    {
        goto CleanData;
    }
    pbCipherText = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbCipherText);
    if (NULL == pbCipherText)
    {
        status = STATUS_MEMORY_NOT_ALLOCATED;
        goto CleanData;
    }

    // Use the key to encrypt the plaintext buffer.
    status = BCryptEncrypt(m_pkeyState->handle, (PUCHAR)(src), (ULONG)(srcSize), NULL, pbIV, cbBlockLen, pbCipherText, cbCipherText, &cbData, BCRYPT_BLOCK_PADDING);
    if (status == STATUS_SUCCESS)
    {
        memcpy(signature, pbCipherText, cbBlockLen);
    }

CleanData:
#pragma warning(suppress: 6001)
    if (pbCipherText)
    {
        HeapFree(GetProcessHeap(), 0, pbCipherText);
    }
    if (pbIV)
    {
        HeapFree(GetProcessHeap(), 0, pbIV);
    }

    return status;
}

NTSTATUS CryptAES::GetSignature(const uint8_t* key, size_t keySize, const uint8_t* src, size_t srcSize, std::vector<uint8_t>& signature)
{
    NTSTATUS status = STATUS_SUCCESS;

    if (m_alg_handle == NULL)
    {
        return STATUS_INVALID_HANDLE;
    }

    DWORD cbData = 0;
    DWORD cbHashObject = 0;
    // calculate the size of the buffer to hold the hash object

    status = CryptGetProperty(BCRYPT_OBJECT_LENGTH, (PBYTE)&cbHashObject, sizeof(DWORD), &cbData);
    if (status != STATUS_SUCCESS)
        return status;

    PBYTE pbHashObject = NULL;
    PBYTE pbHash = NULL;
    // allocate the hash object on the heap
    pbHashObject = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHashObject);
    if (NULL == pbHashObject)
    {
        status = STATUS_MEMORY_NOT_ALLOCATED;
        goto CleanData;
    }

    DWORD cbHash = 0;
    // calculate the length of the hash
    status = CryptGetProperty(BCRYPT_HASH_LENGTH, (PBYTE)&cbHash, sizeof(DWORD), &cbData);
    if (status != STATUS_SUCCESS)
    {
        goto CleanData;
    }

    // allocate the hash buffer on the heap
    pbHash = (PBYTE)HeapAlloc(GetProcessHeap(), 0, cbHash);
    if (NULL == pbHash)
    {
        status = STATUS_MEMORY_NOT_ALLOCATED;
        goto CleanData;
    }

    BCRYPT_HASH_HANDLE hHash = NULL;
    // create a hash
    status = BCryptCreateHash(m_alg_handle, &hHash, pbHashObject, cbHashObject, (PUCHAR)key, (ULONG)keySize, 0);
    if (status != STATUS_SUCCESS)
    {
        goto CleanData;
    }

    // hash message data
    status = BCryptHashData(hHash, (PBYTE)src, (ULONG)srcSize, 0);
    if (status != STATUS_SUCCESS)
    {
        goto CleanData;
    }

    // close the hash
    status = BCryptFinishHash(hHash, pbHash, cbHash, 0);
    if (status == STATUS_SUCCESS)
    {
        signature.resize(cbHash);
        memcpy(signature.data(), pbHash, cbHash);
    }

CleanData:

    if (pbHashObject)
        HeapFree(GetProcessHeap(), 0, pbHashObject);
    if (pbHash)
        HeapFree(GetProcessHeap(), 0, pbHash);
#pragma warning(suppress: 6102)
    if (hHash)
        BCryptDestroyHash(hHash);

    return status;
}
