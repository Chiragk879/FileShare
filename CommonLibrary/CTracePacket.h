#pragma once

namespace IMFS
{
	
#define guint32 unsigned int
#define guint16 unsigned short
#define gint32 int

	typedef struct pcap_hdr_s {
		guint32 magic_number;   /* magic number */
		guint16 version_major;  /* major version number */
		guint16 version_minor;  /* minor version number */
		gint32  thiszone;       /* GMT to local correction */
		guint32 sigfigs;        /* accuracy of timestamps */
		guint32 snaplen;        /* max length of captured packets, in octets */
		guint32 network;        /* data link type */
	} pcap_hdr_t;

	typedef struct pcaprec_hdr_s {
		guint32 ts_sec;         /* timestamp seconds */
		guint32 ts_usec;        /* timestamp microseconds */
		guint32 incl_len;       /* number of octets of packet saved in file */
		guint32 orig_len;       /* actual length of packet */
	} pcaprec_hdr_t;


	typedef struct _CaptureTimestamp
	{
		unsigned int ts_sec;
		unsigned int ts_usec;

	}CaptureTimestamp;

	class CapturePacket
	{
	public:
		CapturePacket(CaptureTimestamp CT, byte* inpacket, unsigned int packetsize)
		{
			timeStamp.ts_sec =  CT.ts_sec;
			timeStamp.ts_usec =  CT.ts_usec;
			packetSize = packetsize;
			packet = new byte[packetSize];

			memcpy(packet, inpacket, packetsize);
		}

		~CapturePacket()
		{
			if(packet != NULL)
			{
				delete []packet;
				packet = NULL;
			}
		}

		unsigned int GetPacketSize()
		{
			return packetSize;
		}

		CaptureTimestamp GettimeStamp()
		{
			return timeStamp;
		}
		byte* Getpacket()
		{
			return packet;
		}

	private:
		CaptureTimestamp timeStamp;
		byte* packet;
		unsigned int packetSize;

	};

	class CTracePacket
	{
	
	public:
		CTracePacket();
		~CTracePacket();

		void capture(const std::vector<byte>& packet);
		void dump(const string& filename);

	protected:
		void GetCurrentTimeStamp(unsigned int &ts_sec, unsigned int &ts_usec);
		bool DoesFileExist(const string& strFilePath);
	private: 
		std::vector<CapturePacket*> m_PacketQueue;
	};
}
