#pragma once

namespace IMFS
{
    /// Represents dialects section within the configuration file.
    class DialectsSection : public ConfigurationSection
    {
    public:
        /// Gets a configuration element containing a collection of dialect configuration elements.
        std::list<DialectElement> Dialects;

        DialectElement GetDialect(const string &dialectName) const;

    public:
        DialectsSection();
        virtual ~DialectsSection();

        void ReadSectionData();
    };
}
