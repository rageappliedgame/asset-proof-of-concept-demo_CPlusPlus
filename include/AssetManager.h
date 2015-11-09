#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <IAsset.h>

#include <string>
#include <map>
#include <list>

namespace rage
{
class AssetManager
{
public:
    // This newer C++11 implementation has issues with older VS versions (shows on exit).
    // http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
    //
    //static AssetManager& getInstance();
    //
    static AssetManager* getInstance();
    std::string registerAssetInstance(IAsset& asset, std::string clazz);
    bool unregisterAssetInstance(std::string id);
    IAsset* findAssetById(std::string id);
    IAsset* findAssetByClass(std::string className);
    std::list<IAsset*> findAssetsByClass(std::string className);
    IBridge* getBridge();
    void setBridge(IBridge* bridge);
    std::string getVersionAndDependenciesReport();
private:
    static AssetManager *instance;
    AssetManager() : idGenerator(0)
    {
        //
    };
    ~AssetManager()
    {
        delete &assets;
    };
    AssetManager(const AssetManager&);
    std::map<std::string, IAsset*> assets;
    int idGenerator;
    IBridge* bridge;
};
}

#endif // ASSETMANAGER_H
