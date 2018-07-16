#include "AssetSettings.h"

using namespace rage;

std::string AssetSettings::getTestProperty()
{
	return this->testProperty;
}

void AssetSettings::setTestProperty(std::string testProperty)
{
	this->testProperty = testProperty;
}

std::vector<std::string> AssetSettings::getTestList()
{
	return this->testList;
}

void AssetSettings::setTestList(std::vector<std::string> testList)
{
	this->testList = testList;
}

bool AssetSettings::isTestReadOnly()
{
	return this->testReadOnly;
}
