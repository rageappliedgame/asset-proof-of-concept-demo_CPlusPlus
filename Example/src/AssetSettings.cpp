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

#include <AssetSettings.h>

using namespace rage;

#pragma message ("VEG AssetSettings.cpp is part of the demo app.")

/// <summary>
/// Gets test property.
/// </summary>
///
/// <returns>
/// The test property.
/// </returns>
std::string AssetSettings::getTestProperty()
{
	return this->testProperty;
}

/// <summary>
/// Sets test property.
/// </summary>
///
/// <param name="testProperty"> The test property. </param>
void AssetSettings::setTestProperty(std::string testProperty)
{
	this->testProperty = testProperty;
}

/// <summary>
/// Gets test list.
/// </summary>
///
/// <returns>
/// The test list.
/// </returns>
std::vector<std::string> AssetSettings::getTestList()
{
	return this->testList;
}

/// <summary>
/// Sets test list.
/// </summary>
///
/// <param name="testList"> List of tests. </param>
void AssetSettings::setTestList(std::vector<std::string> testList)
{
	this->testList = testList;
}

/// <summary>
/// Query if this object is test read only.
/// </summary>
///
/// <returns>
/// True if test read only, false if not.
/// </returns>
bool AssetSettings::isTestReadOnly()
{
	return this->testReadOnly;
}
