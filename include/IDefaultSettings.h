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
#ifndef IDEFAULTSETTINGS_H
#define IDEFAULTSETTINGS_H

#include <string>


 // namespace: rage
 //
 // summary:	.
namespace rage
{
	/// <summary>
	/// A default settings interface for the Bridge (used for loading default settings).
	/// </summary>
	class IDefaultSettings
	{
	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~IDefaultSettings() {};

		/// <summary>
		/// Query if 'clazz' has default settings.
		/// </summary>
		///
		/// <param name="clazz"> The clazz. </param>
		/// <param name="id">    The identifier. </param>
		///
		/// <returns>
		/// True if default settings, false if not.
		/// </returns>
		virtual bool hasDefaultSettings(const std::string& clazz, const std::string& id) = 0;

		/// <summary>
		/// Loads default settings.
		/// </summary>
		///
		/// <param name="clazz"> The clazz. </param>
		/// <param name="id">    The identifier. </param>
		///
		/// <returns>
		/// The default settings.
		/// </returns>
		virtual std::string loadDefaultSettings(const std::string& clazz, const std::string& id) = 0;

		/// <summary>
		/// Saves a default settings.
		/// </summary>
		///
		/// <param name="clazz">    The clazz. </param>
		/// <param name="id">	    The identifier. </param>
		/// <param name="fileData"> Information describing the file. </param>
		virtual void saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData) = 0;
	};
}

#endif // IDEFAULTSETTINGS_H
