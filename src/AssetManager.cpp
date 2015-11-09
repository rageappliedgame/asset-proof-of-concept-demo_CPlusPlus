#include <AssetManager.h>

#include <sstream>
#include <mutex>
#include <iostream>
#include <iomanip>
#include "boost/format.hpp"

using namespace std;
using namespace rage;

AssetManager* AssetManager::instance = NULL;

// http://preshing.com/20130930/double-checked-locking-is-fixed-in-cpp11/
// this newer C++11 implementation has issues with older VS versions (show on exit).
// replaced by a thread-safe DCLP (Double Checked Locking Pattern).
//
//AssetManager& AssetManager::getInstance()
//{
//	static AssetManager instance;
//	return instance;
//}

std::mutex mtx1;
std::mutex mtx2;

AssetManager* AssetManager::getInstance()
{
    // See http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
    // And http://www.codeproject.com/Articles/96942/Singleton-Design-Pattern-and-Thread-Safety
    // And http://jinaldesai.net/all-about-singleton-pattern/
    //
    // Note the use of a AssetManager* needs all statements using AssetManager.getInstance().aMethod()
    // to be changed into AssetManager.getInstance()->aMethod()
    //
    // Problem with a lot of implementations is that the outer instance==NULL test fails when the object is
    // being partially created, thus returning a partially initialized singleton instance.
    //
    AssetManager* tmp = instance;

    if (instance == NULL)	// insert memory barrier #1
    {
        //first synchronization lock, only one thread will enter the block
        mtx1.lock();
        {
            tmp = instance;

            if (tmp == NULL) // insert memory barrier #2
            {
                //second level synchronization lock, only one thread will enter the block
                mtx2.lock();
                {
                    tmp = new AssetManager();
                }
                mtx2.unlock();

                instance = tmp;
            }
        }
        mtx1.unlock();
    }

    return instance;
}

string AssetManager::registerAssetInstance(IAsset& asset, string clazz)
{
    for (map<string, IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if (itr->second == &asset)
        {
            return itr->first;
        }
    }

    stringstream s;
    s << clazz << "_" << idGenerator++;
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
    for (map<string, IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if (className == itr->second->getClassName())
        {
            return itr->second;
        }
    }

    return NULL;
}

list<IAsset*> AssetManager::findAssetsByClass(string className)
{
    list<IAsset*> found;
    for (map<string, IAsset*>::iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {
        if (className == itr->second->getClassName())
        {
            found.push_back(itr->second);
        }
    }

    return found;
}

IBridge* AssetManager::getBridge()
{
    return this->bridge;
}

void AssetManager::setBridge(IBridge* bridge)
{
    this->bridge = bridge;
}

std::string AssetManager::getVersionAndDependenciesReport()
{
    std::stringstream report;

    for (map<string, IAsset*>::const_iterator itr = assets.begin(); itr != assets.end(); ++itr)
    {

        report << boost::format("%-s v%-s") % itr->second->getClassName() % itr->second->getVersion();

        int cnt = 0;

        std::map<std::string, std::string> dependencies = itr->second->getDependencies();
        std::map<std::string, std::string>::const_iterator dit = dependencies.begin();
        for(; dit != dependencies.end(); dit++)
        {
            report << boost::format("|%-s v%-s") % dit->first % dit->second;
            cnt++;
        }


        if (cnt == 0)
        {
            report << boost::format("|%-s") % "No dependencies";
        }

        report << endl;
    }

    return report.str();
}
