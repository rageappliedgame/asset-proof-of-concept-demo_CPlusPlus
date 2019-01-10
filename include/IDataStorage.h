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
#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include <string>
#include <vector>


 // namespace: rage
 //
 // summary:	.
namespace rage
{
	/// <summary>
	/// A data storage interface for the Bridge (used for saving/loading data).
	/// </summary>
	class IDataStorage
	{
	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~IDataStorage() {}

		/// <summary>
		/// Deletes the given name.
		/// </summary>
		///
		/// <param name="name"> The name to delete. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		virtual bool Delete(const std::string& name) = 0;

		/// <summary>
		/// Determine if 'name' exists.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		virtual bool Exists(const std::string& name) = 0;

		/// <summary>
		/// Gets the files.
		/// </summary>
		///
		/// <returns>
		/// A std::vector&lt;std::string&gt;
		/// </returns>
		virtual std::vector<std::string> Files() = 0;

		/// <summary>
		/// Loads the given name.
		/// </summary>
		///
		/// <param name="name"> The name to load. </param>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		virtual std::string Load(const std::string& name) = 0;

		/// <summary>
		/// Saves.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		/// <param name="data"> The data. </param>
		virtual void Save(const std::string& name, const std::string& data) = 0;
	};
}

#endif // IDATASTORAGE_H
