#ifndef VERSIONSTRING_H
#define VERSIONSTRING_H

#include <string>

class VersionString
{
    public:
        VersionString(){};
        VersionString(const char *version);
        //VersionString(const VersionString& other) :
         //   major(other.major), minor(other.minor), revision(other.revision),build(other.build),cnt(other.cnt){};
        virtual ~VersionString();
        bool operator <= (const VersionString &other);
        VersionString& operator = (const VersionString &other);
    private:
        int major, minor, revision, build, cnt;
};

#endif // VERSIONSTRING_H
