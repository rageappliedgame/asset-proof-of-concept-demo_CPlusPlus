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
