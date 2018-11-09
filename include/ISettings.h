// file:	include\ISettings.h
//
// summary:	Declares the ISettings interface
#ifndef ISETTINGS_H
#define ISETTINGS_H

// Include the polymorphic serialization and registration mechanisms
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/xml.hpp>


// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// A settings interface (used for type-safety).
	/// </summary>
	class ISettings
	{
	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~ISettings() {}
	private:

		/// <summary>
		/// An access.
		/// </summary>
		friend class cereal::access;

		/// <summary>
		/// Serialize this object to the given stream.
		/// </summary>
		///
		/// <typeparam name="Archive"> Type of the archive. </typeparam>
		/// <param name="ar"> [in,out] The archive. </param>
		template<class Archive>
		void serialize(Archive & ar)
		{
			//ar();
		}
	};
}

CEREAL_REGISTER_TYPE(rage::ISettings)

#endif // ISETTINGS_H
