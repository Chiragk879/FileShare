#pragma once

namespace IMFS
{
    /// <summary>
    /// Dos error code
    /// </summary>
    enum ErrorCode
    {
        /* SMB X/Open error codes for the ERRDOS error class */
        /// <summary>
        /// No error 
        /// </summary>
        ERRsuccess = 0,
        /// <summary>
        /// Invalid function (or system call) 
        /// </summary>
        ERRbadfunc = 1,
        /// <summary>
        /// File not found (pathname error) 
        /// </summary>
        ERRbadfile = 2,
        /// <summary>
        /// Directory not found 
        /// </summary>
        ERRbadpath = 3,
        /// <summary>
        /// Too many open files 
        /// </summary>
        ERRnofids = 4,
        /// <summary>
        /// Access denied 
        /// </summary>
        ERRnoaccess = 5,
        /// <summary>
        /// Invalid fid 
        /// </summary>
        ERRbadfid = 6,
        /// <summary>
        /// Memory control blocks destroyed. 
        /// </summary>
        ERRbadmcb = 7,
        /// <summary>
        /// Out of memory 
        /// </summary>
        ERRnomem = 8,
        /// <summary>
        /// Invalid memory block address 
        /// </summary>
        ERRbadmem = 9,
        /// <summary>
        /// Invalid environment 
        /// </summary>
        ERRbadenv = 10,
        /// <summary>
        /// Bad Format 
        /// </summary>
        ERRbadformat = 11,
        /// <summary>
        /// Invalid open mode 
        /// </summary>
        ERRbadaccess = 12,
        /// <summary>
        /// Invalid data (only from ioctl call) 
        /// </summary>
        ERRbaddata = 13,
        /// <summary>
        /// reserved 
        /// </summary>
        ERRres = 14,
        /// <summary>
        /// Invalid drive 
        /// </summary>
        ERRbaddrive = 15,
        /// <summary>
        /// Attempt to delete current directory 
        /// </summary>
        ERRremcd = 16,
        /// <summary>
        /// rename/move across different filesystems 
        /// </summary>
        ERRdiffdevice = 17,
        /// <summary>
        /// no more files found in file search 
        /// </summary>
        ERRnofiles = 18,
        /// <summary>
        /// General failure 
        /// </summary>
        ERRgeneral = 31,
        /// <summary>
        /// Share mode on file conflict with open mode 
        /// </summary>
        ERRbadshare = 32,
        /// <summary>
        /// Lock request conflicts with existing lock 
        /// </summary>
        ERRlock = 33,
        /// <summary>
        /// Request unsupported, returned by Win 95, RJS 20Jun98 
        /// </summary>
        ERRunsup = 50,
        /// <summary>
        /// Network name deleted or not available 
        /// </summary>
        ERRnetnamedel = 64,
        /// <summary>
        /// You specified an invalid share name 
        /// </summary>
        ERRnosuchshare = 67,
        /// <summary>
        /// File in operation already exists 
        /// </summary>
        ERRfilexists = 80,
        /// <summary>
        /// Invalid parameter
        /// </summary>
        ERRinvalidparam = 87,
        /// <summary>
        /// Cannot open the file specified 
        /// </summary>
        ERRcannotopen = 110,
        /// <summary>
        /// Buffer overflow
        /// </summary>
        ERRbufferoverflow = 111,
        /// <summary>
        /// Insuficient client buffer
        /// </summary>
        ERRinsufficientbuffer = 122,
        /// <summary>
        /// Invalid name 
        /// </summary>
        ERRinvalidname = 123,
        /// <summary>
        /// Unknown level
        /// </summary>
        ERRunknownlevel = 124,
        /// <summary>
        /// This region is not locked by this locking context. 
        /// </summary>
        ERRnotlocked = 158,
        /// <summary>
        /// The specified path is not valid
        /// </summary>
        ERRinvalidpath = 161,
        /// <summary>
        /// Cancel violation
        /// </summary>
        ERRcancelviolation = 173,
        /// <summary>
        /// No atomic locks
        /// </summary>
        ERRnoatomiclocks = 174,
        /// <summary>
        /// Rename
        /// </summary>
        ERRrename = 183,
        /// <summary>
        /// Named pipe invalid 
        /// </summary>
        ERRbadpipe = 230,
        /// <summary>
        /// All instances of pipe are busy 
        /// </summary>
        ERRpipebusy = 231,
        /// <summary>
        /// named pipe close in progress 
        /// </summary>
        ERRpipeclosing = 232,
        /// <summary>
        /// No process on other end of named pipe 
        /// </summary>
        ERRnotconnected = 233,
        /// <summary>
        /// More data to be returned 
        /// </summary>
        ERRmoredata = 234,
        /// <summary>
        /// from EMC 
        /// </summary>
        ERReainconsistent = 255,
        /// <summary>
        /// No more items
        /// </summary>
        ERRnomoreitems = 259,
        /// <summary>
        /// Invalid directory name in a path. 
        /// </summary>
        ERRbaddirectory = 267,
        /// <summary>
        /// Extended attributes 
        /// </summary>
        ERReasnotsupported = 282,
        /// <summary>
        /// Unknown username or bad password 
        /// </summary>
        ERRlogonfailure = 1326,
        /// <summary>
        /// Buffer too small
        /// </summary>
        ERRbuftoosmall = 2123,
        /// <summary>
        /// Unknown IPC
        /// </summary>
        ERRunknownipc = 2142,
        /// <summary>
        /// No such print job
        /// </summary>
        ERRnosuchprintjob = 2151,
        /// <summary>
        /// Invalid group
        /// </summary>
        ERRinvgroup = 2455,
        /// <summary>
        /// don't support ipc 
        /// </summary>
        ERRnoipc = 66,
        /// <summary>
        /// ERROR_PRINTER_DRIVER_ALREADY_INSTALLED 
        /// </summary>
        ERRdriveralreadyinstalled = 1795,
        /// <summary>
        /// ERROR_UNKNOWN_PORT 
        /// </summary>
        ERRunknownprinterport = 1796,
        /// <summary>
        /// ERROR_UNKNOWN_PRINTER_DRIVER 
        /// </summary>
        ERRunknownprinterdriver = 1797,
        /// <summary>
        /// ERROR_UNKNOWN_PRINTPROCESSOR 
        /// </summary>
        ERRunknownprintprocessor = 1798,
        /// <summary>
        /// ERROR_INVALID_SEPARATOR_FILE 
        /// </summary>
        ERRinvalidseparatorfile = 1799,
        /// <summary>
        /// ERROR_INVALID_PRIORITY 
        /// </summary>
        ERRinvalidjobpriority = 1800,
        /// <summary>
        /// ERROR_INVALID_PRINTER_NAME 
        /// </summary>
        ERRinvalidprintername = 1801,
        /// <summary>
        /// ERROR_PRINTER_ALREADY_EXISTS 
        /// </summary>
        ERRprinteralreadyexists = 1802,
        /// <summary>
        /// ERROR_INVALID_PRINTER_COMMAND 
        /// </summary>
        ERRinvalidprintercommand = 1803,
        /// <summary>
        /// ERROR_INVALID_DATATYPE 
        /// </summary>
        ERRinvaliddatatype = 1804,
        /// <summary>
        /// ERROR_INVALID_ENVIRONMENT 
        /// </summary>
        ERRinvalidenvironment = 1805,
        /// <summary>
        /// ERROR_UNKNOWN_PRINT_MONITOR 
        /// </summary>
        ERRunknownprintmonitor = 3000,
        /// <summary>
        /// ERROR_PRINTER_DRIVER_IN_USE 
        /// </summary>
        ERRprinterdriverinuse = 3001,
        /// <summary>
        /// ERROR_SPOOL_FILE_NOT_FOUND 
        /// </summary>
        ERRspoolfilenotfound = 3002,
        /// <summary>
        /// ERROR_SPL_NO_STARTDOC 
        /// </summary>
        ERRnostartdoc = 3003,
        /// <summary>
        /// ERROR_SPL_NO_ADDJOB 
        /// </summary>
        ERRnoaddjob = 3004,
        /// <summary>
        /// ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED 
        /// </summary>
        ERRprintprocessoralreadyinstalled = 3005,
        /// <summary>
        /// ERROR_PRINT_MONITOR_ALREADY_INSTALLED 
        /// </summary>
        ERRprintmonitoralreadyinstalled = 3006,
        /// <summary>
        /// ERROR_INVALID_PRINT_MONITOR 
        /// </summary>
        ERRinvalidprintmonitor = 3007,
        /// <summary>
        /// ERROR_PRINT_MONITOR_IN_USE 
        /// </summary>
        ERRprintmonitorinuse = 3008,
        /// <summary>
        /// ERROR_PRINTER_HAS_JOBS_QUEUED 
        /// </summary>
        ERRprinterhasjobsqueued = 3009,

        /* Error codes for the ERRSRV class */
        /// <summary>
        /// Non specific error code 
        /// </summary>
        ERRerror = 1,
        /// <summary>
        /// Bad password 
        /// </summary>
        ERRbadpw = 2,
        /// <summary>
        /// reserved 
        /// </summary>
        ERRbadtype = 3,
        /// <summary>
        /// No permissions to do the requested operation 
        /// </summary>
        ERRaccess = 4,
        /// <summary>
        /// tid invalid 
        /// </summary>
        ERRinvnid = 5,
        /// <summary>
        /// Invalid servername 
        /// </summary>
        ERRinvnetname = 6,
        /// <summary>
        /// Invalid device 
        /// </summary>
        ERRinvdevice = 7,
        /// <summary>
        /// Print queue full 
        /// </summary>
        ERRqfull = 49,
        /// <summary>
        /// Queued item too big 
        /// </summary>
        ERRqtoobig = 50,
        /// <summary>
        /// Invalid print file in smb_fid 
        /// </summary>
        ERRinvpfid = 52,
        /// <summary>
        /// Unrecognised command 
        /// </summary>
        ERRsmbcmd = 64,
        /// <summary>
        /// smb server internal error 
        /// </summary>
        ERRsrverror = 65,
        /// <summary>
        /// fid and pathname invalid combination 
        /// </summary>
        ERRfilespecs = 67,
        /// <summary>
        /// reserved 
        /// </summary>
        ERRbadlink = 68,
        /// <summary>
        /// Access specified for a file is not valid 
        /// </summary>
        ERRbadpermits = 69,
        /// <summary>
        /// reserved 
        /// </summary>
        ERRbadpid = 70,
        /// <summary>
        /// attribute mode invalid 
        /// </summary>
        ERRsetattrmode = 71,
        /// <summary>
        /// Message server paused 
        /// </summary>
        ERRpaused = 81,
        /// <summary>
        /// Not receiving messages 
        /// </summary>
        ERRmsgoff = 82,
        /// <summary>
        /// No room for message 
        /// </summary>
        ERRnoroom = 83,
        /// <summary>
        /// too many remote usernames 
        /// </summary>
        ERRrmuns = 87,
        /// <summary>
        /// operation timed out 
        /// </summary>
        ERRtimeout = 88,
        /// <summary>
        /// No resources currently available for request. 
        /// </summary>
        ERRnoresource = 89,
        /// <summary>
        /// too many userids 
        /// </summary>
        ERRtoomanyuids = 90,
        /// <summary>
        /// bad userid 
        /// </summary>
        ERRbaduid = 91,
        /// <summary>
        /// temporarily unable to use raw mode, use MPX mode 
        /// </summary>
        ERRuseMPX = 250,
        /// <summary>
        /// temporarily unable to use raw mode, use standard mode 
        /// </summary>
        ERRuseSTD = 251,
        /// <summary>
        /// resume MPX mode 
        /// </summary>
        ERRcontMPX = 252,
        /// <summary>
        /// No support
        /// </summary>
        ERRnosupport = 0xFFFF,
        /// <summary>
        /// from NT 3.5 response 
        /// </summary>
        ERRunknownsmb = 22,

        /* Error codes for the ERRHRD class */
        /// <summary>
        /// read only media 
        /// </summary>
        ERRnowrite = 19,
        /// <summary>
        /// Unknown device 
        /// </summary>
        ERRbadunit = 20,
        /// <summary>
        /// Drive not ready 
        /// </summary>
        ERRnotready = 21,
        /// <summary>
        /// Unknown command 
        /// </summary>
        ERRbadcmd = 22,
        /// <summary>
        /// Data (CRC) error 
        /// </summary>
        ERRdata = 23,
        /// <summary>
        /// Bad request structure length 
        /// </summary>
        ERRbadreq = 24,
        /// <summary>
        /// Seek
        /// </summary>
        ERRseek = 25,
        /// <summary>
        /// Bad media
        /// </summary>
        ERRbadmedia = 26,
        /// <summary>
        /// Bad sector
        /// </summary>
        ERRbadsector = 27,
        /// <summary>
        /// No paper
        /// </summary>
        ERRnopaper = 28,
        /// <summary>
        /// write fault 
        /// </summary>
        ERRwrite = 29,
        /// <summary>
        /// read fault 
        /// </summary>
        ERRread = 30,
        /// <summary>
        /// General hardware failure
        /// </summary>
        ERRhardgeneral = 31,
        /// <summary>
        /// Wrong disk
        /// </summary>
        ERRwrongdisk = 34,
        /// <summary>
        /// FCN unavailable
        /// </summary>
        ERRFCBunavail = 35,
        /// <summary>
        /// share buffer exceeded 
        /// </summary>
        ERRsharebufexc = 36,
        /// <summary>
        /// Disk full
        /// </summary>
        ERRdiskfull = 39
    };


    /// <summary>
    /// Dos error class
    /// </summary>
    enum ErrorClass
    {
        /// <summary>
        /// Error is from the core DOS operating system set.
        /// </summary>
        ERRDOS = 0x01,
        /// <summary>
        /// Error is generated by the server network file manager.
        /// </summary>
        ERRSRV = 0x02,
        /// <summary>
        /// Error is an hardware error.
        /// </summary>
        ERRHRD = 0x03,
        /// <summary>
        /// /* Command was not in the "SMB" format. */
        /// </summary>
        ERRCMD = 0xFF
    };

}