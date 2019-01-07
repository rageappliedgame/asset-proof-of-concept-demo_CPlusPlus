#ifndef ASSETSETTINGS_H
#define ASSETSETTINGS_H

#include <BaseSettings.h>

#include <string>
#include <vector>

// Include the polymorphic serialization and registration mechanisms
#include <cereal/types/polymorphic.hpp>
#include <cereal/archives/xml.hpp>

#pragma message ("VEG AssetSetting.h is part of the demo app.")

namespace rage
{
	class AssetSettings : public BaseSettings
	{
	public:
		AssetSettings() {};
		virtual ~AssetSettings() {};

		std::string getTestProperty();
		void setTestProperty(std::string testProperty);

		std::vector<std::string> getTestList();
		void setTestList(std::vector<std::string> testList);

		void setSettings(AssetSettings* settings) {
			rage::BaseSettings::setSettings(this);
		};
		bool isTestReadOnly();
	private:
		friend class cereal::access;

		template <class Archive>
		void serialize(Archive & ar)
		{
			ar(testProperty, testReadOnly);

			// cereal still fails on the testList std::vector.
			//ar(testProperty, testReadOnly, testList);
		}

		std::string testProperty = "Hello Default World";
		bool testReadOnly = true;
		std::vector<std::string> testList = { "Hello", "List", "World" };
	};
}

CEREAL_REGISTER_TYPE(rage::AssetSettings)
CEREAL_REGISTER_POLYMORPHIC_RELATION(rage::BaseSettings, rage::AssetSettings)
CEREAL_SPECIALIZE_FOR_ALL_ARCHIVES(rage::AssetSettings, cereal::specialization::member_serialize)

#endif // ASSETSETTINGS_H
