#ifndef ASSET_H
#define ASSET_H

#include <IAsset.h>
#include <BaseAsset.h>

namespace rage
{
    class Asset : public BaseAsset
    {
        public:
            Asset();
            virtual ~Asset();
            void publicMethod(std::string message);

    };
}

#endif // ASSET_H
