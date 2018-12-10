#pragma once

namespace IMFS
{
    /// <summary>
    /// Class that contains static function usefull when working with date/time objects
    /// </summary>
    class DateTimeHelper : public IM::ObjectSignature
    {
    public:
        /// <summary>
        /// Get MS-DOS date
        /// </summary>
        /// <param name="ft"><see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> structure containing the file time to convert to MS-DOS date format</param>
        /// <returns>MS-DOS date packed in an <see cref="ushort"/> value</returns>
        /// <remarks>
        /// The date is a packed value with the following format:
        /// <list type="table">
        ///     <listheader>
        ///         <term>Bits</term>
        ///         <description>Description</description>
        ///     </listheader>
        ///     <item>
        ///         <term>0-4</term>
        ///         <description>Day of the month (1–31)</description>
        ///     </item>
        ///     <item>
        ///         <term>5–8</term>
        ///         <description>Month (1 = January, 2 = February, etc.)</description>
        ///     </item>
        ///     <item>
        ///         <term>9-15</term>
        ///         <description>Year offset from 1980 (add 1980 to get actual year)</description>
        ///     </item>
        /// </list>
        /// </remarks>
        static ushort GetDate(FILETIME& ft);

        /// <summary>
        /// Date time 2 long
        /// </summary>
        /// <param name="dateTime">Date time</param>
        static __int64 DateTime2Long(FSDateTime& dateTime);

        /// <summary>
        /// Dos time 2 date time
        /// </summary>
        /// <param name="date">Date</param>
        /// <param name="time">Time</param>
        static void DosTime2DateTime(ushort date, ushort time, FSDateTime& outTime);

        /// <summary>
        /// Dos date time 2 file time
        /// </summary>
        /// <param name="date">Date</param>
        /// <param name="time">Time</param>
        static void DosDateTime2FileTime(ushort date, ushort time, FILETIME& fileTime);

        /// <summary>
        /// Get MS-DOS time
        /// </summary>
        /// <param name="ft"><see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> structure containing the file time to convert to MS-DOS time format</param>
        /// <returns>MS-DOS date packed in an <see cref="ushort"/> value</returns>
        /// <remarks>
        /// The time is a packed value with the following format:
        /// <list type="table">
        ///     <listheader>
        ///         <term>Bits</term>
        ///         <description>Description</description>
        ///     </listheader>
        ///     <item>
        ///         <term>0-4</term>
        ///         <description>Second divided by 2</description>
        ///     </item>
        ///     <item>
        ///         <term>5–10</term>
        ///         <description>Minute (0–59)</description>
        ///     </item>
        ///     <item>
        ///         <term>11-15</term>
        ///         <description>Hour (0–23 on a 24-hour clock)</description>
        ///     </item>
        /// </list>
        /// </remarks>
        static ushort GetTime(FILETIME& ft);

        /// <summary>
        /// Get a long from a <see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> structure
        /// </summary>
        /// <param name="fileTime"><see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> structure containing the file time to convert</param>
        /// <returns>A long value containing the <paramref name="fileTime"/> </returns>
        static uint64_t FileTime2Long(const FILETIME& fileTime);

        /// <summary>
        /// Get a <see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> from a long value
        /// </summary>
        /// <param name="fileTime">Value to be converted</param>
        /// <returns><see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> structure converted from <paramref name="fileTime"/> </returns>
        static void Long2FileTime(__int64 fileTime, FILETIME& outFileTime);

        /// <summary>
        /// Date time 2 file time
        /// </summary>
        /// <param name="dateTime">Date time</param>
        static void DateTime2FileTime(FSDateTime& dateTime, FILETIME& time);

        /// <summary>
        /// Get a <see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> object from a <see cref="FSDateTime"/>.
        /// </summary>
        /// <param name="dateTime"><see cref="FSDateTime"/> FSDateTime to be converted to a <see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> object</param>
        /// <returns><see cref="System.Runtime.InteropServices.ComTypes.FILETIME"/> object converted from <paramref name="dateTime"/></returns>
        static FILETIME DateTime2FileTimeUtc(const FSDateTime& dateTime);

        /// <summary>
        /// Get current time in UTC timezone
        /// </summary>
        /// <returns>Current time in UTC</returns>
        static __int64 GetCurrentSmbTime();

        /// <summary>
        /// Convert time from Unit Timestamp to Windowd FILETIME.
        /// </summary>
        static __int64 GetSmbTime(const time_t& time);

        /// <summary>
        /// Convert time from Windowd FILETIME to Unix timestamp.
        /// </summary>
        static std::time_t FileTime2TimeT(const FILETIME& ts);
        static std::time_t FileTime2TimeT(const LARGE_INTEGER& ts);

        /// <summary>
        /// Return timestamp in readable format
        /// </summary>
        static IMFS::string TimeToStr(const std::time_t& ts);

        /// <summary>
        /// Return filetime in readable format
        /// </summary>
        static IMFS::string FileTimeToStr(const FILETIME& fileTime);

        /// <summary>
        /// Return filetime represented as large integer in readable format
        /// </summary>
        static IMFS::string LargeIntegerFileTimeToStr(const LARGE_INTEGER& fileTime);

        /// <summary>
        /// Get current time zone in seconds span
        /// </summary>
        /// <returns>Current time zone in seconds span</returns>
        static int64_t GetSmbTimeZone();

        /// <summary>
        /// Converts a file time to local file time.
        /// </summary>
        /// <param name="fileTime">File time</param>
        /// <returns>Local file time</returns>
        static void FileTime2LocalFileTime(FILETIME &fileTime, FILETIME &outFileTime);

        /// <summary>
        /// File time to date time
        /// </summary>
        /// <param name="fileTime">File time</param>
        static void FileTimeToDateTime(FILETIME& fileTime, FSDateTime& outDateTime);

        /// <summary>
        /// Set milliseconds to 0
        /// </summary>
        /// <param name="fsDateTime">Date time</param>
        static FILETIME ClearMilliseconds(const FSDateTime& fsDateTime);
    };
}