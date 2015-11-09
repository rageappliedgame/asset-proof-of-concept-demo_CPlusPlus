#include "RageVersionInfo.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace rage;

RageVersionInfo::RageVersionInfo()
{
    //ctor
    this->soap = scopedSoap.GetSoap();
}

RageVersionInfo::~RageVersionInfo()
{
    //dtor
}

std::string RageVersionInfo::getId()
{
    return v.id;
}

void RageVersionInfo::setId(std::string id)
{
    v.id = id;
}

int RageVersionInfo::getMajor()
{
    return static_cast<int>(v.major);
}

void RageVersionInfo::setMajor(int major)
{
    //TODO
    // v.major = std::to_string(major);
}

int RageVersionInfo::getMinor()
{
    return static_cast<int>(v.minor);
}

void RageVersionInfo::setMinor(int minor)
{
    //TODO

}

int RageVersionInfo::getBuild()
{
    return int(*v.build);
}

int RageVersionInfo::getRevision()
{
    if (v.revision != nullptr)
    {
        return atoi(v.revision->c_str());
    }

    return 0;
}

std::string RageVersionInfo::getVersion()
{
    //TODO:
    std::stringstream ss;
    ss  << this->getMajor()
        << "." << this->getMinor()
        << "." << this->getBuild();

    if (this->getRevision() != 0)
    {
        ss << "." << this->getRevision();
    }
    return ss.str();
}

void RageVersionInfo::setRevision(int revision)
{
    //TODO
}

std::string RageVersionInfo::getMaturity()
{
    return v.maturity;
}

void RageVersionInfo::setMaturity(std::string maturity)
{
    //TODO
}

std::map<std::string, std::string> RageVersionInfo::getDependencies()
{
    std::map<std::string, std::string> result;
    if (v.dependencies.depends == nullptr)
    {
        return result;
    }
    std::vector<version_dependencies_depends>::const_iterator it = v.dependencies.depends->begin();
    for(; it != v.dependencies.depends->end(); it++)
    {
        std::string minv = (*it).minVersion != nullptr ? (*(*it).minVersion) : "0.0";
        std::string maxv = (*it).maxVersion != nullptr ? (*(*it).maxVersion) : "*";
        std::string name = (*it).__item;
        std::string version = (boost::format("%1%-%2%") % minv % maxv).str();
        if ( !result.insert(std::make_pair(name, version)).second )
        {
            // duplicate dependency, so do nothing
        }
    }

    return result;
}

void RageVersionInfo::setDependencies(std::map<std::string,std::string> dependencies)
{
    //TODO
}

void RageVersionInfo::setBuild(int build)
{
    //TODO
}

void RageVersionInfo::LoadVersionInfo(const std::string& strXMLPath)
{
    ifstream fstreamIN(strXMLPath);
    this->soap.is = &fstreamIN;

    if(soap_read_version(&this->soap, &v) != SOAP_OK)
    {
        std::cout << "soap_read__version() failed" << std::endl;
        throw 1;
    }

    if(_setmode(_fileno(stdin), _O_TEXT) == -1)
    {
        std::cout << "_setmode() failed" << std::endl;
        throw 1;
    }
}

std::string RageVersionInfo::SaveVersionInfo(const std::string& strXMLPath)
{
    soap_set_omode(&this->soap, SOAP_XML_INDENT);

    ofstream fstreamOUT(strXMLPath);
    this->soap.os = &fstreamOUT;

    if(soap_write_version(&this->soap, &this->v) != SOAP_OK)
    {
        std::cout << "soap_write_version() failed" << std::endl;
        throw 1;
    }
    return strXMLPath;
}
