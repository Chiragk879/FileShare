#pragma once

#include <memory>
#include <windows.h>
#include <wincrypt.h>
#include "IHmacKey.h"

namespace IMFS
{

    class HmacKeyFactory
    {
    public:
        static HmacKeyFactory* GetInstance();

        /// Instantiates HmacSha256Key with specific key data
        /// key data length can be less, equal or greater than 32 byte - it will be handled internally according to HMAC algorythm
        virtual std::shared_ptr<IHmacKey> CreateKey(HmacKeyType type, const std::vector<uint8_t>& keyData);

        HmacKeyFactory(HmacKeyFactory const&) = delete;
        void operator=(HmacKeyFactory const&) = delete;
        HmacKeyFactory(HmacKeyFactory const&&) = delete;
        void operator=(HmacKeyFactory const&&) = delete;

        virtual ~HmacKeyFactory();

    protected:
        HmacKeyFactory();

        static void SetInstance(HmacKeyFactory* instance);

    private:
        static HmacKeyFactory* m_instance;

        HCRYPTPROV  m_hProv;
    };

}

