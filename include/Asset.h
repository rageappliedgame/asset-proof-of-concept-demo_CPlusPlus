#ifndef ASSET_H
#define ASSET_H

#include <IAsset.h>
#include <BaseAsset.h>
#include <map>

namespace rage
{
class Asset : public BaseAsset
{
public:
    Asset();
    virtual ~Asset();
    void publicMethod(std::string message);
    void doArchive();
    std::vector<std::string> doList();
    std::string doLoad(std::string name);
    void doRemove();
    void doStore();

private:
    std::map<std::string, std::string> fileStorage;
    std::string fData = "Hello Storage World";
    std::string fId1 = "Hello1.txt";
    std::string fId2 = "Hello2.txt";
};
}

#endif // ASSET_H
