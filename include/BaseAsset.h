#ifndef BASEASSET_H
#define BASEASSET_H

#include <IAsset.h>
#include <RageVersionInfo.h>
#include <IDataArchive.h>
#include <IDataStorage.h>
#include <AssetManager.h>

namespace rage
{
class BaseAsset : public IAsset
{
public:
    BaseAsset(std::string className);
    BaseAsset(IBridge* bridge);
    virtual ~BaseAsset();
    virtual std::string getClassName();
    virtual std::string getId();
    virtual std::map<std::string, std::string> getDependencies();
    virtual std::string getMaturity();
    virtual std::string getVersion();
    virtual IBridge* getBridge();
    virtual void setBridge(IBridge* bridge);
protected:
    template<class Interface>
    Interface* getInterface()
    {
        if (this->bridge != nullptr && dynamic_cast<Interface*>(this->bridge))
        {
            return dynamic_cast<Interface*>(this->bridge);
        }
        else if (AssetManager::getInstance()->getBridge() != nullptr
                 && dynamic_cast<Interface*>(AssetManager::getInstance()->getBridge()))
        {
            return dynamic_cast<Interface*>(AssetManager::getInstance()->getBridge());
        }

        return nullptr;
    }
private:
    std::string className;
    std::string id;
    RageVersionInfo *versionInfo;
    IBridge *bridge;

};
}

#endif // BASEASSET_H
