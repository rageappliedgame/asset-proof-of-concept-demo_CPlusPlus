#ifndef IASSET_H
#define IASSET_H

#include <string>

namespace rage
{
    class IAsset
    {
        public:
            virtual std::string getClassName() = 0;
            virtual std::string getId() = 0;
    };
}

#endif // IASSET_H
