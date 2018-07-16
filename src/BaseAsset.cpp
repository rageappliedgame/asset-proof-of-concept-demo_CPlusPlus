#include <BaseAsset.h>

#include <AssetManager.h>
#include <IDefaultSettings.h>

#include <sstream>
#include <ostream>
#include <istream>
#include <fstream>

#include <cereal/archives/xml.hpp>

using namespace std;
using namespace rage;
using namespace cereal;

BaseAsset::BaseAsset(string className)
{
	this->className = className;
	this->id = AssetManager::getInstance()->registerAssetInstance(*this, this->getClassName());

	std::stringstream fn;
	fn << this->className << ".VersionAndDependencies.xml";
	string versionInfoXMLFile = fn.str();

	this->versionInfo = new RageVersionInfo();
	versionInfo->LoadVersionInfo(versionInfoXMLFile);
	this->bridge = nullptr;
}

BaseAsset::~BaseAsset()
{
	AssetManager::getInstance()->unregisterAssetInstance(this->getId());

	delete versionInfo;
}

string BaseAsset::getId()
{
	return this->id;
}

string BaseAsset::getClassName()
{
	return this->className;
}

IBridge* BaseAsset::getBridge()
{
	return this->bridge;
}

void BaseAsset::setBridge(IBridge* bridge)
{
	this->bridge = bridge;
}

std::map<std::string, std::string> BaseAsset::getDependencies()
{
	return this->versionInfo->getDependencies();
}

std::string BaseAsset::getMaturity()
{
	return this->versionInfo->getMaturity();
}

std::string BaseAsset::getVersion()
{
	return this->versionInfo->getVersion();
}

bool BaseAsset::hasSettings()
{
	return (this->settings != nullptr);
}

void BaseAsset::setSettings(ISettings* settings)
{
	this->settings = settings;
}

bool BaseAsset::loadDefaultSettings()
{
	IDefaultSettings* ds = getInterface<IDefaultSettings>();
	if (ds != nullptr && hasSettings() && ds->hasDefaultSettings(className, id))
	{
		std::string xml = ds->loadDefaultSettings(className, id);

		//XX this->settings = settingsFromXml(xml);
		return true;

	}
	return false;
}

bool BaseAsset::loadSettings(std::string fileName)
{
	IDataStorage* ds = getInterface<IDataStorage>();
	if (ds != nullptr && hasSettings() && ds->Exists(fileName))
	{
		std::string xml = ds->Load(fileName);

		//XX this->settings = settingsFromXml(xml);
		return true;
	}
	return false;
}

bool BaseAsset::saveDefaultSettings(bool force)
{
	IDefaultSettings* ds = getInterface<IDefaultSettings>();
	if (ds != nullptr && hasSettings() && (force || ds->hasDefaultSettings(className, id)))
	{
		//XX ds->saveDefaultSettings(className, id, settingsToXml());
		return true;
	}
	return false;
}

bool BaseAsset::saveSettings(std::string fileName)
{
	IDataStorage* ds = getInterface<IDataStorage>();
	if (ds != nullptr && hasSettings())
	{
		//xxx ds->Save(fileName, settingsToXml());
		return true;
	}
	return false;
}

ISettings* BaseAsset::settingsFromXml(std::string xml)
{
	ISettings* settings = new ISettings();
	std::stringstream stream;
	stream << xml;

	cereal::XMLInputArchive archive(stream);

	//XX archive(settings);

	// archive and stream closed when destructors are called

	return settings;
}
