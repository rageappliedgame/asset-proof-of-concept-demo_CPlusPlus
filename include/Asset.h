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
#pragma once

#ifndef ASSET_H
#define ASSET_H

#include <IAsset.h>
#include <BaseAsset.h>

#include <AssetSettings.h>

#include <map>

#pragma message ("VEG Asset.h is part of the demo app.")

namespace rage
{
	class Asset : public BaseAsset
	{
	public:
		Asset();
		virtual ~Asset();
		void publicMethod(std::string message);
		void doArchive();
		std::vector<std::string> doList();
		std::string doLoad(std::string name);
		void doRemove();
		void doStore();
	private:
		std::map<std::string, std::string> fileStorage;
		std::string fData = "Hello Storage World";
		std::string fId1 = "Hello1.txt";
		std::string fId2 = "Hello2.txt";
	};
}

#endif // ASSET_H
