#pragma once

namespace IMFS
{
    class IManIDHash;
    //
    // A unique identifier for an IMan item
    //
    class IManID
    {
        friend class IManIDHash;
        friend class PathManager;

    protected:
        typedef unsigned __int64 IMANID;
        IMANID m_ID;

    public:

        //
        // constructors and operators
        //
        IManID();
        IManID(byte DatabaseID_, unsigned int DocNum_, unsigned short Version_);
        IManID(byte DatabaseID_, unsigned int FolderNum_);
        IManID(const IManID& ID_);
        IManID(uint64_t ID_);

        IManID& operator=(const IManID& ID_);

        inline bool operator==(const IManID& ID_) const
        {
            return m_ID == ID_.m_ID;
        }

        inline bool operator!=(const IManID& ID_) const
        {
            return m_ID != ID_.m_ID;
        }

        inline bool operator<(const IManID& ID_) const
        {
            return m_ID < ID_.m_ID;
        }

        inline bool operator>(const IManID& ID_) const
        {
            return m_ID > ID_.m_ID;
        }

    public:

        //
        // Expose the underlying object
        //
        LARGE_INTEGER GetID(void) const;

    public:

        //
        // Extract information relevant to WorkSite
        //
        bool IsTemporary(void) const;
        unsigned int GetDocNum(void) const;
        unsigned int GetFolderNum(void) const;
        unsigned short GetVersion(void) const;
        byte GetDatabaseID(void) const;
        bool isFolder(void) const;

        void SetVersion(unsigned short version);

    public:
        //
        // Creates a unique IManID to hold a temporary ID for a newly
        // created document.
        //
        static IManID CreateTemporaryDocID();

        //
        // Creates a unique IManID to hold a temporary ID for a newly
        // created folder.
        //
        static IManID CreateTemporaryFolderID();

    private:
        static long ms_nextTemporaryDocNum;
        static long ms_nextTemporaryFolderNum;

    private:
        // Size of UCharMap and LCharMap for algorithm of generation short names of format 8.3
        const static uint8_t m_charMapSize = 32;

        static wchar_t m_UCharMap[m_charMapSize];
        static wchar_t m_LCharMap[m_charMapSize];

        static unsigned __int64 m_Masks[12];
        static unsigned __int64 m_SplitMaskA;
        static unsigned __int64 m_SplitMaskB;
        static unsigned __int64 m_CombineMaskA;
        static unsigned __int64 m_CombineMaskB;

        string GenerateShortName();

        friend class ContentCache; //to use the private constructor declared below
    };

    class IManIDHash
    {
    public:
        IManIDHash() = default;
        std::size_t operator()(const IManID &object)
        {
            IManID::IMANID id = object.m_ID;
            return std::hash<LONGLONG>{}(id);
        }
    };


    // A linked list of nodes and parent nodes
    class IManIDNode
    {
    public:
        IManIDNode();
        IManIDNode(const IManID& id);
        IManIDNode(const IManID& id, IManIDNode *parent);
        ~IManIDNode();

        const IManID& GetID() const;
        void SetID(const IManID& id);
        void SetParent(IManIDNode *parent);
        const IManIDNode* GetParent() const;

    public:
        // obviously need deep copies
        IManIDNode(const IManIDNode& copy);
        IManIDNode& operator=(const IManIDNode& copy);

    private:
        IManID id;
        IManIDNode *parent;
    };
}
