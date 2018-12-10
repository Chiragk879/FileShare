#pragma once

namespace IMFS
{
    /// <summary>
    /// Authentication types.
    /// </summary>
    enum AuthType
    {
        /// <summary>
        /// Unknown auth
        /// </summary>
        UnknownAuth,
        /// <summary>
        /// Clear auth
        /// </summary>
        ClearAuth,
        /// <summary>
        /// NT LM auth
        /// </summary>
        NtlmAuth,
        /// <summary>
        /// Negotioate auth
        /// </summary>
        NegotiateAuth
    };

}