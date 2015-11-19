#include "Bridge.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace rage;

Bridge::Bridge()
{
    this->prefix = "";

    if (!fs::is_directory(storageDir))
    {
        fs::create_directory(storageDir);
    }

    if (!fs::is_directory(archiveDir))
    {
        fs::create_directory(archiveDir);

    }
}

Bridge::Bridge(const char *prefix)
{
    this->prefix = prefix;
}

std::string Bridge::getPrefix()
{
    return this->prefix;
}

void Bridge::setPrefix(const std::string& prefix)
{
    this->prefix = prefix;
}

void Bridge::doLog(const std::string& msg)
{
    cout << this->prefix << msg << endl;
}

std::vector<std::string> Bridge::Files()
{
    std::vector<std::string> files;
    fs::recursive_directory_iterator iter(storageDir), eod;

    BOOST_FOREACH(fs::path const& p, make_pair(iter, eod))
    {
        if (is_regular_file(p))
        {
            files.push_back(p.filename().string());
        }
    }

    return files;
}

bool Bridge::Delete(const std::string& name)
{
    if (Exists(name))
    {
        fs::path p(storageDir);
        p /= name;
        fs::remove(p);
        return true;
    }
    return false;
}

std::string Bridge::Load(const std::string& name)
{
    fs::path p(storageDir);
    p /= name;
    ifstream file(p.string().c_str());
    if (!file)
    {
        cout << "File not found." << endl;
        std::string();
    }
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

void Bridge::Save(const std::string& name, const std::string& data)
{
    fs::path p(storageDir);
    p /= name;
    std::fstream fs;
    fs.open(p.string().c_str(), std::fstream::out);
    fs << data;
    fs.close();
}

bool Bridge::Exists(const std::string& name)
{
    fs::path p(storageDir);
    p /= name;
    return fs::exists(p);
}

bool Bridge::Archive(const std::string& name)
{
    fs::path ps(storageDir);
    ps /= name;
    fs::path pa(archiveDir);
    pa /= name;
    if (fs::exists(ps))
    {
        if (fs::exists(pa))
        {
            fs::remove(pa);
        }

        fs::path pan(archiveDir);

        pt::time_facet *facet = new pt::time_facet("%Y-%m-%d [%H %M %S %f]");

        std::stringstream ss;
        ss.imbue(locale(ss.getloc(), facet));

        ss << pt::second_clock::local_time();

        std::string stampName = (boost::format("%1%-%2%%3%") % ps.stem().string() % ss.str() % ps.extension().string()).str();

        pan /= stampName;

        fs::rename(ps, pan);

        return true;
    }
    return false;
}

std::string Bridge::deriveAssetName(std::string clazz, std::string id)
{
    return (boost::format("%1%AppSettings.xml") % clazz).str();
}

bool Bridge::hasDefaultSettings(const std::string& clazz, const std::string& id)
{
    std::string fileName = deriveAssetName(clazz, id);
    return Exists(fileName);
}

std::string Bridge::loadDefaultSettings(const std::string& clazz, const std::string& id)
{
    std::string fileName = deriveAssetName(clazz, id);
    return Load(fileName);
}

void Bridge::saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData)
{
    std::string fileName = deriveAssetName(clazz, id);
    Save(fileName, fileData);
}
