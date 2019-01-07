#include <Logger.h>

#include <AssetManager.h>
#include <ILog.h>

#include <iostream>

using namespace std;
using namespace rage;

#pragma message ("VEG Logger.cpp is part of the demo app.")

Logger::Logger() : BaseAsset("Logger")
{
	//ctor
}

void Logger::log(string message)
{
	ILog* logger = getInterface<ILog>();
	if (logger != nullptr)
	{
		logger->Log(Severity::Information, message);
	}
	else
	{
		cout << message << endl;
	}
}
