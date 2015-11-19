#ifndef BASESETTINGS_H
#define BASESETTINGS_H

#include <ISettings.h>

#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>

namespace rage
{
class BaseSettings : public ISettings
{
    friend boost::serialization::access;
    public:
        BaseSettings(){};
        virtual ~BaseSettings(){};
    protected:
        template <typename Archive>
        void serialize(Archive& ar, const unsigned int version){
            ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ISettings);
        }
};
}

#endif // BASESETTINGS_H
