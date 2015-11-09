#ifndef RAGEVERSIONINFO_H
#define RAGEVERSIONINFO_H

#include <string>
#include <map>
#include <boost/format.hpp>
#include "vadH.h"

namespace rage
{
// RAII support
class CScopedSoap
{
// gSOAP runtime context
    struct soap m_soap;

public:
    CScopedSoap()
    {
        // initialize runtime context
        soap_init(&m_soap);

        // Set input mode
        soap_imode(&m_soap, SOAP_ENC_XML);

        // start new (de)serialization phase
        soap_begin(&m_soap);
    }

    ~CScopedSoap()
    {
        // remove deserialized class instances (C++ objects)
        soap_destroy(&m_soap);

        // clean up and remove deserialized data
        soap_end(&m_soap);

        // detach context (last use and no longer in scope)
        soap_done(&m_soap);
    }

    struct soap& GetSoap()
    {
        return m_soap;
    }
};

class RageVersionInfo
{
public:
    RageVersionInfo();
    virtual ~RageVersionInfo();
    std::string getId();
    void setId(std::string id);
    int getMajor();
    void setMajor(int major);
    int getMinor();
    void setMinor(int minor);
    int getBuild();
    int getRevision();
    void setRevision(int revision);
    std::string getMaturity();
    void setMaturity(std::string maturity);
    std::map<std::string, std::string> getDependencies();
    void setDependencies(std::map<std::string,std::string> dependencies);
    void setBuild(int build);
    std::string getVersion();
    //void LoadVersionInfo(struct soap& soap, version& v, const std::string& strXMLPath);
    void LoadVersionInfo(const std::string& strXMLPath);
    //std::string SaveVersionInfo(struct soap& soap, version& v, const std::string& strXMLPath);
    std::string SaveVersionInfo(const std::string& strXMLPath);
protected:
private:
    struct soap soap;
    version v;
    CScopedSoap scopedSoap;
};

}
#endif // RAGEVERSIONINFO_H
