// file:	src\AssetSettings.cpp
//
// summary:	Implements the asset settings class
#include "AssetSettings.h"

using namespace rage;

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
