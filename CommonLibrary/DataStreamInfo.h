#pragma once

namespace IMFS
{
    /// <summary>
    /// Structure containing information about a stream associated with a file
    /// </summary>
    class DataStreamInfo
    {
        public:
            /// <summary>
            /// Stream name
            /// </summary>
            string Name;

            /// <summary>
            /// Stream type
            /// </summary>
            uint32_t Type;

            /// <summary>
            /// Stream size
            /// </summary>
            uint64_t Size;

            /// <summary>
            /// Stream allocation size
            /// </summary>
            uint64_t AllocationSize;

            /// <summary>
            /// Stream attributes
            /// </summary>
            uint64_t Attributes;

        public:

            /// <summary>
            /// DataStreamInfo
            /// </summary>
            /// <param name="name"></param>
            /// <param name="type"></param>
            /// <param name="size"></param>
            /// <param name="attributes"></param>
            DataStreamInfo(const string& name, uint32_t type, uint64_t size, uint64_t allocationSize, uint64_t attributes)
                : Name(name)
            {
                this->Type = type;
                this->Size = size;
                this->AllocationSize = allocationSize;
                this->Attributes = attributes;
            }

            DataStreamInfo(const DataStreamInfo& src)
            {
                this->Name = src.Name;
                this->Type = src.Type;
                this->Size = src.Size;
                this->AllocationSize = src.AllocationSize;
                this->Attributes = src.Attributes;
            }

            virtual ~DataStreamInfo();
    };

    class FakeStream: public DataStreamInfo
    {
    public:
        FakeStream(const string& name, uint64_t attributes, ByteBuffer fakeData)
            : DataStreamInfo(name, BACKUP_DATA, static_cast<uint64_t>(fakeData.GetLength()), static_cast<uint64_t>(fakeData.GetLength()), attributes)
        {
            Name = L":" + name + L":$DATA";
            Data = fakeData;
        }

        FakeStream(const FakeStream& src)
            : DataStreamInfo(src)
        {
            Data = src.Data;
        }

    public:
        ByteBuffer Data;
    };

    class SupportedFileStreams
    {
    public:
        static std::map<std::wstring, FakeStream>& GetStreams();
    };
}
