#pragma once

#include "HmacKeyFactory.h"
#include "IHmacKey.h"

//NOTE: This code is not used because SAML auth token aquisition implemented via .NET

namespace IMFS
{

    class HmacSha1Key : public IHmacKey
    {
    public:
        virtual bool CalcHmac(const void* data, size_t size, std::vector<uint8_t>& result);

        virtual ~HmacSha1Key();

    private:
        HmacSha1Key(HCRYPTPROV hProv, const std::vector<uint8_t>& key) throw(...);

        friend std::shared_ptr<IHmacKey> HmacKeyFactory::CreateKey(HmacKeyType type, const std::vector<uint8_t>& key);

        static const size_t HMAC_SHA1_KEY_SIZE;

        /// HmacSha1Key owns key descriptor and is responsible for it's destruction
        HCRYPTKEY   m_hKey;

        /// HmacSha1Key does not own security provider descriptor, only use it
        HCRYPTPROV m_hProv;
    };

}
