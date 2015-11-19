#include <BaseAsset.h>

#include <AssetManager.h>
#include <IDefaultSettings.h>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>

#include <sstream>

using namespace std;
using namespace rage;

BaseAsset::BaseAsset(string className)
{
    this->className = className;
    this->id = AssetManager::getInstance()->registerAssetInstance(*this, this->getClassName());
    string versionInfoXMLFile = (boost::format("%1%.VersionAndDependencies.xml") % this->className).str();
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

ISettings* BaseAsset::getSettings()
{
    return this->settings;
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
        this->settings = settingsFromXml(xml);
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
        this->settings = settingsFromXml(xml);
        return true;
    }
    return false;
}

bool BaseAsset::saveDefaultSettings(bool force)
{
    IDefaultSettings* ds = getInterface<IDefaultSettings>();
    if (ds != nullptr && hasSettings() && (force || ds->hasDefaultSettings(className, id)))
    {
        ds->saveDefaultSettings(className, id, settingsToXml());
        return true;
    }
    return false;
}

bool BaseAsset::saveSettings(std::string fileName)
{
    IDataStorage* ds = getInterface<IDataStorage>();
    if (ds != nullptr && hasSettings())
    {
        ds->Save(fileName, settingsToXml());
        return true;
    }
    return false;
}

ISettings* BaseAsset::settingsFromXml(std::string xml)
{
    ISettings* settings = new ISettings();
    std::stringstream ss;
    ss << xml;
    boost::archive::xml_iarchive ia(ss);
    ia >> BOOST_SERIALIZATION_NVP(settings);
    // archive and stream closed when destructors are called

    return settings;
}

std::string BaseAsset::settingsToXml()
{
    std::stringstream ss;
    boost::archive::xml_oarchive oa(ss);
    oa << boost::serialization::make_nvp("AssetSettings", this->settings);

    return ss.str();
}
