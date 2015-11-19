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
    explicit BaseAsset(std::string className);
    virtual ~BaseAsset();
    std::string getClassName();
    std::string getId();
    std::map<std::string, std::string> getDependencies();
    std::string getMaturity();
    std::string getVersion();
    bool hasSettings();
    ISettings* getSettings();
    virtual void setSettings(ISettings* settings);
    bool loadDefaultSettings();
    bool loadSettings(std::string fileName);
    bool saveDefaultSettings(bool force);
    bool saveSettings(std::string fileName);
    ISettings* settingsFromXml(std::string xml);
    std::string settingsToXml();
    IBridge* getBridge();
    void setBridge(IBridge* bridge);
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
    RageVersionInfo *versionInfo = nullptr;
    IBridge *bridge = nullptr;
    ISettings* settings = nullptr;

};
}

#endif // BASEASSET_H
