#ifndef ASSETSETTINGS_H
#define ASSETSETTINGS_H

#include <BaseSettings.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/export.hpp>

#include <string>
#include <vector>

namespace rage
{
class AssetSettings : public BaseSettings
{
    friend class boost::serialization::access;

public:
    AssetSettings(){};
    virtual ~AssetSettings(){};
    std::string getTestProperty();
    void setTestProperty(std::string testProperty);
    std::vector<std::string> getTestList();
    void setTestList(std::vector<std::string> testList);
    bool isTestReadOnly();
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(BaseSettings);
        ar & BOOST_SERIALIZATION_NVP(testProperty);
        ar & BOOST_SERIALIZATION_NVP(testReadOnly);
        ar & BOOST_SERIALIZATION_NVP(testList);
    }
private:
    std::string testProperty = "Hello Default World";
    bool testReadOnly = true;
    std::vector<std::string> testList = {"Hello", "List", "World"};

};
}

// Before calling BOOST_CLASS_EXPORT_*
// should include the archives which you want to use.
// The makro then adds specific serialize-functions for the headers.
BOOST_CLASS_EXPORT_KEY(rage::AssetSettings);

#endif // ASSETSETTINGS_H
