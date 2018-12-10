#include "stdafx.h"

using namespace IMFS;

//
// Two forms.  The first form is for a permanent ID, as assigned by DMS.
//
//     More Significant...                                ...Less Significant
//       |                                                                |
//       |<------------------------------64------------------------------>|
//       |                                                                |
//       |       <--------------------------57--------------------------->|
//       |<--7-->1<---------------------46---------------------><---10--->|
//	         |   |                       |                           |      
//	         |   |                       |                           |      
//	         |   |                       |                           |      
//   DatabaseID isFolder      ItemID (DocNum/FolderNum)           Version
//
// The second is for a temporary ID, used for newly created docs/folders that do 
// not yet have an ID in the back end system:
//
//     More Significant...                                ...Less Significant
//       |                                                                |
//       |<------------------------------64------------------------------>|
//       |<--7-->1<xxxxx 14 xxxx><------32---------------------><xx 10 xx>|
//	         |   |        |              |                           |      
//	         |   |        |              |                           |      
//	         |   |        |              |                           |      
//     TmpIDInd isFolder Resvd.   Temp ID (unique)                Reserved
//
//  * The TmpIDInd is always all 1's
//
//  * We assume at most 127 databases
//  * We assume at most 1023 versions per docnum

#define DatabaseIDMask		0xFE00000000000000
#define TempIndicatorMask	0xFE00000000000000
#define isFolderMask		0x0100000000000000
#define ItemIDMask			0x00FFFFFFFFFFFC00
#define VersionMask			0x00000000000003FF

#define DatabaseIDShift		57
#define TempIndicatorShift	57
#define ItemIDShift			10

//
// Short file name support:
//
// An IManID has 64 bits of info
//
// 63                                                             0
// DDDDDDDFIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIVVVVVVVVVV
//
// D = Db
// F = IsFolder
// I = Item ID
// V = Version
//
// This splits nicely into eleven 6-bit chunks for our 8.3 file name, 
// with two bits to spare!
//
// Unfortunately, there are not enough valid case-insensitive characters to
// which to map our 6-bit value.
//
// The best we can do is split this into 5-bit chunks, and map each
// chunk to one of 32 characters.  That would require 13 characters to 
// encode the entire 64-bit id and, of course, we can only use 11 for a 
// valid 8.3 short name.
//
// We are taking a shortcut.  We allow 46-bits for Item ID but at
// present it is only 32-bits.  Therefore, we can ignore 14 bits, 
// bringing us down to 55 bits of information.
//
// 55 bits splits nicely into 10 chunks of 5 bits each, for a
// an 8.3 filename with ~ at the start.
//
// DDDDDDDF--------------IIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIVVVVVVVVVV
//
// The bitmasks for each character are as follows
//
// 1. "~"
// 2. 1111100000000000000000000000000000000000000000000000000000000000
// 3. 0000011100000000000000110000000000000000000000000000000000000000
// 4. 0000000000000000000000001111100000000000000000000000000000000000
// 5. 0000000000000000000000000000011111000000000000000000000000000000
// 6. 0000000000000000000000000000000000111110000000000000000000000000
// 7. 0000000000000000000000000000000000000001111100000000000000000000
// 8. 0000000000000000000000000000000000000000000011111000000000000000
// 9. "."
// 10 0000000000000000000000000000000000000000000000000111110000000000
// 11 0000000000000000000000000000000000000000000000000000001111100000
// 12 0000000000000000000000000000000000000000000000000000000000011111
//

wchar_t IManID::m_UCharMap[IManID::m_charMapSize] =
{
    L'0', L'4', L'8', L'C', L'G', L'K', L'N', L'R', L'V', L'Z',
    L'1', L'5', L'9', L'D', L'H', L'L', L'P', L'S', L'W', L'!',
    L'2', L'6', L'B', L'F', L'J', L'M', L'Q', L'T', L'X', L'@',
    L'3', L'7'
};

wchar_t IManID::m_LCharMap[IManID::m_charMapSize] =
{
    L'0', L'4', L'8', L'c', L'g', L'k', L'n', L'r', L'v', L'z',
    L'1', L'5', L'9', L'd', L'h', L'l', L'p', L's', L'w', L'!',
    L'2', L'6', L'b', L'f', L'j', L'm', L'q', L't', L'x', L'@',
    L'3', L'7'
};

unsigned __int64 IManID::m_Masks[12] =
{
    0x0000000000000000,  // "~"
    0xF800000000000000,
    0x0000000000000000,  // split into two masks, below
    0x000000F800000000,
    0x00000007C0000000,
    0x000000003E000000,
    0x0000000001F00000,
    0x00000000000F8000,
    0x0000000000000000,  // "."
    0x0000000000007C00,
    0x00000000000003E0,
    0x000000000000001F,
};

// a. 0000011100000000000000000000000000000000000000000000000000000000
unsigned __int64 IManID::m_SplitMaskA = 0x0700000000000000;
// b. 0000000000000000000000110000000000000000000000000000000000000000
unsigned __int64 IManID::m_SplitMaskB = 0x0000030000000000;

// a. 11100
unsigned __int64 IManID::m_CombineMaskA = 0x1C;
// b. 00011
unsigned __int64 IManID::m_CombineMaskB = 0x03;


long IManID::ms_nextTemporaryDocNum = 1;
long IManID::ms_nextTemporaryFolderNum = 1;

IManID::IManID()
    : m_ID(0)
{
}

IManID::IManID(byte DatabaseID_, unsigned int DocNum_, unsigned short Version_)
{
    IMFS_ASSERT(127 > DatabaseID_);
    IMFS_ASSERT(1024 > Version_);

    m_ID = ((IMANID)DatabaseID_ << DatabaseIDShift) +
        ((IMANID)DocNum_ << ItemIDShift) +
        Version_;
}

IManID::IManID(byte DatabaseID_, unsigned int FolderNum_)
{
    IMFS_ASSERT(127 > DatabaseID_);

    m_ID = ((IMANID)DatabaseID_ << DatabaseIDShift) +
        ((IMANID)FolderNum_ << ItemIDShift) +
        isFolderMask;
}

IManID::IManID(const IManID& ID_)
{
    m_ID = ID_.m_ID;
}

IManID::IManID(uint64_t ID_)
{
    m_ID = ID_;
}

IManID& IManID :: operator=(const IManID& ID_)
{
    if (&ID_ == this) return *this;
    m_ID = ID_.m_ID;
    return *this;
}

LARGE_INTEGER IManID::GetID(void) const
{
    LARGE_INTEGER liRet;
    liRet.QuadPart = m_ID;
    return liRet;
}

unsigned int IManID::GetDocNum(void) const
{
    if (IsTemporary())
    {
        IMFS_ASSERT(false); // there is no doc num, not yet a real doc in DMS
        return -1;
    }

    return (unsigned int)((m_ID & ItemIDMask) >> ItemIDShift);
}

unsigned int IManID::GetFolderNum(void) const
{
    if (IsTemporary())
    {
        IMFS_ASSERT(false); // there is no folder num, not yet a real folder in DMS
        return -1;
    }

    return (unsigned int)((m_ID & ItemIDMask) >> ItemIDShift);
}

unsigned short IManID::GetVersion(void) const
{
    if (IsTemporary())
    {
        IMFS_ASSERT(false); // there is no version, not yet a real item in DMS
        return -1;
    }

    return (unsigned short)(m_ID & VersionMask);
}

void IManID::SetVersion(unsigned short version)
{
    if (IsTemporary())
    {
        IMFS_ASSERT(false); // there is no version, not yet a real item in DMS
    }

    m_ID = (m_ID & ~(VersionMask)) | version;
}

byte IManID::GetDatabaseID(void) const
{
    if (IsTemporary())
    {
        IMFS_ASSERT(false); // there is no db id, not yet a real item in DMS
        return -1;
    }

    return (byte)((m_ID & DatabaseIDMask) >> DatabaseIDShift);
}

bool IManID::IsTemporary(void) const
{
    byte tmpInd = (byte)((m_ID & TempIndicatorMask) >> TempIndicatorShift);
    return (tmpInd == 0x7F);
}

bool IManID::isFolder(void) const
{
    return (m_ID & isFolderMask) > 0;
}

string IManID::GenerateShortName()
{
    string result;

    int shiftRight = 59;
    for (int i = 0; i < 12; i++)
    {
        switch (i)
        {
        case 0:
            result += (string)L'~';
            break;
        case 8:
            result += (string)L'.';
            break;
        case 2:
            // this is where we ignore 14 bits in the middle
        {
            unsigned __int64 mapIndexA = (m_ID & m_SplitMaskA);
            unsigned __int64 mapIndexB = (m_ID & m_SplitMaskB);
            mapIndexA = mapIndexA >> 54;
            mapIndexB = mapIndexB >> 40;
            unsigned __int64 mapIndex = mapIndexA | mapIndexB;
            IMFS_ASSERT(mapIndex <= m_charMapSize - 1);
            IMFS_ASSERT(mapIndex >= 0);
            wchar_t c = m_UCharMap[mapIndex];
            result += (string)c;
        }
        shiftRight -= 19;
        break;
        default:
        {
            unsigned __int64 mapIndex = (m_ID & m_Masks[i]);
            mapIndex = mapIndex >> shiftRight;
            IMFS_ASSERT(mapIndex <= m_charMapSize - 1);
            IMFS_ASSERT(mapIndex >= 0);
            wchar_t c = m_UCharMap[mapIndex];
            result += (string)c;

            shiftRight -= 5;
        }
        break;
        }
    }

    return result;
}

IManID IManID::CreateTemporaryDocID()
{
    long nextTempId = ::InterlockedIncrement(&ms_nextTemporaryDocNum);
    unsigned __int64 calculatedID = nextTempId;
    calculatedID = calculatedID << ItemIDShift;
    calculatedID = calculatedID | TempIndicatorMask;

    return calculatedID;
}

IManID IManID::CreateTemporaryFolderID()
{
    long nextTempId = ::InterlockedIncrement(&ms_nextTemporaryFolderNum);
    unsigned __int64 calculatedID = nextTempId;
    calculatedID = calculatedID << ItemIDShift;
    calculatedID = calculatedID | TempIndicatorMask;
    calculatedID = calculatedID | isFolderMask;
    return calculatedID;
}

IManIDNode::IManIDNode() : parent(NULL)
{
}

IManIDNode::IManIDNode(const IManID& id_) : id(id_), parent(NULL)
{
}

IManIDNode::IManIDNode(const IManID& id_, IManIDNode *parent_) : id(id_), parent(parent_)
{
}

IManIDNode::IManIDNode(const IManIDNode& copy)
{
    this->id = copy.id;
    if (copy.parent == NULL)
        this->parent = NULL;
    else
        this->parent = new IManIDNode(*copy.parent);
}

IManIDNode& IManIDNode :: operator=(const IManIDNode& copy)
{
    if (this == &copy)
        return *this;

    if (this->parent != NULL)
    {
        delete parent;
        parent = NULL;
    }

    this->id = copy.id;
    if (copy.parent == NULL)
        this->parent = NULL;
    else
        this->parent = new IManIDNode(*copy.parent);

    return *this;
}


IManIDNode :: ~IManIDNode()
{
    if (parent != NULL)
    {
        delete parent;
        parent = NULL;
    }
}

const IManID& IManIDNode::GetID() const
{
    return id;
}

void IManIDNode::SetParent(IManIDNode *value)
{
    parent = value;
}

const IManIDNode* IManIDNode::GetParent() const
{
    return parent;
}

void IManIDNode::SetID(const IManID& value)
{
    id = value;
}
