#include "VersionString.h"

#include <iostream>
using namespace std;

VersionString::VersionString(const char *version)
{
    major = 999, minor = 999, revision = 999, build = 999;

    cnt = sscanf(version, "%d.%d.%d.%d", &major, &minor, &build, &revision);

    if (cnt > 0)
    {
        if (cnt < 2) minor = 0;
        if (cnt < 3) build = 0;
        if (cnt < 4) revision = 0;
    }
}

VersionString::~VersionString()
{
    //dtor
}

bool VersionString::operator <= (const VersionString &other)
{
    if (major < other.major)
    {
        return true;
    }
    else if (major == other.major)
    {
        if (minor < other.minor)
        {
            return true;
        }
        else if (minor == other.minor)
        {
            if (build < other.build)
            {
                return true;
            }
            else if (build == other.build)
            {
                if (revision <= other.revision)
                    return true;
            }
        }
    }


    return false;
}

VersionString& VersionString::operator = (const VersionString &other)
{
    if (this != &other)
    {
            major = other.major;
            minor = other.minor;
            build = other.build;
            revision = other.revision;
    }

    return *this;
}
