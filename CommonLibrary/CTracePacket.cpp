#include "stdafx.h"


#if defined(_MSC_VER) || defined(__BORLANDC__)
#define EPOCHFILETIME (116444736000000000i64)
#else
#define EPOCHFILETIME (116444736000000000LL)
#endif

#define IPHEADERSIZE 20
#define TCPHEADERSIZE 20
#define NETBIOSFRAME 4


using namespace IMFS;


CTracePacket::CTracePacket()
{
}

CTracePacket::~CTracePacket()
{
	if(m_PacketQueue.size() > 0)
	{
		for(std::vector<CapturePacket*>::iterator itr = m_PacketQueue.begin(); itr != m_PacketQueue.end(); ++itr)
		{
			delete *itr;
		}
		m_PacketQueue.clear();
	}
}


void CTracePacket::GetCurrentTimeStamp(unsigned int &ts_sec, unsigned int &ts_usec)
{
	SYSTEMTIME systemTime;
	::GetSystemTime( &systemTime );

	FILETIME fileTime;
	::SystemTimeToFileTime( &systemTime, &fileTime );
	LARGE_INTEGER   li;
#pragma warning(suppress: 6102)
	li.LowPart  = fileTime.dwLowDateTime;
	li.HighPart = fileTime.dwHighDateTime;

	__int64         t;

	t  = li.QuadPart;       /* In 100-nanosecond intervals */
	t -= EPOCHFILETIME;     /* Offset to the Epoch time */
	t /= 10;                /* In microseconds */
	ts_sec  = (long)(t / 1000000);
	ts_usec = (long)(t % 1000000);


}

void CTracePacket::capture(const std::vector<byte>& packet)
{
	
	unsigned int ts_sec;
	unsigned int ts_usec;
	GetCurrentTimeStamp(ts_sec, ts_usec);
	CaptureTimestamp CT;
	CT.ts_sec = ts_sec;
	CT.ts_usec = ts_usec;
	
	byte PaddingBytes[] = {0x00, 0x15 , 0xc5 , 0x14 , 0x41 , 0xc5 , 0x00 , 0x1f , 0x6c , 0x03 , 0x32 , 0x80 , 0x08 , 0x00 , 0x45 , 0x00
				, 0x00 , 0xb1 , 0x00 , 0x66 , 0x40 , 0x00 , 0x7f , 0x06 , 0xda , 0x2b , 0x0a , 0x78 , 0x02 , 0x5c , 0x0a , 0x78
				, 0x09 , 0x6a , 0x06 , 0x01 , 0x00 , 0x8b , 0xf7 , 0xd4 , 0x47 , 0xf3 , 0x99 , 0xd9 , 0xf4 , 0xf0 , 0x50 , 0x18
				, 0xff , 0xfb , 0xf1 , 0x3c , 0x00 , 0x00 , 0x00 , 0x00 , 0x00 , 0x85};

	
	size_t size = packet.size()+ IPHEADERSIZE + TCPHEADERSIZE + NETBIOSFRAME;

	byte* data = (byte*)&size;
	PaddingBytes [16] = data[1];
	PaddingBytes [17] =  data[0];

	byte *packetArray = new byte[packet.size()+ sizeof(PaddingBytes)];
	int i = sizeof(PaddingBytes);

	memcpy(packetArray,PaddingBytes, sizeof(PaddingBytes));
	
	std::vector<byte> tempPacket = packet;
	for(std::vector<byte>::iterator it = tempPacket.begin(); it != tempPacket.end(); ++it)
	{
		packetArray[i] = *it;
		++i;
	}

	CapturePacket *ck = new CapturePacket(CT, packetArray, (unsigned int)(packet.size()+ sizeof(PaddingBytes)));
	delete []packetArray;
	m_PacketQueue.push_back(ck);

}

bool
CTracePacket :: DoesFileExist(const string& strFilePath)
{
	WIN32_FIND_DATA finfo;
	ZeroMemory(&finfo,sizeof(WIN32_FIND_DATA));
	HANDLE hInfo = ::FindFirstFile(strFilePath.c_str(),&finfo);
	if(hInfo != INVALID_HANDLE_VALUE)
	{
		::FindClose(hInfo);
		return true;
	}
	return false;
}

void CTracePacket::dump(const string& filename)
{
	if(!filename.empty())
	{
		pcap_hdr_t GHeader;
		pcaprec_hdr_t packetHeader;
		DWORD written = 0;
		bool isHeaderisWritten = true;

		if(!DoesFileExist(filename))
		{
			HANDLE hFile = ::CreateFile(filename.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				GHeader.magic_number = 0xa1b2c3d4;
				GHeader.version_major = 2;
				GHeader.version_minor = 4;
				GHeader.thiszone = 0;
				GHeader.sigfigs = 0;
				GHeader.snaplen =0;
				GHeader.network = 1; /* ethernet */

				if(!::WriteFile(hFile,&GHeader,sizeof(GHeader),&written,NULL) )
				{
					LogMgr::LogError(L"CPacketCaptureDump::dump faliled. CreateFile failed!");
					isHeaderisWritten = false;
				}
				::CloseHandle(hFile);
			}
		}
		
		if(isHeaderisWritten)
		{
			written = 0;
			HANDLE hFile = ::CreateFile(filename.c_str(),GENERIC_WRITE,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
			
			if(hFile != INVALID_HANDLE_VALUE)
			{
				if(::SetFilePointer(hFile,NULL,NULL,FILE_END) != INVALID_SET_FILE_POINTER)
				{
					for(std::vector<CapturePacket*>::iterator itr = m_PacketQueue.begin(); itr != m_PacketQueue.end(); ++itr)
					{
						CapturePacket *cp = *itr;
						CaptureTimestamp timeStamp = cp->GettimeStamp();

						packetHeader.incl_len = cp->GetPacketSize();
						packetHeader.orig_len = cp->GetPacketSize();
						packetHeader.ts_sec = timeStamp.ts_sec;
						packetHeader.ts_usec = timeStamp.ts_usec;

						if(::WriteFile(hFile,&packetHeader,sizeof(packetHeader),&written,NULL) )
						{
							written =0;
							if(!::WriteFile(hFile,cp->Getpacket(),cp->GetPacketSize(),&written,NULL) )
							{
								LogMgr::LogError(L"CPacketCaptureDump::dump faliled. writing packet failed!");	
							}
						}
						else
						{
								LogMgr::LogError(L"CPacketCaptureDump::dump faliled. writing packet header failed!");
						}
						delete cp;

					}
					m_PacketQueue.clear();

				}
				::CloseHandle(hFile);
			}
			else
			{
				LogMgr::LogError(L"CPacketCaptureDump::dump faliled. writing packet failed!");
			}
		}
	}
	else
	{
		LogMgr::LogError(L"CPacketCaptureDump::dump faliled. dump file name is empty!");
	}
	
}