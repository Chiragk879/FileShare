#pragma once

#include <vector>
#include <memory>

namespace IMFS
{

class ByteBuffer: public IM::ObjectSignature
{
public:
    typedef std::vector<uint8_t> container_type;

    ByteBuffer ();

    /// Do not duplicate data.
    ByteBuffer (const ByteBuffer& bufferToCopy);

    /// Do not duplicate data.
    ByteBuffer (const ByteBuffer&& bufferToMove);

    ByteBuffer(const ArrayWrapper<byte>& arr);

    ByteBuffer (size_t length);

    /// Duplicate data.
    ByteBuffer (const void* data, size_t length);

    /// Duplicate data.
    ByteBuffer (const container_type& data);

    virtual ~ByteBuffer () = default;

    /// Do not duplicate data.
    ByteBuffer& operator= (const ByteBuffer& bufferToCopy);

    /// Do not duplicate data.
    ByteBuffer& operator= (const ByteBuffer&& bufferToMove);

    /// Duplicate data.
    ByteBuffer* CloneBuffer() const;

    inline bool operator == (const ByteBuffer& another) { return *(m_data) == *(another.m_data); }
    inline bool operator != (const ByteBuffer& another) { return *(m_data) != *(another.m_data); }

    inline container_type& GetBytes () { return *m_data; }
    inline void* GetDataPtr(size_t offset = 0) { return m_data->data() + offset; }
    inline size_t GetLength () const { return m_data->size(); }
    inline void Extend(size_t extendSize) { m_data->resize(m_data->size() + extendSize, 0); }

    /// Copy data from buffer to vector and return length or return zero if failed.
    size_t GetBytesAt (std::vector<byte>& result, size_t offset, size_t length);

    /// Copy data from vector to buffer and return length or return zero if failed.
    size_t SetBytesAt (size_t offset, const std::vector<byte>& bytes, size_t sourceOffset, size_t length);

    /// We are on x86 and all getters and setters assume the same as host byte order (x86, x86_64 - little endian) [2.2 Message Syntax].
    template <typename T> T Get (size_t offset)
    {
        if (m_data->size() >= (offset + sizeof(T)))
        {
            return *(reinterpret_cast<T*>(m_data->data() + offset));
        }
        return 0;
    }

    /// We are on x86 and all getters and setters assume the same as host byte order (x86, x86_64 - little endian) [2.2 Message Syntax].
    template <typename T> int Set (size_t offset, T value)
    {
        if (m_data->size() >= (offset + sizeof(T)))
        {
            *(reinterpret_cast<T*>(m_data->data() + offset)) = value;
            return sizeof(T);
        }
        else
        {
            return 0;
        }
    }

    // getters/setters - Smb1 legacy

    byte GetByteAt (size_t offset) { return (*m_data)[offset]; }
    int SetByteAt (size_t offset, byte value) { return Set<uint8_t>(offset, value); }

    ushort GetUShortAt(size_t offset) { return Get<uint16_t>(offset); }
    int SetUShortAt (size_t offset, ushort value) { return Set<uint16_t>(offset, value); }

    short GetShortAt(size_t offset) { return Get<int16_t>(offset); }
    int SetShortAt (size_t offset, short value) { return Set<int16_t>(offset, value); }

    uint GetUIntAt(size_t offset) { return Get<uint32_t>(offset); }
    int SetUIntAt (size_t offset, uint value) { return Set<uint32_t>(offset, value); }

    int GetIntAt(size_t offset) { return Get<int32_t>(offset); }
    int SetIntAt (size_t offset, int value) { return Set<int32_t>(offset, value); }

    unsigned __int64 Get__uint64At(size_t offset) { return Get<unsigned __int64>(offset); }
    int Set__uint64At (size_t offset, unsigned __int64 value) { return Set<unsigned __int64>(offset, value); }

    __int64 Get__int64At(size_t offset) { return Get<__int64>(offset); }
    int Set__int64At (size_t offset, __int64 value) { return Set<__int64>(offset, value); }

    // IMFS STRINGS - Smb1 legacy

    size_t GetStringAt (IMFS::string& result, size_t pos, size_t bytes,
            bool isUnicode, bool aligned);

    size_t SetStringAt (size_t offset, const IMFS::string& s, bool isUnicode,
            bool aligned);

    void GetString (size_t pos, size_t length, IMFS::string& result, bool zeroterminated);

    size_t GetZeroTerminatedStringAt (IMFS::string& result, size_t pos,
            size_t maximum, bool wildcardReplacement, bool isUnicode,
            bool aligned);

    size_t SetZeroTerminatedStringAt (size_t pos, const IMFS::string& s,
            bool isUnicode, bool aligned);

    // wstring

    inline std::wstring GetWStringAt(size_t pos, size_t length_bytes)
    {
        if (m_data->size() >= (pos + length_bytes))
        {
            return std::wstring(reinterpret_cast<wchar_t*>(m_data->data() + pos), length_bytes / sizeof(wchar_t));
        }
        else
        {
            return std::wstring();
        }
    };
    inline bool SetWStringAt(size_t pos, const std::wstring& ws)
    {
        if (m_data->size() >= (pos + ws.size()*sizeof(wchar_t)))
        {
            memcpy(m_data->data() + pos, ws.data(), ws.size()*sizeof(wchar_t));
            return true;
        }
        else
        {
            return false;
        }
    };

    inline bool InBounds(size_t offset, size_t count = 0) const
    {
        return (offset + count) <= m_data->size();
    }

public:

    // Legacy

    static size_t Align (size_t offset, size_t boundary);

    static size_t GetStringSize (size_t pos, const IMFS::string& input,
            bool isUnicode, bool aligned);

    static size_t GetZeroTerminatedStringSize (size_t pos, const IMFS::string& input,
            bool isUnicode, bool aligned);

private:

    size_t GetUnicodeStringAt (IMFS::string& result, size_t pos, size_t bytes,
            bool wildcardReplacement, bool aligned);

    size_t GetAsciiStringAt (IMFS::string& result, size_t pos, size_t bytes);

    size_t SetAsciiStringAt (size_t offset, const IMFS::string& s);

    size_t SetZeroTerminatedAsciiStringAt(size_t offset, const IMFS::string& s);

    std::shared_ptr<container_type> m_data;
};

} // namespace IMFS
