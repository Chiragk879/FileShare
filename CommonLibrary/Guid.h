#pragma once

namespace IMFS
{
    class Guid
    {
    public:
        Guid();
        Guid(GUID& guid);
        Guid(std::vector<byte>& id);
        virtual ~Guid();

    public:
        GUID value;

    public:
        static Guid NewGuid();
        Guid& operator=(GUID& id);
        Guid& operator=(std::vector<byte>& id);
        void ToByteArray(std::vector<byte>& target) const;
        string ToString();
        inline bool Equals(const Guid& other) const {
            return (*this == other);
        }
        virtual bool operator==(const Guid& other) const;
        virtual bool operator<(const Guid& other) const;
    };
}