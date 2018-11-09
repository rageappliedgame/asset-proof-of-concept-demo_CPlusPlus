// file:	include\BaseSettings.h
//
// summary:	Declares the base settings class
#ifndef BASESETTINGS_H
#define BASESETTINGS_H

#include <ISettings.h>

// Include the polymorphic serialization and registration mechanisms
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/xml.hpp>


// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// A base settings.
	/// </summary>
	class BaseSettings : public ISettings
	{
	public:

		/// <summary>
		/// Default constructor.
		/// </summary>
		BaseSettings() {};

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~BaseSettings() {};

		/// <summary>
		/// Sets the settings.
		/// </summary>
		///
		/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
		void setSettings(BaseSettings* settings);
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
		template <class Archive>
		void serialize(Archive & ar)
		{
			//ar();
		}
	};
}

CEREAL_REGISTER_TYPE(rage::BaseSettings)
CEREAL_REGISTER_POLYMORPHIC_RELATION(rage::ISettings, rage::BaseSettings)

#endif // BASESETTINGS_H
