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
