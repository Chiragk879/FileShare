#pragma once

#include "HmacKeyFactory.h"
#include "IHmacKey.h"

namespace IMFS
{

    class HmacSha256Key : public IHmacKey
    {
    public:
        virtual bool CalcHmac(const void* data, size_t size, std::vector<uint8_t>& result);

        virtual ~HmacSha256Key();

    private:
        HmacSha256Key(HCRYPTPROV hProv, const std::vector<uint8_t>& key) throw(...);

        friend std::shared_ptr<IHmacKey> HmacKeyFactory::CreateKey(HmacKeyType type, const std::vector<uint8_t>& key);

        static const size_t HMAC_SHA256_KEY_SIZE;

        /// HmacSha256Key owns key descriptor and is responsible for it's destruction
        HCRYPTKEY   m_hKey;

        /// HmacSha256Key does not own security provider descriptor, only use it
        HCRYPTPROV m_hProv;
    };

}
