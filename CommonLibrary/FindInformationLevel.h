#pragma once

namespace IMFS
{
    /// <summary>
    /// Transaction 2 find information level.
    /// </summary>
    enum FindInfoLevel
    {
		SMB_INFO_ERROR = 0x000,       
		/// <summary>
        /// Standard Info.
        /// </summary>
        SMB_INFO_STANDARD = 0x0001,
        /// <summary>
        /// Query EA Size
        /// </summary>
        SMB_INFO_QUERY_EA_SIZE = 0x0002,
        /// <summary>
        /// Query EA's From List
        /// </summary>
        SMB_INFO_QUERY_EAS_FROM_LIST = 0x0003,
        /// <summary>
        /// Query All EA's
        /// </summary>
        SMB_INFO_QUERY_ALL_EAS = 0x0004,
        /// <summary>
        /// Directory Info (NT)
        /// </summary>
        SMB_FIND_FILE_DIRECTORY_INFO = 0x0101,
        /// <summary>
        /// Full Directory Info (NT)
        /// </summary>
        SMB_FIND_FILE_FULL_DIRECTORY_INFO = 0x0102,
        /// <summary>
        /// Names Info (NT)
        /// </summary>
        SMB_FIND_FILE_NAMES_INFO = 0x0103,
        /// <summary>
        /// Both Directory Info (NT)
        /// </summary>
        SMB_FIND_FILE_BOTH_DIRECTORY_INFO = 0x0104,
        /// <summary>
        /// ID Full Directory Info
        /// </summary>
        SMB_FIND_FILE_ID_FULL_DIRECTORY_INFO = 0x0105,
        /// <summary>
        /// ID Both Directory Info
        /// </summary>
        SMB_FIND_FILE_ID_BOTH_DIRECTORY_INFO = 0x0106,
        /// <summary>
        /// Unix Info
        /// </summary>
        SMB_FIND_FILE_UNIX = 0x0202
    };
}