#ifndef IDATAARCHIVE_H
#define IDATAARCHIVE_H

namespace rage
{
class IDataArchive
{
public:
    virtual ~IDataArchive() {}
    virtual bool Archive(const std::string& name) = 0;
};
}

#endif // IDATAARCHIVE_H
