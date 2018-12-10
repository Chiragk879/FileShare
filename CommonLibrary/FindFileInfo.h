#pragma once

namespace IMFS
{
    enum class ReturnPathNameAs : uint8_t
    {
        OriginalName,
        Dot,
        DotDot
    };

    /// <summary>
    /// Base class used for passing find file information between IFS, IVFS and Protocol handler
    /// </summary>
    class FindFileInfo2
    {
    public:
        /// <summary>
        /// File name
        /// </summary>
        virtual ConstNormalizedPathPtr GetFileName() = 0;
        virtual void SetFileName(ConstNormalizedPathPtr value) = 0;

        /// <summary>
        /// Resume key
        /// </summary>
        virtual uint GetResumeKey() = 0;
        virtual void SetResumeKey(uint value) = 0;


        virtual void SetReturnPathNameAs(ReturnPathNameAs value) = 0;
        virtual ReturnPathNameAs GetReturnPathNameAs() = 0;

    public:
        FindFileInfo2();
        virtual ~FindFileInfo2();
    };
    using FindFileInfo2Ptr=std::shared_ptr<FindFileInfo2>;
    using FindFileInfo2Array=std::vector<FindFileInfo2Ptr>;
    using FindFileInfo2ArrayPtr=std::shared_ptr<FindFileInfo2Array>;
}
