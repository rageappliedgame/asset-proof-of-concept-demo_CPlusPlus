#include <Asset.h>

#include <AssetManager.h>
#include <Logger.h>

using namespace std;
using namespace rage;

Asset::Asset() : BaseAsset("Asset")
{
    //ctor
}

Asset::~Asset()
{
    //dtor
}

void Asset::publicMethod(string message)
{
    list<IAsset*> loggers = AssetManager::getInstance().findAssetsByClass("Logger");
    list<IAsset*>::const_iterator it;
    for(it=loggers.begin(); it != loggers.end(); ++it)
    {
        Logger* logger = dynamic_cast<Logger*>(*it);
        if (logger) {
            logger->log(message);
        }
    }
}
