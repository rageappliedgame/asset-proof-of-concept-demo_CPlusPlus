#include <Logger.h>

#include <AssetManager.h>
#include <ILogger.h>

#include <iostream>

using namespace std;
using namespace rage;

Logger::Logger() : BaseAsset("Logger")
{
    //ctor
}

Logger::~Logger()
{
    //dtor
}

void Logger::log(string message)
{
    ILogger* logger = getInterface<ILogger>();
    if (logger != nullptr)
    {
        logger->doLog(message);
    }
    else
    {
        cout << message << endl;
    }
}
