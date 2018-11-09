// file:	src\BaseAsset.cpp
//
// summary:	Implements the base asset class
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

/// <summary>
/// Constructor.
/// </summary>
///
/// <param name="className"> Name of the class. </param>
BaseAsset::BaseAsset(string className)
{
	this->className = className;
	this->id = AssetManager::getInstance().registerAssetInstance(*this, this->getClassName());

	std::stringstream fn;
	fn << this->className << ".VersionAndDependencies.xml";
	string versionInfoXMLFile = fn.str();

	this->versionInfo = new RageVersionInfo();
	versionInfo->LoadVersionInfo(versionInfoXMLFile);
	this->bridge = nullptr;
}

/// <summary>
/// Destructor.
/// </summary>
BaseAsset::~BaseAsset()
{
	AssetManager::getInstance().unregisterAssetInstance(this->getId());

	delete versionInfo;
}

/// <summary>
/// Gets the identifier.
/// </summary>
///
/// <returns>
/// The identifier.
/// </returns>
string BaseAsset::getId()
{
	return this->id;
}

/// <summary>
/// Gets class name.
/// </summary>
///
/// <returns>
/// The class name.
/// </returns>
string BaseAsset::getClassName()
{
	return this->className;
}

/// <summary>
/// Gets the bridge.
/// </summary>
///
/// <returns>
/// Null if it fails, else the bridge.
/// </returns>
IBridge* BaseAsset::getBridge()
{
	return this->bridge;
}

/// <summary>
/// Sets a bridge.
/// </summary>
///
/// <param name="bridge"> [in,out] If non-null, the bridge. </param>
void BaseAsset::setBridge(IBridge* bridge)
{
	this->bridge = bridge;
}

/// <summary>
/// Gets the dependencies.
/// </summary>
///
/// <returns>
/// The dependencies.
/// </returns>
std::map<std::string, std::string> BaseAsset::getDependencies()
{
	return this->versionInfo->getDependencies();
}

/// <summary>
/// Gets the maturity.
/// </summary>
///
/// <returns>
/// The maturity.
/// </returns>
std::string BaseAsset::getMaturity()
{
	return this->versionInfo->getMaturity();
}

/// <summary>
/// Gets the version.
/// </summary>
///
/// <returns>
/// The version.
/// </returns>
std::string BaseAsset::getVersion()
{
	return this->versionInfo->getVersion();
}

/// <summary>
/// Query if this object has settings.
/// </summary>
///
/// <returns>
/// True if settings, false if not.
/// </returns>
bool BaseAsset::hasSettings()
{
	return (this->settings != nullptr);
}

/// <summary>
/// Sets the settings.
/// </summary>
///
/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
void BaseAsset::setSettings(ISettings* settings)
{
	this->settings = settings;
}

/// <summary>
/// Loads default settings.
/// </summary>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
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

/// <summary>
/// Loads the settings.
/// </summary>
///
/// <param name="fileName"> Filename of the file. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
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

/// <summary>
/// Saves a default settings.
/// </summary>
///
/// <param name="force"> True to force. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
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

/// <summary>
/// Saves the settings.
/// </summary>
///
/// <param name="fileName"> Filename of the file. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
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

/// <summary>
/// Settings from XML.
/// </summary>
///
/// <param name="xml"> The XML. </param>
///
/// <returns>
/// Null if it fails, else a pointer to the ISettings.
/// </returns>
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
