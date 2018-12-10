#pragma once

#include <vector>
#include <cstdint>

namespace IMFS
{

    enum class HmacKeyType
    {
        HMAC_SHA1 = 1,
        HMAC_SHA256 = 2
    };

    class IHmacKey
    {
    public:
        /// Produce 32 byte length HMAC SHA256 with this key for given data
        /// return true on success
        virtual bool CalcHmac(const void* data, size_t size, std::vector<uint8_t>& result) = 0;

        virtual ~IHmacKey() = default;
    };

}

