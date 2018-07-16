#ifndef BRIDGE_H
#define BRIDGE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <istream>
#include <string>

#include <experimental/filesystem>

#pragma message ("VEG This is part of the demo app")

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
