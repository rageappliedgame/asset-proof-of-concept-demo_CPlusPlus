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

#pragma message ("VEG Bridge.h is part of the demo app.")

//#include <IDataStorage.h>
//#include <IDataArchive.h>
//#include <IDefaultSettings.h>

#include <ILog.h>
#include <IBridge.h>

using namespace std;

namespace fs = std::experimental::filesystem;

namespace rage
{
	class Bridge : public IBridge, ILog
	{
	public:
		Bridge();
		virtual ~Bridge() {};

		//bool Delete(const std::string& name);
		//bool Exists(const std::string& name);
		//std::vector<std::string> Files();
		//std::string Load(const std::string& name);
		//void Save(const std::string& name, const std::string& data);

		void Log(Severity severity, const std::string& msg);

		//bool Archive(const std::string& name);

		//bool hasDefaultSettings(const std::string& clazz, const std::string& id);
		//std::string loadDefaultSettings(const std::string& clazz, const std::string& id);
		//void saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData);
	private:
		//fs::path storageDir{ (boost::format(".%1%%2%") % PATH_SEPARATOR % "DataStorage").str() };
		// 
		fs::path storageDir;// : fs::path(".");// = "./DataStorage";
		fs::path archiveDir;// = "./ArchiveStorage";
	};
}

#endif // BRIDGE_H
