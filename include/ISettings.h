#ifndef ISETTINGS_H
#define ISETTINGS_H

// Include the polymorphic serialization and registration mechanisms
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/xml.hpp>

namespace rage
{
	class ISettings
	{
	public:
		virtual ~ISettings() {}
	private:
		friend class cereal::access;

		template<class Archive>
		void serialize(Archive & ar)
		{
			//ar();
		}
	};
}

CEREAL_REGISTER_TYPE(rage::ISettings)

#endif // ISETTINGS_H
