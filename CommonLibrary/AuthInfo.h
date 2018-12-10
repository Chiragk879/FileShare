#pragma once

#include <cstdint>
#include <vector>

namespace IMFS
{
    /// <summary>
    /// Auth info
    /// </summary>
	class AuthInfo : public IM::ObjectSignature
    {
		public:
			/// <summary>
			/// Login name
			/// </summary>
			BSTR LoginName;
			/// <summary>
			/// Access token
			/// </summary>
			HANDLE AccessToken;
			/// <summary>
			/// Session key
			/// </summary>
			std::vector<uint8_t> SessionKey;

		public:
			AuthInfo& operator=(const AuthInfo& copy);

		private:
			BSTR m_loginName;
		public:
			AuthInfo();
			virtual ~AuthInfo();

    };

}