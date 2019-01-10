/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union�s Horizon
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
#ifndef IDATAARCHIVE_H
#define IDATAARCHIVE_H


 // namespace: rage
 //
 // summary:	.
namespace rage
{
	/// <summary>
	/// A data archive interface for the Bridge (used for archiving data).
	/// </summary>
	class IDataArchive
	{
	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~IDataArchive() {}

		/// <summary>
		/// Archives the given name.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		virtual bool Archive(const std::string& name) = 0;
	};
}

#endif // IDATAARCHIVE_H
