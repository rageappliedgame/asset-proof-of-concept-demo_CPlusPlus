/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union’s Horizon
 * 2020 research and innovation programme under grant agreement No 644187.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
