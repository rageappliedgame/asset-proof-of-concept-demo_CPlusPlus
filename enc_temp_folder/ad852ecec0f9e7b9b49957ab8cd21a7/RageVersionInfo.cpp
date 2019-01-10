/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union’s Horizon
 * 2020 research and innovation programme under grant agreement No 644187.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "RageVersionInfo.h"

#include <fstream>
#include <sstream>

using namespace std;
using namespace rage;

/// <summary>
/// Default constructor.
/// </summary>
RageVersionInfo::RageVersionInfo()
{
	this->soap = scopedSoap.GetSoap();
}

/// <summary>
/// Gets the identifier.
/// </summary>
///
/// <returns>
/// The identifier.
/// </returns>
std::string RageVersionInfo::getId()
{
	return v.id;
}

/// <summary>
/// Sets an identifier.
/// </summary>
///
/// <param name="id"> The identifier. </param>
void RageVersionInfo::setId(std::string id)
{
	v.id = id;
}

/// <summary>
/// Gets the major.
/// </summary>
///
/// <returns>
/// The major.
/// </returns>
int RageVersionInfo::getMajor()
{
	return static_cast<int>(v.major);
}

/// <summary>
/// Sets a major.
/// </summary>
///
/// <param name="major"> The major. </param>
void RageVersionInfo::setMajor(int major)
{
	//TODO
}

/// <summary>
/// Gets the minor.
/// </summary>
///
/// <returns>
/// The minor.
/// </returns>
int RageVersionInfo::getMinor()
{
	return static_cast<int>(v.minor);
}

/// <summary>
/// Sets a minor.
/// </summary>
///
/// <param name="minor"> The minor. </param>
void RageVersionInfo::setMinor(int minor)
{
	//TODO
}

/// <summary>
/// Gets the build.
/// </summary>
///
/// <returns>
/// The build.
/// </returns>
int RageVersionInfo::getBuild()
{
	return int(*v.build);
}

/// <summary>
/// Gets the revision.
/// </summary>
///
/// <returns>
/// The revision.
/// </returns>
int RageVersionInfo::getRevision()
{
	if (v.revision != nullptr)
	{
		return atoi(v.revision->c_str());
	}

	return 0;
}

/// <summary>
/// Gets the version.
/// </summary>
///
/// <returns>
/// The version.
/// </returns>
std::string RageVersionInfo::getVersion()
{
	std::stringstream ss;
	ss << this->getMajor()
		<< "." << this->getMinor()
		<< "." << this->getBuild();

	if (this->getRevision() != 0)
	{
		ss << "." << this->getRevision();
	}
	return ss.str();
}

/// <summary>
/// Sets a revision.
/// </summary>
///
/// <param name="revision"> The revision. </param>
void RageVersionInfo::setRevision(int revision)
{
	//TODO
}

/// <summary>
/// Gets the maturity.
/// </summary>
///
/// <returns>
/// The maturity.
/// </returns>
std::string RageVersionInfo::getMaturity()
{
	return v.maturity;
}

/// <summary>
/// Sets a maturity.
/// </summary>
///
/// <param name="maturity"> The maturity. </param>
void RageVersionInfo::setMaturity(std::string maturity)
{
	//TODO
}

/// <summary>
/// Gets the dependencies.
/// </summary>
///
/// <returns>
/// The dependencies.
/// </returns>
std::map<std::string, std::string> RageVersionInfo::getDependencies()
{
	std::map<std::string, std::string> result;
	if (v.dependencies.depends == nullptr)
	{
		return result;
	}
	std::vector<version_dependencies_depends>::const_iterator it = v.dependencies.depends->begin();
	for (; it != v.dependencies.depends->end(); ++it)
	{
		std::string minv = (*it).minVersion != nullptr ? (*(*it).minVersion) : "0.0";
		std::string maxv = (*it).maxVersion != nullptr ? (*(*it).maxVersion) : "*";
		std::string name = (*it).__item;

		std::stringstream tmp;
		tmp << minv << "." << maxv;

		std::string version = tmp.str();
		if (!result.insert(std::make_pair(name, version)).second)
		{
			// duplicate dependency, so do nothing
		}
	}

	return result;
}

/// <summary>
/// Sets the dependencies.
/// </summary>
///
/// <param name="dependencies"> The dependencies. </param>
void RageVersionInfo::setDependencies(std::map<std::string, std::string> dependencies)
{
	//TODO
}

/// <summary>
/// Sets a build.
/// </summary>
///
/// <param name="build"> The build. </param>
void RageVersionInfo::setBuild(int build)
{
	//TODO
}

/// <summary>
/// Loads version information.
/// </summary>
///
/// <exception cref="1"> Thrown when a 1 error condition occurs. </exception>
///
/// <param name="strXMLPath"> Full pathname of the XML file. </param>
void RageVersionInfo::LoadVersionInfo(const std::string& strXMLPath)
{
	ifstream fstreamIN(strXMLPath);
	this->soap.is = &fstreamIN;

	if (soap_read_version(&this->soap, &v) != SOAP_OK)
	{
		std::cout << "soap_read__version() failed" << std::endl;
		throw 1;
	}

	if (_setmode(_fileno(stdin), _O_TEXT) == -1)
	{
		std::cout << "_setmode() failed" << std::endl;
		throw 1;
	}
}

/// <summary>
/// Saves a version information.
/// </summary>
///
/// <exception cref="1"> Thrown when a 1 error condition occurs. </exception>
///
/// <param name="strXMLPath"> Full pathname of the XML file. </param>
///
/// <returns>
/// A std::string.
/// </returns>
std::string RageVersionInfo::SaveVersionInfo(const std::string& strXMLPath)
{
	soap_set_omode(&this->soap, SOAP_XML_INDENT);

	ofstream fstreamOUT(strXMLPath);
	this->soap.os = &fstreamOUT;

	if (soap_write_version(&this->soap, &this->v) != SOAP_OK)
	{
		std::cout << "soap_write_version() failed" << std::endl;
		throw 1;
	}
	return strXMLPath;
}
