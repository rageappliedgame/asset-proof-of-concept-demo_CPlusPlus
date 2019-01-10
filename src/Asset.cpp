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
#include <Asset.h>

#include <AssetManager.h>
#include <Logger.h>

using namespace std;
using namespace rage;

#pragma message ("VEG Asset.cpp is part of the demo app.")

Asset::Asset() : BaseAsset("Asset")
{
	AssetSettings* settings = new AssetSettings();
	
	settings->setTestProperty(settings->getTestProperty() + " test");

	this->setSettings(settings);
}

Asset::~Asset()
{
	//
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
		for (map<string, string>::const_iterator it = this->fileStorage.begin(); it != this->fileStorage.end(); ++it)
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
		ds->Save(this->fId1, this->fData);
		ds->Save(this->fId2, this->fData);
	}
	else
	{
		this->fileStorage[this->fId1] = this->fData;
		this->fileStorage[this->fId2] = this->fData;
	}
}

void Asset::publicMethod(string message)
{
	list<IAsset*> loggers = AssetManager::getInstance().findAssetsByClass("Logger");
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
