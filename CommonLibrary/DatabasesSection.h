#pragma once

namespace IMFS
{
    /// <summary>
    /// Represents databases and associated IDs section within the configuration file.
    /// The IDs are arbitrary, but global throughout the server.
    /// </summary>
    class DatabasesSection : public ConfigurationSection
    {
    public:
        /// <summary>
        /// Gets a configuration element containing a collection of dialect configuration elements.
        /// </summary>
        ///[ConfigurationProperty("Databases", IsDefaultCollection = false)]
        std::list<DatabasesElement> Databases;
    public:
        DatabasesSection();
        virtual ~DatabasesSection();

        void ReadSectionData();
    };
}
