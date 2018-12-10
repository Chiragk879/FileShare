#include "stdafx.h"
#include "XmlReader.h"

using namespace IMFS;

AccessRightsSection::AccessRightsSection()
{
    deniedFileRights = 0;
    deniedFolderRights = 0;
}
AccessRightsSection::~AccessRightsSection()
{
}

void AccessRightsSection::ReadSectionData()
{
    XMLReader reader;
    reader.ReadSection(SectionTypes::AccessRights, this);
}
