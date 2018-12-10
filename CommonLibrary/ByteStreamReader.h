#pragma once

namespace IMFS
{
    //
    // An attempt to safely treat a byte buffer as a stream of bytes for
    // easier reading & parsing.  All multi-byte reads are in little-endian
    // format.
    //
    class ByteStreamReader
    {
    public:
        ByteStreamReader(const std::vector<unsigned char>& source_);
        ~ByteStreamReader();

        // Returns the next four bytes from the stream
        int ReadInt32();

        // Returns the next four bytes from the stream
        unsigned int ReadUInt32();

        // Returns the next byte in the stream
        unsigned char ReadByte();

        // Moves the position <n> bytes forward or backward in the stream
        void SkipBytes(int size);

        // Returns the next two bytes from the stream
        unsigned short ReadUInt16();

    private:
        const std::vector<unsigned char>& source;
        size_t pos;

        ByteStreamReader& operator=(const ByteStreamReader& other);

    };
}
