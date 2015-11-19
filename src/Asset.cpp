#include <Asset.h>

#include <AssetManager.h>
#include <Logger.h>

using namespace std;
using namespace rage;

Asset::Asset() : BaseAsset("Asset")
{
    this->settings = new AssetSettings();
    this->settings->setTestProperty(this->settings->getTestProperty() + " test");
    BaseAsset::setSettings(this->settings);
}

Asset::~Asset()
{
    delete settings;
}

void Asset::setSettings(ISettings *settings)
{
    this->settings = dynamic_cast<AssetSettings*>(settings);
}

void Asset::doArchive()
{
    IDataArchive* ds = getInterface<IDataArchive>();
    if (ds != nullptr)
    {
        ds->Archive(this->fId2);
    }
    else
    {
        map<std::string, std::string>::const_iterator itr = this->fileStorage.find(this->fId2);
        if (itr != this->fileStorage.end())
        {
            this->fileStorage.erase(itr);
        }
    }
}

std::vector<std::string> Asset::doList()
{
    IDataStorage* ds = getInterface<IDataStorage>();
    if (ds != nullptr)
    {
        return ds->Files();
    }
    else
    {
        std::vector<std::string> result;
        for(map<string,string>::const_iterator it = this->fileStorage.begin(); it != this->fileStorage.end(); ++it)
        {
            result.push_back(it->first);
        }
        return result;
    }
}

std::string Asset::doLoad(std::string name)
{
    IDataStorage* ds = getInterface<IDataStorage>();
    if (ds != nullptr)
    {
        return ds->Load(name);
    }
    else
    {
        for (map<std::string, std::string>::const_iterator itr = this->fileStorage.begin(); itr != this->fileStorage.end(); ++itr)
        {
            if (name == itr->first)
            {
                return itr->second;
            }
        }
    }

    return nullptr;
}

void Asset::doRemove()
{
    IDataStorage* ds = getInterface<IDataStorage>();
    if (ds != nullptr)
    {
        ds->Delete(fId1);
    }
    else
    {
        map<std::string, std::string>::const_iterator itr = this->fileStorage.find(fId1);
        if (itr != this->fileStorage.end())
        {
            this->fileStorage.erase(itr);
        }
    }
}

void Asset::doStore()
{
    IDataStorage* ds = getInterface<IDataStorage>();
    if (ds != nullptr)
    {
        ds->Save(this->fId1,this->fData);
        ds->Save(this->fId2,this->fData);
    }
    else
    {
        this->fileStorage[this->fId1] = this->fData;
        this->fileStorage[this->fId2] = this->fData;
    }
}

void Asset::publicMethod(string message)
{
    list<IAsset*> loggers = AssetManager::getInstance()->findAssetsByClass("Logger");
    list<IAsset*>::const_iterator it;
    for (it = loggers.begin(); it != loggers.end(); ++it)
    {
        Logger* logger = dynamic_cast<Logger*>(*it);
        if (logger)
        {
            logger->log(logger->getId() + " - " + message);
        }
    }
}
