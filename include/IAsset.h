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
