#ifndef BRIDGE_H
#define BRIDGE_H

#include <IDataStorage.h>
#include <IDataArchive.h>
#include <ILogger.h>
#include <IBridge.h>

#include <string>
#include <sstream>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/foreach.hpp>

using namespace std;

namespace fs = boost::filesystem;
namespace pt = boost::posix_time;

namespace rage
{
const char PATH_SEPARATOR =
#if defined(_WIN32) || defined(__CYGWIN__)
    '\\';
#else
    '/';
#endif
class Bridge : public IBridge, public IDataStorage, public ILogger, public IDataArchive
{
public:
    Bridge();
    Bridge(const char *prefix);
    virtual ~Bridge();
    bool Delete(const std::string& name);
    bool Exists(const std::string& name);
    std::vector<std::string> Files();
    std::string Load(const std::string& name);
    void Save(const std::string& name, const std::string& data);
    std::string getPrefix();
    void setPrefix(const std::string& prefix);
    void doLog(const std::string& msg);
    bool Archive(const std::string& name);
protected:
private:
    std::string prefix;
    fs::path storageDir {(boost::format(".%1%%2%") % PATH_SEPARATOR % "DataStorage").str()};
    fs::path archiveDir {(boost::format(".%1%%2%") % PATH_SEPARATOR % "ArchiveStorage").str()};
};
}
#endif // BRIDGE_H
