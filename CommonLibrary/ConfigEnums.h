#pragma once

namespace IMFS
{
    /// <summary>
    /// One or more of the following flags MAY be combined to specify the type of software a file server is running.
    /// The SV_TYPE flags indicate the services that are available on the server.
    /// </summary>
    enum ServerType
    {
        /// <summary>
        /// A server running the WorkStation Service
        /// </summary>
        WORKSTATION = 0x00000001,
        /// <summary>
        /// A server running the Server Service
        /// </summary>
        SERVER = 0x00000002,
        /// <summary>
        /// Any server running with SQL Server
        /// </summary>
        SQLSERVER = 0x00000004,
        /// <summary>
        /// Primary domain controller
        /// </summary>
        DOMAIN_CTRL = 0x00000008,
        /// <summary>
        /// Backup domain controller
        /// </summary>
        DOMAIN_BAKCTRL = 0x00000010,
        /// <summary>
        /// Server is available as a time source for network time synchronization
        /// </summary>
        TIME_SOURCE = 0x00000020,
        /// <summary>
        /// Apple File Protocol server
        /// </summary>
        AFP = 0x00000040,
        /// <summary>
        /// Novell server
        /// </summary>
        NOVELL = 0x00000080,
        /// <summary>
        /// LAN Manager 2.x domain member
        /// </summary>
        DOMAIN_MEMBER = 0x00000100,
        /// <summary>
        /// Servers maintained by the browser
        /// </summary>
        LOCAL_LIST_ONLY = 0x40000000,
        /// <summary>
        /// Server sharing print queue
        /// </summary>
        PRINTQ_SERVER = 0x00000200,
        /// <summary>
        /// Server running dial-in service
        /// </summary>
        DIALIN_SERVER = 0x00000400,
        /// <summary>
        /// Xenix server
        /// </summary>
        XENIX_SERVER = 0x00000800,
        /// <summary>
        /// Microsoft File and Print for NetWare
        /// </summary>
        SERVER_MFPN = 0x00004000,
        /// <summary>
        /// Windows Server 2003, Windows XP, Windows 2000, or Windows NT
        /// </summary>
        NT = 0x00001000,
        /// <summary>
        /// Server running Windows for Workgroups
        /// </summary>
        WFW = 0x00002000,
        /// <summary>
        /// Windows Server 2003, Windows 2000 Server, or server that is not a domain controller
        /// </summary>
        SERVER_NT = 0x00008000,
        /// <summary>
        /// Server that can run the browser service
        /// </summary>
        POTENTIAL_BROWSER = 0x00010000,
        /// <summary>
        /// Server running a browser service as backup
        /// </summary>
        BACKUP_BROWSER = 0x00020000,
        /// <summary>
        /// Server running the master browser service
        /// </summary>
        MASTER_BROWSER = 0x00040000,
        /// <summary>
        /// Server running the domain master browser
        /// </summary>
        DOMAIN_MASTER = 0x00080000,
        /// <summary>
        /// Primary domain
        /// </summary>
        DOMAIN_ENUM = 0x80000000,
        /// <summary>
        /// Windows Me, Windows 98, or Windows 95
        /// </summary>
        WINDOWS = 0x00400000,
        /// <summary>
        /// Terminal Server
        /// </summary>
        TERMINALSERVER = 0x02000000,
        /// <summary>
        /// Server clusters available in the domain
        /// </summary>
        CLUSTER_NT = 0x10000000,
        /// <summary>
        /// Cluster virtual servers available in the domain
        /// </summary>
        CLUSTER_VS_NT = 0x04000000
    };

    /// <summary>
    /// List of server capabilities
    /// </summary>
    enum SmbCapabilities
    {
        /// <summary>
        /// The server supports SMB_COM_READ_RAW and SMB_COM_WRITE_RAW requests.
        /// </summary>
        CAP_RAW_MODE = 0x00000001,

        /// <summary>
        /// The server supports SMB_COM_READ_MPX and SMB_COM_WRITE_MPX requests.
        /// </summary>
        CAP_MPX_MODE = 0x00000002,

        /// <summary>
        /// The server supports 16-bit Unicode characters.
        /// </summary>
        CAP_UNICODE = 0x00000004,

        /// <summary>
        /// The server supports large files with 64-bit offsets.
        /// </summary>
        CAP_LARGE_FILES = 0x00000008,

        /// <summary>
        /// The server supports the SMB packets particular to the NTLM 0.12 dialect.
        /// </summary>
        CAP_NT_SMBS = 0x00000010,

        /// <summary>
        /// The server supports the use of Microsoft RPC for remote API calls that would 
        /// otherwise use the legacy Remote Administration Protocol, as specified in [MS-RAP].
        /// </summary>
        CAP_RPC_REMOTE_APIS = 0x00000020,

        /// <summary>
        /// The server is capable of responding with 32-bit status codes in the Status 
        /// field of the SMB Header (for more information, see 2.2.1).
        /// </summary>
        CAP_STATUS32 = 0x00000040,

        /// <summary>
        /// The server supports level II oplocks.
        /// </summary>
        CAP_LEVEL_II_OPLOCKS = 0x00000080,

        /// <summary>
        /// The server supports the SMB_COM_LOCK_AND_READ command requests.
        /// </summary>
        CAP_LOCK_AND_READ = 0x00000100,

        /// <summary>
        /// The server supports the TRANS2_FIND_FIRST2, TRANS2_FIND_NEXT2, and FIND_CLOSE2
        /// command requests.
        /// </summary>
        CAP_NT_FIND = 0x00000200,

        /// <summary>
        /// The server is aware of the Distributed File System (DFS) Referral Protocol, 
        /// as specified in [MS-DFSC], and can respond to Microsoft DFS referral requests.
        /// For more information, see [MSDFS].
        /// </summary>
        CAP_DFS = 0x00001000,

        /// <summary>
        /// The server supports Windows NT information level requests, as specified in 
        /// section 2.2.13. This allows the client to pass native Windows NT structures 
        /// (as specified in [MS-FSCC]) in QUERY and SET operations, 
        /// as specified in section 2.2.13.
        /// </summary>
        CAP_INFOLEVEL_PASSTHRU = 0x00002000,

        /// <summary>
        /// The server supports large read operations. This capability affects the maximum
        /// size, in bytes, of the server buffer for sending an SMB_COM_WRITE_ANDX response 
        /// to the client. When this capability is set by the server (and set by the client 
        /// in the SMB_COM_SESSION_SETUP_ANDX request (section 2.2.4)), the maximum server 
        /// buffer size for sending data can be up to 65,535 bytes rather than the 
        /// MaxBufferSize field. Therefore, the server can send a single SMB_COM_WRITE_ANDX 
        /// response to the client up to this size.
        /// </summary>
        CAP_LARGE_READX = 0x00004000,

        /// <summary>
        /// The server supports large write operations. This capability affects the maximum size,
        /// in bytes, of the server buffer for receiving an SMB_COM_WRITE_ANDX client request. 
        /// When this capability is set by the server (and set by the client in the 
        /// SMB_COM_SESSION_SETUP_ANDX request (section 2.2.4)), the maximum server buffer
        /// size can be up to 65,535 bytes rather than the MaxBufferSize field. 
        /// Therefore, a client can send a single SMB_COM_WRITE_ANDX request up to this size.
        /// </summary>
        CAP_LARGE_WRITEX = 0x00008000,

        /// <summary>
        /// The server supports the FSCTL_SRV_REQUEST_RESUME_KEY (as specified in sections
        /// 2.2.14.7.2 and 2.2.14.8.2) FSCTL that was sent as an SMB_COM_NT_TRANSACTION_REQUEST 
        /// with an NT_TRANSACT_IOCTL subcommand, as specified in section 2.2.14.72.2.14.7.
        /// </summary>
        CAP_LWIO = 0x00010000,

        /// <summary>
        /// The server supports UNIX extensions. For more information, see [SNIA].
        /// </summary>
        CAP_UNIX = 0x00800000,

        /// <summary>
        /// The server supports compressed SMB packets
        /// </summary>
        CAP_COMPRESSED_DATA = 0x02000000,

        /// <summary>
        /// The server supports re-authentication, if required, as specified in section 3.1.5.1.
        /// </summary>
        CAP_DYNAMIC_REAUTH = 0x20000000,

        /// <summary>
        /// The server supports persistent handles.
        /// </summary>
        CAP_PERSISTENT_HANDLES = 0x40000000,

        /// <summary>
        /// The server supports extended security for authentication, as specified in 
        /// section 3.2.4.2.3. This bit is used in conjunction with the 
        /// SMB_FLAGS2_EXTENDED_SECURITY Flags2 field in the SMB Header (bit 11), 
        /// as specified in SMB Header Extensions and Changes.
        /// </summary>
        CAP_EXTENDED_SECURITY = 0x80000000
    };

    /// <summary>
    /// List of SMB2 Server capabilities
    /// </summary>
    enum Smb2Capabilities
    {
        SMB2_GLOBAL_CAP_NONE = 0x00000000,
        /// <summary>
        /// When set, indicates that the client supports the Distributed File System (DFS).
        /// </summary>
        SMB2_GLOBAL_CAP_DFS = 0x00000001,
        /// <summary>
        /// When set, indicates that the client supports leasing.
        /// </summary>
        SMB2_GLOBAL_CAP_LEASING = 0x00000002,
        /// <summary>
        /// When set, indicates that the client supports multi-credit operations.
        /// </summary>
        SMB2_GLOBAL_CAP_LARGE_MTU = 0x00000004,
        /// <summary>
        /// When set, indicates that the client supports establishing multiple channels for a single session.
        /// </summary>
        SMB2_GLOBAL_CAP_MULTI_CHANNEL = 0x00000008,
        /// <summary>
        /// When set, indicates that the client supports persistent handles.
        /// </summary>
        SMB2_GLOBAL_CAP_PERSISTENT_HANDLES = 0x00000010,
        /// <summary>
        /// When set, indicates that the client supports directory leasing.
        /// </summary>
        SMB2_GLOBAL_CAP_DIRECTORY_LEASING = 0x00000020,
        /// <summary>
        /// When set, indicates that the client supports encryption.
        /// </summary>
        SMB2_GLOBAL_CAP_ENCRYPTION = 0x00000040,
    };

    /// <summary>
    /// Security mode field.
    /// </summary>
    enum SecurityMode
    {
        /// <summary>
        /// When set, indicates user mode security. 
        /// When not set, indicates share mode security, 
        /// as specified in [CIFS] section 4.1.1 Bit 0).
        /// </summary>
        USER_SECURITY = 0x01,
        /// <summary>
        /// When set, indicates the client MUST encrypt passwords.
        /// When not set, indicates the client MUST send plain-text passwords for user 
        /// level security mode and share level security mode, as specified in 
        /// section [CIFS] section 4.1.1, "Bit 1".
        /// </summary>
        ENCRYPT_PASSWORDS = 0x02,
        /// <summary>
        /// When set, security signatures (SMB sequence numbers) MAY be used.
        /// </summary>
        SECURITY_SIGNATURES_ENABLED = 0x04,
        /// <summary>
        /// When set, security signatures (SMB sequence numbers) MUST be used.
        /// </summary>
        SECURITY_SIGNATURES_REQUIRED = 0x08,
    };

    /// <summary>
    /// SMB2 Security mode field.
    /// </summary>
    enum class Smb2SecurityMode : uint16_t
    {
        /// <summary>
        /// When set, indicates that security signatures are enabled on the server 
        /// </summary>
        SMB2_NEGOTIATE_SIGNING_ENABLED = 0x0001,
        /// <summary>
        /// When set, indicates that security signatures are required by the server.
        /// </summary>
        SMB2_NEGOTIATE_SIGNING_REQUIRED = 0x0002,
    };

    /// <summary>
    /// The following values are used to specify the type of a shared resource.
    /// Zero or more of the SPECIAL and TEMPORARY flags MAY be combined with the 
    /// previous values to further specify the characteristics of a shared resource.
    /// </summary>    
    enum ShareTypes
    {
        /// <summary>
        /// Disk drive
        /// </summary>
        DISKTREE = 0x00000000,
        /// <summary>
        /// Print queue
        /// </summary>
        PRINTQ = 0x00000001,
        /// <summary>
        /// Communication device
        /// </summary>
        DEVICE = 0x00000002,
        /// <summary>
        /// Interprocess communication (IPC)
        /// </summary>
        IPC = 0x00000003,
        /// <summary>
        /// Special share reserved for interprocess communication (IPC$) or remote administration of the server (ADMIN$). Can also refer to administrative shares such as C$, D$, E$, and so forth.
        /// </summary>
        SPECIAL = 0x80000000,
        /// <summary>
        /// A temporary share that is not persisted for creation each time the file server initializes.
        /// </summary>
        TEMPORARY = 0x40000000
    };

}