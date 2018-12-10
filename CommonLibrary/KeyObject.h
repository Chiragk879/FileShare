#pragma once

namespace IMFS
{
    /// <summary>
    /// An object that extends this can participate in an STL map
	/// that contains different types of objects (polymorphic).  This works
	/// provided that it provides a key which a) uniquely distinguishes 
	/// itself from other instances of its type, and, b) distinguishes 
	/// itself from other instances of any subtype!  
	///
	/// This is why we use a Guid -- to give a huge namespace across types.
    /// </summary>
	class KeyObject
	{
		public:
			virtual const Guid& GetObjectKey() const = 0;

		public:
			virtual ~KeyObject();
	};

}