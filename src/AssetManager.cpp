// file:	src\AssetManager.cpp
//
// summary:	Implements the asset manager class
#include <AssetManager.h>

#include <VersionString.h>

#include <sstream>
#include <iostream>
#include <iomanip>

#ifdef USE_CALL_ONCE
#include <mutex>
#endif

using namespace std;
using namespace rage;

#ifdef USE_CALL_ONCE
std::unique_ptr<AssetManager> AssetManager::m_instance;
std::once_flag AssetManager::m_onceFlag;
#endif

/// <summary>
/// Gets the instance.
/// </summary>
///
/// <returns>
/// The instance.
/// </returns>
AssetManager& AssetManager::getInstance()
{
#ifdef USE_CALL_ONCE
	std::call_once(m_onceFlag,
		[] {
		m_instance.reset(new AssetManager);
	});
	return *m_instance.get();
#else
	static AssetManager instance;
	return instance;
#endif
}

/// <summary>
/// Registers the asset instance.
/// </summary>
///
/// <param name="asset"> [in,out] The asset. </param>
/// <param name="clazz"> The clazz. </param>
///
/// <returns>
/// A string.
/// </returns>
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

/// <summary>
/// Unregisters the asset instance described by ID.
/// </summary>
///
/// <param name="id"> The identifier. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
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

/// <summary>
/// Searches for the first asset by identifier.
/// </summary>
///
/// <param name="id"> The identifier. </param>
///
/// <returns>
/// Null if it fails, else the found asset by identifier.
/// </returns>
IAsset* AssetManager::findAssetById(string id)
{
	map<string, IAsset *>::iterator itr = assets.find(id);
	if (itr != assets.end())
	{
		return itr->second;
	}

	return NULL;
}

/// <summary>
/// Searches for the first asset by class.
/// </summary>
///
/// <param name="className"> Name of the class. </param>
///
/// <returns>
/// Null if it fails, else the found asset by class.
/// </returns>
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

/// <summary>
/// Searches for the first assets by class.
/// </summary>
///
/// <param name="className"> Name of the class. </param>
///
/// <returns>
/// Null if it fails, else the found assets by class.
/// </returns>
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

/// <summary>
/// Gets the bridge.
/// </summary>
///
/// <returns>
/// Null if it fails, else the bridge.
/// </returns>
IBridge* AssetManager::getBridge()
{
	return this->bridge;
}

/// <summary>
/// Sets a bridge.
/// </summary>
///
/// <param name="bridge"> [in,out] If non-null, the bridge. </param>
void AssetManager::setBridge(IBridge* bridge)
{
	this->bridge = bridge;
}

/// <summary>
/// Gets version and dependencies report.
/// </summary>
///
/// <returns>
/// The version and dependencies report.
/// </returns>
std::string AssetManager::getVersionAndDependenciesReport()
{
	std::stringstream report;

	for (map<string, IAsset*>::const_iterator itr = assets.begin(); itr != assets.end(); ++itr)
	{

		report << itr->second->getClassName() << " v" << itr->second->getVersion();

		int cnt = 0;

		std::map<std::string, std::string> dependencies = itr->second->getDependencies();
		std::map<std::string, std::string>::const_iterator dit = dependencies.begin();
		for (; dit != dependencies.end(); ++dit)
		{
			char lvs[20], hvs[20], *p_lvs = nullptr, *p_hvs = nullptr;
			int vcnt = sscanf(dit->second.c_str(), "%[^-]-%s", lvs, hvs);
			if (vcnt == 1)
			{
				p_hvs = lvs;
				p_lvs = lvs;
			}
			else if (vcnt == 2)
			{
				p_lvs = lvs;
				p_hvs = hvs;
			}

			VersionString low(p_lvs);
			VersionString hi(p_hvs);

			bool found = false;

			list<IAsset*> dep = AssetManager::getInstance().findAssetsByClass(dit->first);
			for (std::list<IAsset*>::const_iterator iterator = dep.begin(), end = dep.end(); iterator != end; ++iterator)
			{
				VersionString vdep(((*iterator)->getVersion()).c_str());
				if (low <= vdep && vdep <= hi)
				{
					found = true;
					break;
				}
			}

			report << "|" << dit->first << " v" << dit->second << " [" << (found ? "resolved" : "missing") << "]";

			cnt++;
		}

		if (cnt == 0)
		{
			report << "|" << "No dependencies";
		}

		report << endl;

	}

	return report.str();
}
