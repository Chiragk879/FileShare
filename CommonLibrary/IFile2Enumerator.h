#pragma once

namespace IMFS
{
    class Folder2;

    // This follows .Net's IEnumerator; e.g.:
    //		while(x.MoveNext())
    //		{
    //			File f;
    //			ApiRet y = x.Current(f);
    //			if (ERROR_SUCCESS != y) return y;
    //			// do stuff with f...
    //		}
    //		x.Reset(); // if we want to re-use x
    class IFile2Enumerator
    {
        friend class Folder2;

    public:
        virtual ApiRet MoveNext(const size_t count_ = 1) = 0; // The parameter is used to simulate having called MoveNext() "count_" times.
        virtual void Reset(void) = 0;
        virtual ApiRet Current(File2& file_) const = 0;
        virtual bool IsEmpty(void) = 0;

        // don't call this unless you really really know what you're doing
        virtual void RenameInsideDataProvider(ConstNormalizedPathPtr pNewName_) = 0;

    protected:
        virtual IFile2Enumerator* Clone(void) const = 0;
    };
}