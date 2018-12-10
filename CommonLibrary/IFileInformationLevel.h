#pragma once

namespace IMFS
{
    /// <summary>
    /// IFile information level
    /// </summary>
    struct /* interface */ IFileInformationLevel
    {
		public:
			/// <summary>
			/// Information level
			/// </summary>
			virtual FileInfoByHandleClass getInformationLevel() const = 0;

            virtual ~IFileInformationLevel() = default;
    };
    using IFileInformationLevelPtr=std::shared_ptr<IFileInformationLevel>;

}