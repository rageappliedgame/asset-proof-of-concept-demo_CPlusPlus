#ifndef BASEASSET_H
#define BASEASSET_H

#include <IAsset.h>

namespace rage
{
    class BaseAsset : public IAsset
    {
        public:
            BaseAsset(std::string className);
            virtual ~BaseAsset();
            virtual std::string getClassName();
            virtual std::string getId();
        private:
            std::string className;
            std::string id;
    };
}

#endif // BASEASSET_H
