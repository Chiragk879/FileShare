#pragma once

namespace IMFS
{
	class DatabasesElement : public ConfigurationElement
	{
		public:
			/// <summary>
			/// Gets the database name.
			/// </summary>
			///[ConfigurationProperty("Name",
			///   IsRequired = true, IsKey = true)]
			string Name;

			/// <summary>
			/// Gets the database Id.
			/// </summary>
			///[ConfigurationProperty("Id",
			///	IsRequired = true)]
			int Id;

		public:
			DatabasesElement();
			virtual ~DatabasesElement();
	};
}