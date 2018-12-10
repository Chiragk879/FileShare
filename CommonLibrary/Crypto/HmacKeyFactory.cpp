#include "stdafx.h"

#include "HmacKeyFactory.h"
#include "HmacSha256Key.h"
#include "HmacSha1Key.h"
#include "..\logmgr.h"

using namespace IMFS;

HmacKeyFactory* HmacKeyFactory::m_instance = nullptr;

HmacKeyFactory* HmacKeyFactory::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new HmacKeyFactory();
    }
    return m_instance;
}

void HmacKeyFactory::SetInstance(HmacKeyFactory* instance)
{
    m_instance = instance;
}

HmacKeyFactory::HmacKeyFactory() :
m_hProv(0)
{
    // 1 - Get Crypto Service Provider handle - hProv
    // SHA_256 supported by Enchances RSA and AES, but getting AES fails
    if (!CryptAcquireContext(&m_hProv, 0, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        IMLOG_ERROR(L"%s: CryptAcquireContext failed with code 0x%08X.", __FUNCTIONW__, GetLastError());
        m_hProv = 0;
    }
}

HmacKeyFactory::~HmacKeyFactory()
{
    if (m_hProv != 0)
    {
        CryptReleaseContext(m_hProv, 0);
        m_hProv = 0;
    }
}

std::shared_ptr<IHmacKey> HmacKeyFactory::CreateKey(HmacKeyType type, const std::vector<uint8_t>& keyData)
{
    if (m_hProv != 0)
    {
        IHmacKey* result = nullptr;
        try
        {
            switch (type)
            {
                case HmacKeyType::HMAC_SHA1:
                    result = new HmacSha1Key(m_hProv, keyData);
                    break;

                case HmacKeyType::HMAC_SHA256:
                    result = new HmacSha256Key(m_hProv, keyData);
                    break;
            }
        }
        catch (...)
        {
            IMLOG_ERROR(L"%s: HmacSha256Key instantiation failed.", __FUNCTIONW__);
        }
        return std::shared_ptr<IHmacKey>(result);
    }
    IMLOG_ERROR(L"%s: CSP not initialized.", __FUNCTIONW__);
    return nullptr;
}

