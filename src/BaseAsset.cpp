#include <BaseAsset.h>

#include <AssetManager.h>

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

BaseAsset::BaseAsset(IBridge* bridge)
{
    this->bridge = bridge;
}

BaseAsset::~BaseAsset()
{
    AssetManager::getInstance()->unregisterAssetInstance(this->getId());
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


