// file:	include\RageVersionInfo.h
//
// summary:	Declares the rage version information class
#ifndef RAGEVERSIONINFO_H
#define RAGEVERSIONINFO_H

#include <string>
#include <map>

#include "vadH.h"

// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// RAII support (is used for loading/saving 'version' from/to xml).
	/// </summary>
	class CScopedSoap
	{
		/// <summary>
		/// gSOAP runtime context.
		/// </summary>
		struct soap m_soap;

	public:

		/// <summary>
		/// Default constructor.
		/// </summary>
		CScopedSoap()
		{
			/// <summary>
			/// initialize runtime context.
			/// </summary>
			soap_init(&m_soap);

			/// <summary>
			/// Set input mode.
			/// </summary>
			soap_imode(&m_soap, SOAP_ENC_XML);

			/// <summary>
			/// start new (de)serialization phase.
			/// </summary>
			soap_begin(&m_soap);
		}

		/// <summary>
		/// Destructor.
		/// </summary>
		~CScopedSoap()
		{
			/// <summary>
			/// remove deserialized class instances (C++ objects)
			/// </summary>
			soap_destroy(&m_soap);

			/// <summary>
			/// clean up and remove deserialized data.
			/// </summary>
			soap_end(&m_soap);

			/// <summary>
			/// detach context (last use and no longer in scope)
			/// </summary>
			soap_done(&m_soap);
		}

		/// <summary>
		/// Gets the SOAP.
		/// </summary>
		///
		/// <returns>
		/// The SOAP.
		/// </returns>
		struct soap& GetSoap()
		{
			return m_soap;
		}
	};

	/// <summary>
	/// Information about the rage version.
	/// </summary>
	class RageVersionInfo
	{
	public:

		/// <summary>
		/// Default constructor.
		/// </summary>
		RageVersionInfo();

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~RageVersionInfo() {};

		/// <summary>
		/// Gets the identifier.
		/// </summary>
		///
		/// <returns>
		/// The identifier.
		/// </returns>
		std::string getId();

		/// <summary>
		/// Sets an identifier.
		/// </summary>
		///
		/// <param name="id"> The identifier. </param>
		void setId(std::string id);

		/// <summary>
		/// Gets the major.
		/// </summary>
		///
		/// <returns>
		/// The major.
		/// </returns>
		int getMajor();

		/// <summary>
		/// Sets a major.
		/// </summary>
		///
		/// <param name="major"> The major. </param>
		void setMajor(int major);

		/// <summary>
		/// Gets the minor.
		/// </summary>
		///
		/// <returns>
		/// The minor.
		/// </returns>
		int getMinor();

		/// <summary>
		/// Sets a minor.
		/// </summary>
		///
		/// <param name="minor"> The minor. </param>
		void setMinor(int minor);

		/// <summary>
		/// Gets the build.
		/// </summary>
		///
		/// <returns>
		/// The build.
		/// </returns>
		int getBuild();

		/// <summary>
		/// Gets the revision.
		/// </summary>
		///
		/// <returns>
		/// The revision.
		/// </returns>
		int getRevision();

		/// <summary>
		/// Sets a revision.
		/// </summary>
		///
		/// <param name="revision"> The revision. </param>
		void setRevision(int revision);

		/// <summary>
		/// Gets the maturity.
		/// </summary>
		///
		/// <returns>
		/// The maturity.
		/// </returns>
		std::string getMaturity();

		/// <summary>
		/// Sets a maturity.
		/// </summary>
		///
		/// <param name="maturity"> The maturity. </param>
		void setMaturity(std::string maturity);

		/// <summary>
		/// Gets the dependencies.
		/// </summary>
		///
		/// <returns>
		/// The dependencies.
		/// </returns>
		std::map<std::string, std::string> getDependencies();

		/// <summary>
		/// Sets the dependencies.
		/// </summary>
		///
		/// <param name="dependencies"> The dependencies. </param>
		void setDependencies(std::map<std::string, std::string> dependencies);

		/// <summary>
		/// Sets a build.
		/// </summary>
		///
		/// <param name="build"> The build. </param>
		void setBuild(int build);

		/// <summary>
		/// Gets the version.
		/// </summary>
		///
		/// <returns>
		/// The version.
		/// </returns>
		std::string getVersion();
		//void LoadVersionInfo(struct soap& soap, version& v, const std::string& strXMLPath);

		/// <summary>
		/// Loads version information.
		/// </summary>
		///
		/// <param name="strXMLPath"> Full pathname of the XML file. </param>
		void LoadVersionInfo(const std::string& strXMLPath);
		//std::string SaveVersionInfo(struct soap& soap, version& v, const std::string& strXMLPath);

		/// <summary>
		/// Saves a version information.
		/// </summary>
		///
		/// <param name="strXMLPath"> Full pathname of the XML file. </param>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		std::string SaveVersionInfo(const std::string& strXMLPath);
	private:

		/// <summary>
		/// A soap.
		/// </summary>
		struct soap soap;

		/// <summary>
		/// A version to process.
		/// </summary>
		version v;

		/// <summary>
		/// The scoped SOAP.
		/// </summary>
		CScopedSoap scopedSoap;
	};
}

#endif // RAGEVERSIONINFO_H
