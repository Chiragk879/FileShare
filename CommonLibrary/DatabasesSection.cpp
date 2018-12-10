#include "stdafx.h"
#include "DatabasesSection.h"
#include "XMLReader.h"

using namespace IMFS;

DatabasesSection::DatabasesSection()
{
}
DatabasesSection::~DatabasesSection()
{
}

void DatabasesSection::ReadSectionData()
{
    XMLReader reader;
    reader.ReadSection(SectionTypes::Databases, this);
}
