#ifndef ILOGGER_H
#define ILOGGER_H

namespace rage
{
class ILogger
{
public:
    virtual std::string getPrefix() = 0;
    virtual void setPrefix(const std::string& prefix) = 0;
    virtual void doLog(const std::string& msg) = 0;
};
}

#endif // ILOGGER_H
