#include "stdafx.h"

using namespace IMFS;

DataStreamInfo :: ~DataStreamInfo()
{
}


std::map<std::wstring, FakeStream>& SupportedFileStreams::GetStreams()
{
    // Disable Zone.Identifier because it gaves nothing and MacOS all the time tries to delete it.
    //static const std::string ZoneTransfer("[ZoneTransfer]\r\nZoneId=1\r\n");
    //size_t ZoneTransferLen = ZoneTransfer.size();
    //static FakeStream ZoneIdentifier(L"Zone.Identifier", 0, ByteBuffer(ZoneTransfer.data(), ZoneTransfer.size()));
    static std::map<std::wstring, FakeStream> streams; //({ { L"Zone.Identifier", ZoneIdentifier} });

    return streams;
}