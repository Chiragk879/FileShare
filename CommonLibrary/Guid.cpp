#include "stdafx.h"

using namespace IMFS;

bool
Guid :: operator==(const Guid& other) const
{
    UUID a = value;
    UUID b = other.value;
    RPC_STATUS status = 0;
    return (::UuidCompare(&a, &b, &status) == 0);
}

void
Guid::ToByteArray(std::vector<byte>& target) const
{
    target.clear();

    byte *p = (byte *)&value.Data1;
    for (int i = 0; i < sizeof(value.Data1); i++, p++)
        target.push_back(*p);

    p = (byte *)&value.Data2;
    for (int i = 0; i < sizeof(value.Data2); i++, p++)
        target.push_back(*p);

    p = (byte *)&value.Data3;
    for (int i = 0; i < sizeof(value.Data3); i++, p++)
        target.push_back(*p);

    p = (byte *)value.Data4;
    for (int i = 0; i < sizeof(value.Data4); i++, p++)
        target.push_back(*p);
}


Guid
Guid::NewGuid()
{
    Guid ng;

#pragma warning(suppress: 6031)
    ::UuidCreate(&ng.value);

    return ng;
}

Guid::Guid()
{
    memset(&value, 0, sizeof(value));
}
Guid::Guid(GUID& id)
{
    memcpy(&value, &id, sizeof(value));
}

Guid::Guid(std::vector<byte>& id)
{
    IMFS_ASSERT(id.size() == 16);

    unsigned char *pLong;
    pLong = (unsigned char*)&value.Data1;
    pLong[0] = id[0];
    pLong[1] = id[1];
    pLong[2] = id[2];
    pLong[3] = id[3];

    pLong = (unsigned char*)&value.Data2;
    pLong[0] = id[4];
    pLong[1] = id[5];

    pLong = (unsigned char*)&value.Data3;
    pLong[0] = id[6];
    pLong[1] = id[7];

    value.Data4[0] = id[8];
    value.Data4[1] = id[9];
    value.Data4[2] = id[10];
    value.Data4[3] = id[11];
    value.Data4[4] = id[12];
    value.Data4[5] = id[13];
    value.Data4[6] = id[14];
    value.Data4[7] = id[15];
}

Guid& Guid :: operator=(std::vector<byte>& id)
{
    IMFS_ASSERT(id.size() == 16);

    unsigned char *pLong;
    pLong = (unsigned char*)&value.Data1;
    pLong[0] = id[0];
    pLong[1] = id[1];
    pLong[2] = id[2];
    pLong[3] = id[3];

    pLong = (unsigned char*)&value.Data2;
    pLong[0] = id[4];
    pLong[1] = id[5];

    pLong = (unsigned char*)&value.Data3;
    pLong[0] = id[6];
    pLong[1] = id[7];

    value.Data4[0] = id[8];
    value.Data4[1] = id[9];
    value.Data4[2] = id[10];
    value.Data4[3] = id[11];
    value.Data4[4] = id[12];
    value.Data4[5] = id[13];
    value.Data4[6] = id[14];
    value.Data4[7] = id[15];
    return *this;
}

Guid :: ~Guid()
{
}

bool
Guid :: operator<(const Guid& other) const
{
    UUID a = value;
    UUID b = other.value;
    RPC_STATUS status = 0;
    return (::UuidCompare(&a, &b, &status) == -1);

}

string
Guid::ToString()
{
    wchar_t buff[256] = {0};
#pragma warning(suppress: 6031)
    ::StringFromGUID2(value, buff, _countof(buff) - 1);
    return buff;
}
