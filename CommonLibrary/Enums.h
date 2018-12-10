#pragma once

namespace IMFS
{
	enum DeviceState
    {
        /// <summary>
        /// No state.
        /// </summary>
        DC_NONE = 0x000,
        /// <summary>
        /// 8-bit count to control pipe instancing.
        /// </summary>
        ICount = 0x00FF,
        /// <summary>
        /// This bit field indicates the client read mode for the named pipe.
        /// </summary>
        ReadMode = 0x0100,
        /// <summary>
        /// This bit field indicates the type of the named pipe when the named pipe 
        /// was created by the server.
        /// </summary>
        NamedPipeType = 0x0400,
        /// <summary>
        /// A value that indicates the endpoint of the pipe.
        /// </summary>
        EndPoint = 0x4000,
        /// <summary>
        /// If set, indicates that named pipe read requests return immediately if no 
        /// data is available, and writes return immediately.
        /// </summary>
        Blocking = 0x8000,
    };
}