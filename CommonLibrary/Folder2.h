#pragma once

namespace IMFS
{

    class Folder2 : public virtual IM::ObjectSignature, public File2
    {
    public:
        IFile2Enumerator& GetDocuments(void)	{ return *m_pDocuments; }
        IFile2Enumerator& GetSubfolders(void)	{ return *m_pSubfolders; }

        Folder2();
        Folder2(ConstNormalizedPathPtr pFileName_, IFile2Enumerator* pDocuments_, IFile2Enumerator* pSubfolders_);
        virtual ~Folder2(void);
        Folder2(const Folder2& x_);
        Folder2& operator=(const Folder2& x_);

    public:
        bool IsEmpty() const;

        // don't call this unless you really really know what you're doing
        virtual void RenameInsideDataProvider(ConstNormalizedPathPtr pNewName_);

        static string FolderAccessRightsToString(DWORD mask);
        static void SetAlwaysAccessRights(DWORD& dwMask);
        static void SetGenericRights(DWORD& dwMask);

    protected:
        IFile2Enumerator *m_pDocuments;
        IFile2Enumerator *m_pSubfolders;
    };

    using Folder2Ptr = std::shared_ptr<Folder2>;
}