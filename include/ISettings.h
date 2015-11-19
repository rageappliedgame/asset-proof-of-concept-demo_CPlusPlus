#ifndef ISETTINGS_H
#define ISETTINGS_H

#include <boost/serialization/serialization.hpp>

namespace rage
{
class ISettings
{
    friend class boost::serialization::access;
public:
    virtual ~ISettings() {}
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {}
};

}

#endif // ISETTINGS_H
