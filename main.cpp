#include <AssetManager.h>
#include <Asset.h>
#include <Logger.h>
#include <DialogueAsset.h>
#include <PubSub.h>
#include <Bridge.h>
#include <RageVersionInfo.h>

#include <iostream>
#include "main.h"

using namespace std;
using namespace rage;

template <typename ...Args>
void MyEventHandler(string topic, Args... args)
{
	//va_list args;
	//va_start(args, topic);

	cout << "[PubSup]" << topic << " : " << args[0] << endl;
}

Asset* asset1 = nullptr;
Asset* asset2 = nullptr;
Logger* asset3 = nullptr;
Logger* asset4 = nullptr;
DialogueAsset* asset5 = nullptr;

Bridge* bridge1 = new Bridge();
Bridge* bridge2 = new Bridge();

static void test_01_Setup()
{
	AssetManager::getInstance().setBridge(bridge2);

	asset1 = new Asset();
	asset2 = new Asset();

	asset3 = new Logger();
	asset4 = new Logger();

	asset5 = new DialogueAsset();

	asset3->setBridge(bridge2);

	asset3->log("Asset1: " + asset1->getClassName() + ", " + asset1->getId());
	asset3->log("Asset2: " + asset2->getClassName() + ", " + asset2->getId());
	asset3->log("Asset3: " + asset3->getClassName() + ", " + asset3->getId());
	asset3->log("Asset4: " + asset4->getClassName() + ", " + asset4->getId());
	asset3->log("Asset5: " + asset5->getClassName() + ", " + asset5->getId());

	cout << endl;
}

void test_02_VersionAndDependenciesReport()
{
	cout << "Asset " << asset1->getClassName() << "v" << asset1->getVersion() << endl;

	std::map<std::string, std::string> dependencies = asset1->getDependencies();

	std::map<std::string, std::string>::const_iterator it = dependencies.begin();
	for (; it != dependencies.end(); ++it)
	{
		cout << "Depends on " << it->first << it->second << endl;
	}

	cout << endl;

	cout << AssetManager::getInstance().getVersionAndDependenciesReport() << endl;

	cout << "Version: v" << asset1->getVersion() << endl;

	cout << endl;
}

void test_03_AssetToAssetAndBridge()
{
	asset3->log("LogByLogger: " + asset3->getClassName() + ", " + asset3->getId());

	asset1->publicMethod("Hello World (console.log)");

	AssetManager::getInstance().setBridge(bridge1);

	asset1->publicMethod("Hello Different World (Game Engine Logging)");

	asset2->setBridge(bridge2);

	asset1->publicMethod("Hello Different World (Game Engine Logging)");

	cout << endl;
}

void test_04_DataStorageAndArchive_doList()
{
	std::vector<std::string> files = asset2->doList();
	for (std::vector<std::string>::const_iterator it = files.begin(); it != files.end(); ++it)
	{
		std::ostringstream oss;
		oss << *it << "=" << asset2->doLoad(*it);
		asset3->log(oss.str());
	}

	cout << endl;
}

void test_04_DataStorageAndArchive()
{
	asset3->log("----[assetmanager.bridge]-----");

	// Create Hello1.txt and Hello2.txt
	asset2->doStore();
	test_04_DataStorageAndArchive_doList();

	// Remove Hello1.txt
	asset2->doRemove();
	test_04_DataStorageAndArchive_doList();

	// Move Hello2.txt
	asset2->doArchive();

	asset3->log("----[default]-----");

	//! Reset/Remove Both Bridges.
	//
	asset2->setBridge(nullptr);

	AssetManager::getInstance().setBridge(nullptr);

	test_04_DataStorageAndArchive_doList();

	asset2->doStore();

	asset3->log("----[private.bridge]-----");

	asset2->setBridge(bridge2);

	asset2->doStore();

	test_04_DataStorageAndArchive_doList();

	asset3->log("----[default]-----");

	asset2->setBridge(nullptr);

	test_04_DataStorageAndArchive_doList();

	cout << endl;
}

template <typename ...Args>
void test_05_EventSubscription()
{
	//! Event Subscription.
	//
	// Define an event, subscribe to it and fire the event.
	//
	PubSub::getInstance().define("EventSystem.Msg");

	//! Using a method.
	//
#pragma message("VEG This method still fails.")
	/*
		int subId1 = PubSub::getInstance().subscribe("EventSystem.Msg", static_cast<std::function<void(string, Function lambda)>>(MyEventHandler));

		PubSub::getInstance().publish("EventSystem.Msg", "hello", "from", "demo.html!");

		PubSub::getInstance().unsubscribe(subId1);
	*/


	//! Using anonymous delegate.
	//XXX See https://stackoverflow.com/questions/23347287/parameter-pack-expansion-fails
	//    See https://stackoverflow.com/questions/25680461/variadic-template-pack-expansion
	//    See cout << typeid(variable).name() << endl;
	//int subId2 = PubSub::getInstance().subscribe("EventSystem.Msg", (string topic, Args... args)
	//{
#pragma message("VEG This method still fails.")
	//	va_list args1;
	//	va_start(args1, topic);

	//	cout << "[PubSub]." << topic << ": [" << args1[0] << " " << args1[1] << " " << args1[2] << "] (anonymous delegate)" << endl;
	//});

	//PubSub::getInstance().publish("EventSystem.Msg", 1, 2, 3.14159265);

	//PubSub::getInstance().unsubscribe(subId2);
	//}

	cout << endl;
}

void test_06_SanityChecks()
{

	cout << "Trying to re-register: " << AssetManager::getInstance().registerAssetInstance(*asset4, asset4->getClassName()) << endl;

	cout << endl;
}

void test_07_DialogueAsset()
{
	//! DialogAsset.
	//
	//TODO: load script from variable
	asset5->loadScript("me", "script.txt");

	// Interacting using branches
	//
	asset5->interact("me", "player", "banana");

	// Interacting using branches
	//
	asset5->interact("me", "player");
	asset5->interact("me", "player", 2); //Answer id 2

	asset5->interact("me", "player");
	asset5->interact("me", "player", 6); //Answer id 6

	asset5->interact("me", "player");

	cout << endl;
}

void test_08_Settings()
{
	//script.dialogueText.text = asset1.DefaultSettings.Count.ToString();//["NewKey0"].;


	//! Log Default Settings
	cout << asset1->settingsToXml<AssetSettings>() << endl;

	//! Log Default Settings
	asset2->setBridge(bridge1);
	cout << asset2->settingsToXml<AssetSettings>() << endl;

	//! Save App Default Settings if not present (and Settings is not null).
	asset2->saveDefaultSettings(false);

	//! Load App Default Settings if present (and Settings is not null).
	asset2->loadDefaultSettings();
	cout << asset2->settingsToXml<AssetSettings>() << endl;

	//! Try Saving an Asset with No Settings (null)
	if (asset3->hasSettings())
	{
		asset3->saveDefaultSettings(false);

		//XX cout << asset3->settingsToXml() << endl;
	}

	//! Save Runtime Settings
	asset2->saveSettings("runtime-settings.xml");

	//! Load Runtime Settings.
	asset1->setBridge(bridge1);
	asset1->loadSettings("runtime-settings.xml");

	cout << asset1->settingsToXml<AssetSettings>() << endl;
}

int main()
{
	cout << "DirectorySeparatorChar:" << PATH_SEPARATOR << endl;

	test_01_Setup();

	test_02_VersionAndDependenciesReport();

	test_03_AssetToAssetAndBridge();

	test_04_DataStorageAndArchive();

	test_05_EventSubscription();

	test_06_SanityChecks();

	test_07_DialogueAsset();

	test_08_Settings();

	std::cout << "Press Enter to continue...";
	std::cin.ignore();

	delete asset1;
	delete asset2;
	delete asset3;
	delete asset4;
	delete asset5;

	delete bridge1;
	delete bridge2;

	return EXIT_SUCCESS;
}
