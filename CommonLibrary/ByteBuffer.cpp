#include "ByteBuffer.h"
#include "stdafx.h"


using namespace IMFS;

ByteBuffer::ByteBuffer () :
        m_data(new container_type())
{
}

IMFS::ByteBuffer::ByteBuffer(const ArrayWrapper<byte> & arr)
    : m_data(new container_type(arr.size()))
{
    if (!arr.empty())
        memcpy(m_data->data(), static_cast<const byte*>(arr), arr.size());
}

ByteBuffer::ByteBuffer (size_t length) :
        m_data(new container_type(length, 0))
{
}

ByteBuffer::ByteBuffer (const container_type& values) :
        m_data(new container_type(values))
{
}

ByteBuffer::ByteBuffer (const ByteBuffer& bufferToCopy) :
        m_data(bufferToCopy.m_data)
{
}

ByteBuffer::ByteBuffer (const ByteBuffer&& bufferToMove) :
        m_data(bufferToMove.m_data)
{
}

ByteBuffer::ByteBuffer (const void* values, size_t length) :
        m_data(new container_type(length))
{
    if (values != nullptr)
        memcpy(m_data->data(), values, length);
}

ByteBuffer& ByteBuffer::operator= (const ByteBuffer& bufferToCopy)
{
    m_data = bufferToCopy.m_data;
    return *this;
}

ByteBuffer& ByteBuffer::operator= (const ByteBuffer&& bufferToMove)
{
    m_data = bufferToMove.m_data;
    return *this;
}

ByteBuffer *ByteBuffer::CloneBuffer () const
{
    return new ByteBuffer(*m_data);
}

size_t ByteBuffer::GetBytesAt (std::vector<byte>& result, size_t offset, size_t length)
{
    if (m_data->size() < (offset + length))
        return 0;

    result.resize(length);

    memcpy(result.data(), m_data->data() + offset, length);

    return length;
}

size_t ByteBuffer::SetBytesAt (size_t offset, const std::vector<byte>& bytes,
        size_t sourceOffset, size_t length)
{
    if (m_data->size() < (offset + length) || bytes.size() < (sourceOffset + length))
        return 0;

    memcpy(m_data->data() + offset, bytes.data() + sourceOffset, length);

    return length;
}

size_t ByteBuffer::GetStringAt (IMFS::string& result, size_t pos, size_t bytes,
        bool isUnicode, bool aligned)
{
    if (isUnicode)
        return GetUnicodeStringAt(result, pos, bytes, true, aligned);
    else
        return GetAsciiStringAt(result, pos, bytes);
}

size_t ByteBuffer::SetStringAt (size_t offset, const IMFS::string& s, bool isUnicode,
        bool aligned)
{

    int bytesCount = 0;

    if (!s.empty())
    {
        if (!isUnicode)
        {
            return SetAsciiStringAt(offset, s);
        }
        int num = 0;

        if (aligned && ((offset & 1) == 1))
        {
            offset++;
            num = 1;
        }

        for (int i = 0; i < s.Length(); i++)
        {
            (*m_data)[offset] = (byte) (s[i] & '\x00ff');
            offset++;
            (*m_data)[offset] = (byte) (s[i] >> 8);
            offset++;
        }
        bytesCount = ((s.Length() * 2) + num);
    }
    return bytesCount;
}

size_t ByteBuffer::GetStringSize (size_t pos, const IMFS::string& input,
        bool isUnicode, bool aligned)
{
    size_t stringSize = 0;
    stringSize = input.size();
    if (isUnicode)
        stringSize = stringSize * 2;
    if (isUnicode && aligned)
        stringSize += (pos % 2);
    return stringSize;
}

size_t ByteBuffer::GetZeroTerminatedStringSize (size_t pos, const IMFS::string& input,
        bool isUnicode, bool aligned)
{
    size_t stringSize = 0;
    stringSize = input.size() + 1;
    if (isUnicode)
        stringSize = stringSize * 2;
    if (isUnicode && aligned)
        stringSize += (pos % 2);

    return stringSize;
}

size_t ByteBuffer::SetZeroTerminatedStringAt (size_t pos, const IMFS::string& s,
        bool isUnicode, bool aligned)
{
    int bytesCount = 0;

    if (!isUnicode)
    {
        return SetZeroTerminatedAsciiStringAt(pos, s);
    }
    int num = 0;
    if (aligned && ((pos & 1) == 1))
    {
        pos++;
        num = 1;
    }
    for (int i = 0; i < s.Length(); i++)
    {
        (*m_data)[pos] = (byte) (s[i] & '\x00ff');
        pos++;
        (*m_data)[pos] = (byte) (s[i] >> 8);
        pos++;
    }
    (*m_data)[pos] = 0;
    (*m_data)[pos++] = 0;
    bytesCount = (((s.Length() * 2) + 2) + num);

    return bytesCount;
}

size_t ByteBuffer::SetZeroTerminatedAsciiStringAt (size_t offset,
        const IMFS::string& s)
{
    size_t bytesCount = 0;
    char* ascii = IMFS::string::GetAsASCII(850, s.size(), s);

    if (ascii != NULL)
    {
        size_t index = 0;
        size_t len = strlen(ascii);
        for (index = 0; index < len; index++)
        {
            (*m_data)[offset + index] = (byte) (ascii[index]);
            if (ascii[index] == '\0')
                break;
        }
        bytesCount = len + 1;
        delete[] ascii;
    }

    return bytesCount;
}

void ByteBuffer::GetString (size_t pos, size_t length, IMFS::string& result,
        bool zeroterminated)
{
    std::unique_ptr<char[]> str = std::make_unique<char[]>(length + 1);

    for (size_t i = 0; i < length; ++i)
    {
        str[i] = (char) (*m_data)[i + pos];
        if (zeroterminated && str[i] == '\0')
            break;
    }
    str[length] = '\0';
    IMFS::string::AssignAsUnicode(850, length, str.get(), result);
}

size_t ByteBuffer::GetZeroTerminatedStringAt (IMFS::string& result, size_t pos,
        size_t maximum, bool wildcardReplacement, bool isUnicode, bool aligned)
{
    if (isUnicode)
    {
        return GetUnicodeStringAt(result, pos, maximum, wildcardReplacement,
                aligned);
    }
    size_t num = pos + maximum;
    size_t index = pos;
    while (((*m_data)[index] != 0) && (index < num))
    {
        if ((wildcardReplacement && ((*m_data)[index] == '"'))
                && ((*m_data)[index + 1] == '*'))
        {
            (*m_data)[index] = (byte) '.';
        }
        index++;
    }
    if (index < num)
    {
        GetString(pos, index - pos, result, true);
        return ((index - pos) + 1);
    }
    result = L"";
    return 1;

}
static size_t GetZeroTerminatedStringSize (size_t pos, const IMFS::string& input,
        bool isUnicode, bool aligned)
{
    size_t stringSize = 0;
    if (!input.empty())
    {
        stringSize = input.size() + 1;
        if (isUnicode)
            stringSize = stringSize * 2;
        if (isUnicode && aligned)
            stringSize += (pos % 2);
    }
    return stringSize;
}

size_t ByteBuffer::GetUnicodeStringAt (IMFS::string& result, size_t pos, size_t bytes,
        bool wildcardReplacement, bool aligned)
{
    int num = 0;
    if (aligned && ((pos & 1) == 1))
    {
        pos++;
        num = 1;
    }
    size_t capacity = bytes >> 1;
    int num3 = 0;
    bool flag = false;
    bool flag2 = false;
    StringBuilder *builder = new StringBuilder();
    for (size_t i = 0; i < capacity; i++)
    {
        num3 = GetByteAt(pos + (i * 2)) | (GetByteAt((pos + (i * 2)) + 1) << 8);

        if (num3 == 0)
        {
            break;
        }

        if (num3 == '>')
        {
            num3 = 0x3f;
            //break;
        }
        if (num3 == '<')
        {
            num3 = 0x2A;
            //break;
        }
        if (num3 == '"')
        {
            num3 = 0x2e;
        }

        if (flag)
        {
            if ((num3 == 0x2a) || (num3 == 0x3f))
            {
                builder->Append('.');
            }
            else
            {
                builder->Append('"');
            }
            flag = false;
        }
        if (flag2)
        {
            if (num3 == 0x2e)
            {
                builder->Append('*');
            }
            else
            {
                builder->Append('<');
            }
            flag2 = false;
        }
        if (wildcardReplacement && (num3 == 0x22))
        {
            flag = true;
        }
        else if (wildcardReplacement && (num3 == 60))
        {
            flag2 = true;
        }
        else
        {
            builder->Append(num3);
        }
    }

    if (flag2)
    {
        builder->Append('*');
    }
    result = builder->ToString();
    if (wildcardReplacement)
    {
        if ((result.empty()))
        {
            result = L"\\";
        }
        if (!result.StartsWith(L"\\"))
        {
            result = L"\\";
        }

        if (result.EndsWith(L":$DATA"))
        {
            result = result.Substring(0, result.Length() - 6);
        }
    }

    size_t returnResult = 0;

    if (num3 == 0)
    {
        returnResult = (((builder->ToString().Length() * 2) + 2) + num);
        delete builder;
        return returnResult;
    }
    returnResult = ((builder->ToString().Length() * 2) + num);
    delete builder;
    return returnResult;

}

size_t ByteBuffer::GetAsciiStringAt (IMFS::string& result, size_t pos, size_t bytes)
{
    GetString(pos, bytes, result, false);
    return bytes;
}

size_t ByteBuffer::SetAsciiStringAt (size_t offset, const IMFS::string& s)
{
    size_t bytesCount = 0;
    char* ascii = IMFS::string::GetAsASCII(850, s.size(), s);

    if (ascii != NULL)
    {
        size_t index = 0;
        size_t len = strlen(ascii);
        for (index = 0; index < len; index++)
        {
            (*m_data)[offset + index] = (byte) (ascii[index]);
        }
        bytesCount = len;
        delete[] ascii;
    }

    return bytesCount;
}

size_t ByteBuffer::Align (size_t offset, size_t boundary)
{
    return ((offset + boundary - 1) & ~(boundary - 1));
}

