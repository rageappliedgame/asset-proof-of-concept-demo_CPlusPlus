#include <AssetManager.h>
#include <Asset.h>
#include <Logger.h>
#include <DialogueAsset.h>
#include <PubSub.h>

#include <iostream>

using namespace std;
using namespace rage;

class MyLogger
{
    public:
        void log(const void* message)
        {
            cout << "Custom Logging: " << (char*)message << endl;
        }
};

void foo(const char* message)
{
    cout << "Foo: " << message << endl;
}

int main()
{
    Asset* asset1 = new Asset();
    Asset* asset2 = new Asset();
    Logger* asset3 = new Logger();
    Logger* asset4 = new Logger();
    DialogueAsset* asset5 = new DialogueAsset();

    asset3->log("Asset1: " + asset1->getClassName() + ", " + asset1->getId());
    asset3->log("Asset2: " + asset2->getClassName() + ", " + asset2->getId());
    asset3->log("Asset3: " + asset3->getClassName() + ", " + asset3->getId());
    asset3->log("Asset4: " + asset4->getClassName() + ", " + asset4->getId());
    asset3->log("Asset5: " + asset5->getClassName() + ", " + asset5->getId());

    asset3->log("LogByLogger: " + asset3->getClassName() + ", " + asset3->getId());

    asset1->publicMethod("Hello World (console.log)");

    MyLogger myLogger;
    asset4->OnLog += new LogDelegate<MyLogger>(&myLogger, &MyLogger::log);

    PubSub::getInstance().define("EventSystem.Msg");

    PubSub::getInstance().subscribe("EventSystem.Msg", [asset4](char* message){asset4->log(message);});
    PubSub::getInstance().subscribe("EventSystem.Msg", static_cast<std::function<void(char*)>>(foo));

    PubSub::getInstance().publish("EventSystem.Msg", "Hellow, World!");

    string assetId = AssetManager::getInstance().registerAssetInstance(*asset4, asset4->getClassName());
    cout << assetId << endl;

    asset5->loadScript("me", "script.txt");

    asset5->interact("me", "player", "banana");

    asset5->interact("me", "player");
    asset5->interact("me", "player", 2); //Answer id 2

    asset5->interact("me", "player");
    asset5->interact("me", "player", 6); //Answer id 6

    asset5->interact("me", "player");


    return 0;
}
