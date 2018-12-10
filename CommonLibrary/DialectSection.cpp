#include "stdafx.h"
#include "dialectsSection.h"
#include "XMLReader.h"

using namespace IMFS;

DialectsSection::DialectsSection()
{
}

DialectsSection::~DialectsSection()
{
}

void DialectsSection::ReadSectionData()
{
    XMLReader reader;
    reader.ReadSection(SectionTypes::Dialects, this);

    auto foundIt = std::find_if(Dialects.begin(), Dialects.end(), [](const DialectElement& element) {
        return (element.Enabled);
    });

    if (foundIt == Dialects.end())
        IMLOG_ERROR(L"Unable to find the activated dialects. Clients cannot communicate.");
}

DialectElement DialectsSection::GetDialect(const string &dialectName) const
{
    auto foundIt = std::find_if(Dialects.begin(), Dialects.end(), [&dialectName](const DialectElement& element) {
        return ((element.Name == dialectName) && element.Enabled);
    });

    if (foundIt == Dialects.end())
        return DialectElement();
    else
        return *foundIt;
}
