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
#ifndef IASSET_H
#define IASSET_H

#include <ISettings.h>
#include <IBridge.h>

#include <string>
#include <map>

namespace rage
{
class IAsset
{
public:
    virtual std::string getClassName() = 0;
    virtual std::string getId() = 0;
    virtual std::map<std::string, std::string> getDependencies() = 0;
    virtual std::string getMaturity() = 0;
    virtual std::string getVersion() = 0;
    virtual rage::IBridge* getBridge() = 0;
    virtual void setBridge(rage::IBridge* bridge) = 0;
};
}

#endif // IASSET_H
