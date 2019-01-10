/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union’s Horizon
 * 2020 research and innovation programme under grant agreement No 644187.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <BaseAsset.h>

#include <AssetManager.h>
#include <IDefaultSettings.h>

#include <sstream>
#include <ostream>
#include <istream>
#include <fstream>

#include <cereal/archives/xml.hpp>

using namespace std;
using namespace rage;
using namespace cereal;

/// <summary>
/// Constructor.
/// </summary>
///
/// <param name="className"> Name of the class. </param>
BaseAsset::BaseAsset(string className)
{
	this->className = className;
	this->id = AssetManager::getInstance().registerAssetInstance(*this, this->getClassName());

	std::stringstream ss;
	ss << this->className << ".VersionAndDependencies.xml";
	string versionInfoXMLFile = ss.str();

	this->versionInfo = new RageVersionInfo();
	versionInfo->LoadVersionInfo(versionInfoXMLFile);
	this->bridge = nullptr;
}

/// <summary>
/// Destructor.
/// </summary>
BaseAsset::~BaseAsset()
{
	AssetManager::getInstance().unregisterAssetInstance(this->getId());
	
	delete settings;
	
	delete versionInfo;
}

/// <summary>
/// Gets the identifier.
/// </summary>
///
/// <returns>
/// The identifier.
/// </returns>
string BaseAsset::getId()
{
	return this->id;
}

/// <summary>
/// Gets class name.
/// </summary>
///
/// <returns>
/// The class name.
/// </returns>
string BaseAsset::getClassName()
{
	return this->className;
}

/// <summary>
/// Gets the bridge.
/// </summary>
///
/// <returns>
/// Null if it fails, else the bridge.
/// </returns>
IBridge* BaseAsset::getBridge()
{
	return this->bridge;
}

/// <summary>
/// Sets a bridge.
/// </summary>
///
/// <param name="bridge"> [in,out] If non-null, the bridge. </param>
void BaseAsset::setBridge(IBridge* bridge)
{
	this->bridge = bridge;
}

/// <summary>
/// Gets the dependencies.
/// </summary>
///
/// <returns>
/// The dependencies.
/// </returns>
std::map<std::string, std::string> BaseAsset::getDependencies()
{
	return this->versionInfo->getDependencies();
}

/// <summary>
/// Gets the maturity.
/// </summary>
///
/// <returns>
/// The maturity.
/// </returns>
std::string BaseAsset::getMaturity()
{
	return this->versionInfo->getMaturity();
}

/// <summary>
/// Gets the version.
/// </summary>
///
/// <returns>
/// The version.
/// </returns>
std::string BaseAsset::getVersion()
{
	return this->versionInfo->getVersion();
}

/// <summary>
/// Query if this object has settings.
/// </summary>
///
/// <returns>
/// True if settings, false if not.
/// </returns>
bool BaseAsset::hasSettings()
{
	return (this->settings != nullptr);
}

/// <summary>
/// Sets the settings.
/// </summary>
///
/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
void BaseAsset::setSettings(ISettings* settings)
{
	this->settings = settings;
}