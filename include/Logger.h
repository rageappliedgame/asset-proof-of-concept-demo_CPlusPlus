#ifndef LOGGER_H
#define LOGGER_H

#include <BaseAsset.h>

namespace rage
{
class Logger : public BaseAsset
{
public:
    Logger();
    virtual ~Logger();
    virtual void log(std::string message);
private:
    void doLog(const void* message);
};
}

#endif // LOGGER_H
