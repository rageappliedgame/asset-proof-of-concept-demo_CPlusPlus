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
            static AssetManager& getInstance();
            std::string registerAssetInstance(IAsset& asset, std::string clazz);
            bool unregisterAssetInstance(std::string id);
            IAsset* findAssetById(std::string id);
            IAsset* findAssetByClass(std::string className);
            std::list<IAsset*> findAssetsByClass(std::string className);
        private:
            AssetManager(): idGenerator(0){};
            ~AssetManager(){delete &assets;};
            AssetManager(const AssetManager&);
            std::map<std::string, IAsset*> assets;
            int idGenerator;
    };
}

#endif // ASSETMANAGER_H
