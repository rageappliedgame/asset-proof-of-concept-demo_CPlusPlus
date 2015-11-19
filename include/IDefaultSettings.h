#ifndef IDEFAULTSETTINGS_H
#define IDEFAULTSETTINGS_H

#include <string>

namespace rage
{
class IDefaultSettings
{
public:
    virtual ~IDefaultSettings() {};
    virtual bool hasDefaultSettings(const std::string& clazz, const std::string& id) = 0;
    virtual std::string loadDefaultSettings(const std::string& clazz, const std::string& id) = 0;
    virtual void saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData) = 0;
};
}

#endif // IDEFAULTSETTINGS_H
