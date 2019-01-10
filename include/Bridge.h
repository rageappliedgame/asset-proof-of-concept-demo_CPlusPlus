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
#ifndef BRIDGE_H
#define BRIDGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>

#include <experimental/filesystem>

#include <IBridge.h>

#include <ILog.h>
#include <IDataStorage.h>
#include <IDataArchive.h>
#include <IDefaultSettings.h>

using namespace std;

namespace fs = std::experimental::filesystem;

#pragma message ("VEG Bridge.h is part of the demo app.")

namespace rage
{
	/// <summary>
	/// A bridge.
	/// </summary>
	class Bridge : public IBridge, public ILog, public IDataStorage, public IDataArchive, public IDefaultSettings
	{
	public:

		/// <summary>
		/// Default constructor.
		/// </summary>
		Bridge();

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~Bridge() {};

		/// <summary>
		/// Deletes the given name.
		/// </summary>
		///
		/// <param name="name"> The name to delete. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool Delete(const std::string& name);

		/// <summary>
		/// Determine if 'name' exists.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool Exists(const std::string& name);

		/// <summary>
		/// Gets the files.
		/// </summary>
		///
		/// <returns>
		/// A std::vector&lt;std::string&gt;
		/// </returns>
		std::vector<std::string> Files();

		/// <summary>
		/// Loads the given name.
		/// </summary>
		///
		/// <param name="name"> The name to load. </param>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		std::string Load(const std::string& name);

		/// <summary>
		/// Saves.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		/// <param name="data"> The data. </param>
		void Save(const std::string& name, const std::string& data);

		/// <summary>
		/// Logs.
		/// </summary>
		///
		/// <param name="severity"> The severity. </param>
		/// <param name="msg">	    The message. </param>
		void Log(Severity severity, const std::string& msg);

		/// <summary>
		/// Archives the given name.
		/// </summary>
		///
		/// <param name="name"> The name. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool Archive(const std::string& name);

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
		bool hasDefaultSettings(const std::string& clazz, const std::string& id);

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
		std::string loadDefaultSettings(const std::string& clazz, const std::string& id);

		/// <summary>
		/// Saves a default settings.
		/// </summary>
		///
		/// <param name="clazz">    The clazz. </param>
		/// <param name="id">	    The identifier. </param>
		/// <param name="fileData"> Information describing the file. </param>
		void saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData);
	private:

		/// <summary>
		/// The base dir (current directory).
		/// </summary>
		fs::path baseDir = ".";

		/// <summary>
		/// Examples: fs::path("."); or "." + PATH_SEPARATOR + "DataStorage";
		/// </summary>
		fs::path storageDir = baseDir / "DataStorage";

		/// <summary>
		/// Examples: fs::path("."); or "." + PATH_SEPARATOR + "ArchiveStorage";
		/// </summary>
		fs::path archiveDir = baseDir / "ArchiveStorage";

		/// <summary>
		/// Derive asset name.
		/// </summary>
		///
		/// <param name="className"> Name of the class. </param>
		/// <param name="id">		 The identifier. </param>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		std::string deriveAssetName(std::string className, std::string id);
	};
}

#endif // BRIDGE_H
