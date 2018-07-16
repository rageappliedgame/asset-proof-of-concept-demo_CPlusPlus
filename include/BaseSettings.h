#ifndef BASESETTINGS_H
#define BASESETTINGS_H

#include <ISettings.h>

// Include the polymorphic serialization and registration mechanisms
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/xml.hpp>

namespace rage
{
	class BaseSettings : public ISettings
	{
	public:
		BaseSettings() {};
		virtual ~BaseSettings() {};
		void setSettings(BaseSettings* settings);
	private:
		friend class cereal::access;
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
