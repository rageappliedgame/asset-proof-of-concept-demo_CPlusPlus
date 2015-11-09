#ifndef IDATAARCHIVE_H
#define IDATAARCHIVE_H


class IDataArchive
{
public:
    virtual ~IDataArchive() {}
    virtual bool Archive(const std::string& name) = 0;
};

#endif // IDATAARCHIVE_H
