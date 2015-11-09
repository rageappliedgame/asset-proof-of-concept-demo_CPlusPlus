#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include <string>
#include <vector>

namespace rage
{
class IDataStorage
{
public:
    virtual ~IDataStorage() {}
    virtual bool Delete(const std::string& name) = 0;
    virtual bool Exists(const std::string& name) = 0;
    virtual std::vector<std::string> Files() = 0;
    virtual std::string Load(const std::string& name) = 0;
    virtual void Save(const std::string& name, const std::string& data) = 0;
};
}
#endif // IDATASTORAGE_H
