#include <BaseAsset.h>

#include <AssetManager.h>

using namespace std;
using namespace rage;

BaseAsset::BaseAsset(string className)
{
    this->className = className;
    this->id = AssetManager::getInstance().registerAssetInstance(*this, this->getClassName());
}

BaseAsset::~BaseAsset()
{
    AssetManager::getInstance().unregisterAssetInstance(this->getId());
}

string BaseAsset::getId()
{
    return this->id;
}

string BaseAsset::getClassName()
{
    return this->className;
}
