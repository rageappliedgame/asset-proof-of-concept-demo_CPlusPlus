#include <AssetManager.h>

#include <sstream>

using namespace std;
using namespace rage;

AssetManager& AssetManager::getInstance()
{
    static AssetManager instance;
    return instance;
}

string AssetManager::registerAssetInstance(IAsset& asset, string clazz)
{
    for(map<string,IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if (itr->second == &asset)
        {
            return itr->first;
        }
    }

    stringstream s;
    s << clazz << "_" << ++idGenerator;
    string id = s.str();
    assets[id] = &asset;

    return id;
}

bool AssetManager::unregisterAssetInstance(string id)
{
    map<string, IAsset *>::iterator itr = assets.find(id);
    if (itr != assets.end())
    {
        assets.erase(itr);
        return true;
    }

    return false;
}

IAsset* AssetManager::findAssetById(string id)
{
    map<string, IAsset *>::iterator itr = assets.find(id);
    if (itr != assets.end())
    {
        return itr->second;
    }

    return NULL;
}

IAsset* AssetManager::findAssetByClass(string className)
{
    for(map<string,IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if(className == itr->second->getClassName())
        {
            return itr->second;
        }
    }

    return NULL;
 }

 list<IAsset*> AssetManager::findAssetsByClass(string className)
 {
    list<IAsset*> found;
    for(map<string,IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if(className == itr->second->getClassName())
        {
            found.push_back(itr->second);
        }
    }

    return found;
 }
