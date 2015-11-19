#ifndef VERSIONSTRING_H
#define VERSIONSTRING_H

#include <string>

namespace rage
{
class VersionString
{
public:
    VersionString(){};
    explicit VersionString(const char *version);
    virtual ~VersionString(){};
    bool operator <= (const VersionString &other);
    VersionString& operator = (const VersionString &other);
private:
    int major, minor, revision, build, cnt;
};
}

#endif // VERSIONSTRING_H
