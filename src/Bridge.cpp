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
#include "Bridge.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <experimental/filesystem>

#include <cereal/archives/xml.hpp>

#pragma message ("VEG Bridge.cpp is part of the demo app.")

namespace fs = std::experimental::filesystem;

using namespace std;
using namespace rage;

/// <summary>
/// Default constructor.
/// </summary>
Bridge::Bridge()
	:storageDir("./StorageDir"), archiveDir("./ArchiveStorage")
{
	if (!fs::is_directory(storageDir))
	{
		fs::create_directory(storageDir);
	}

	if (!fs::is_directory(archiveDir))
	{
		fs::create_directory(archiveDir);

	}
}

/// <summary>
/// Logs.
/// </summary>
///
/// <param name="severity"> The severity. </param>
/// <param name="msg">	    The message. </param>
void Bridge::Log(Severity severity, const std::string& msg)
{
	cout << severity << ": " << msg << endl;
}

/// <summary>
/// Gets the files.
/// </summary>
///
/// <returns>
/// A std::vector&lt;std::string&gt;
/// </returns>
std::vector<std::string> Bridge::Files()
{
	std::vector<std::string> files;
	fs::recursive_directory_iterator iter(storageDir), eod;

	for (fs::path const& p : iter)
	{
		if (is_regular_file(p))
		{
			files.push_back(p.filename().string());
		}
	}

	return files;
}

/// <summary>
/// Deletes the given name.
/// </summary>
///
/// <param name="name"> The name to delete. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
bool Bridge::Delete(const std::string& name)
{
	if (Exists(name))
	{
		fs::path p(storageDir);
		p /= name;
		fs::remove(p);
		return true;
	}
	return false;
}

/// <summary>
/// Loads the given name.
/// </summary>
///
/// <param name="name"> The name to load. </param>
///
/// <returns>
/// A std::string.
/// </returns>
std::string Bridge::Load(const std::string& name)
{
	fs::path p(storageDir);
	p /= name;
	ifstream file(p.string().c_str());
	if (!file)
	{
		cout << "File not found." << endl;
		std::string();
	}
	stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return buffer.str();
}

/// <summary>
/// Saves.
/// </summary>
///
/// <param name="name"> The name. </param>
/// <param name="data"> The data. </param>
void Bridge::Save(const std::string& name, const std::string& data)
{
	fs::path p(storageDir);
	p /= name;
	std::fstream fs;
	fs.open(p.string().c_str(), std::fstream::out);
	fs << data;
	fs.close();
}

/// <summary>
/// Determine if 'name' exists.
/// </summary>
///
/// <param name="name"> The name. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
bool Bridge::Exists(const std::string& name)
{
	fs::path p(storageDir);
	p /= name;
	return fs::exists(p);
}

/// <summary>
/// Archives the given name.
/// </summary>
///
/// <param name="name"> The name. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
bool Bridge::Archive(const std::string& name)
{
	fs::path ps(storageDir);
	ps /= name;

	fs::path pa(archiveDir);
	pa /= name;

	if (fs::exists(ps))
	{
		if (fs::exists(pa))
		{
			fs::remove(pa);
		}

		fs::path pan(archiveDir);

		char buffer[128];
		time_t t;
		time(&t);
		struct tm* timeinfo;
		timeinfo = localtime(&t);

		std::strftime(buffer, sizeof(buffer), "%Y-%m-%d [%H-%M-%S]", timeinfo);

		std::string stamp(buffer);

		stamp.append(" ");
		stamp.append(name);

		pan /= stamp;

		fs::rename(ps, pan);

		return true;
	}
	return false;
}

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
bool Bridge::hasDefaultSettings(const std::string& clazz, const std::string& id)
{
	std::string fileName = deriveAssetName(clazz, id);
	return Exists(fileName);
}

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
std::string Bridge::loadDefaultSettings(const std::string& clazz, const std::string& id)
{
	std::string fileName = deriveAssetName(clazz, id);
	return Load(fileName);
}

/// <summary>
/// Saves a default settings.
/// </summary>
///
/// <param name="clazz">    The clazz. </param>
/// <param name="id">	    The identifier. </param>
/// <param name="fileData"> Information describing the file. </param>
void Bridge::saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData)
{
	std::string fileName = deriveAssetName(clazz, id);
	Save(fileName, fileData);
}

/// <summary>
/// Derive asset name.
/// </summary>
///
/// <param name="clazz"> The clazz. </param>
/// <param name="id">    The identifier. </param>
///
/// <returns>
/// A std::string.
/// </returns>
std::string Bridge::deriveAssetName(std::string clazz, std::string id)
{
	return clazz + "AppSettings.xml";
}