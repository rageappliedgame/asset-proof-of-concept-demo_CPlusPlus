#include <Logger.h>

#include <AssetManager.h>

#include <iostream>

using namespace std;
using namespace rage;

Logger::Logger() : BaseAsset("Logger")
{
    this->OnLog += new LogDelegate<Logger>(this, &Logger::doLog);
}

void Logger::log(string message)
{
   OnLog(message.c_str());
}

Logger::~Logger()
{
    //dtor
}

void Logger::doLog(const void* message)
{
    if (OnLog.getInvocationList().size() == 1)
    {
        cout << "[" << this->getId() << "] " << (char*)message << endl;
    }
}
