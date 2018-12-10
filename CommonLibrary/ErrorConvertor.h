#pragma once

namespace IMFS
{
    /// <summary>
    /// Error convertor
    /// </summary>
    class ErrorConvertor
    {
	private:
		static ErrorConvertor ms_instance;

		ErrorConvertor();
		~ErrorConvertor();

        /// <summary>
        /// Nt status 2 dos error
        /// </summary>
		static std::map<NtStatus, uint> ntStatus2DosError;
        /// <summary>
        /// Api return 2 nt status
        /// </summary>
        static std::map<ApiRet, NtStatus> apiRet2NtStatus;

        /// <summary>
        /// Initialize nt status 2 dos error
        /// </summary>
        static void InitializeNtStatus2DosError();

        /// <summary>
        /// Initialize api return 2 nt status
        /// </summary>
        static void InitializeApiRet2NtStatus();

	public:
        /// <summary>
        /// Get DosError error code from a <see cref="NtStatus"/> error code
        /// </summary>
        /// <param name="status">Error code in <see cref="NtStatus"/> format</param>
        /// <returns>DosError error code</returns>
        static uint DosError(NtStatus status);

        /// <summary>
        /// Get <see cref="NtStatus"/> from a <see cref="ApiRet"/> error code
        /// </summary>
        /// <param name="apiRet">Error code in <see cref="ApiRet"/> format</param>
        /// <returns><see cref="NtStatus"/> error code</returns>
        static NtStatus ApiRet2NtStatus(ApiRet apiRet);

        /// <summary>
        /// Is dos code
        /// </summary>
        /// <param name="status">Status</param>
        static bool IsDosCode(NtStatus status);

        /// <summary>
        /// Pack dos in nt status
        /// </summary>
        /// <param name="dosClass">Dos class</param>
        /// <param name="dosCode">Dos code</param>
        static NtStatus PackDosInNtStatus(byte dosClass, ushort dosCode);

        /// <summary>
        /// Unpack dos error class
        /// </summary>
        /// <param name="status">Status</param>
        static byte UnpackDosErrorClass(NtStatus status);

        /// <summary>
        /// Unpack dos error code
        /// </summary>
        /// <param name="status">Status</param>
        static ushort UnpackDosErrorCode(NtStatus status);
    };

}