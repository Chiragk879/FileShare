#pragma once

#include <vector>
#include <cstdint>

namespace IMFS
{
    class CryptKey
    {
    public:
        CryptKey(const std::vector<uint8_t>& key = std::vector<uint8_t>()) : m_key(key) {};
        virtual ~CryptKey() = default;
        void SetKey(const std::vector<uint8_t> key) { m_key = key; }
        const std::vector<uint8_t> GetKey() const { return m_key; }
        size_t size() const { return m_key.size(); }
    private:
        std::vector<uint8_t> m_key;
    };
}

