// file:	include\BaseAsset.h
//
// summary:	Declares the base asset class
#ifndef BASEASSET_H
#define BASEASSET_H

#include <IAsset.h>
#include <RageVersionInfo.h>
#include <IDataArchive.h>
#include <IDataStorage.h>
#include <AssetManager.h>
#include <BaseSettings.h>


// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// A base asset.
	/// </summary>
	class BaseAsset : public IAsset
	{
	public:

		/// <summary>
		/// Constructor.
		/// </summary>
		///
		/// <param name="className"> Name of the class. </param>
		explicit BaseAsset(std::string className);

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~BaseAsset();

		/// <summary>
		/// Gets class name.
		/// </summary>
		///
		/// <returns>
		/// The class name.
		/// </returns>
		std::string getClassName();

		/// <summary>
		/// Gets the identifier.
		/// </summary>
		///
		/// <returns>
		/// The identifier.
		/// </returns>
		std::string getId();

		/// <summary>
		/// Gets the dependencies.
		/// </summary>
		///
		/// <returns>
		/// The dependencies.
		/// </returns>
		std::map<std::string, std::string> getDependencies();

		/// <summary>
		/// Gets the maturity.
		/// </summary>
		///
		/// <returns>
		/// The maturity.
		/// </returns>
		std::string getMaturity();

		/// <summary>
		/// Gets the version.
		/// </summary>
		///
		/// <returns>
		/// The version.
		/// </returns>
		std::string getVersion();

		/// <summary>
		/// Query if this object has settings.
		/// </summary>
		///
		/// <returns>
		/// True if settings, false if not.
		/// </returns>
		bool hasSettings();

		/// <summary>
		/// Gets the settings.
		/// </summary>
		///
		/// <typeparam name="Settings"> Type of the settings. </typeparam>
		///
		/// <returns>
		/// Null if it fails, else the settings.
		/// </returns>
		template<class Settings> Settings* getSettings() {
			if (this->settings != nullptr && dynamic_cast<Settings*>(this->settings))
			{
				return dynamic_cast<Settings*>(this->settings);
			}
			return nullptr;
		}

		/// <summary>
		/// template <class T>
		/// </summary>
		///
		/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
		void setSettings(ISettings* settings);

		/// <summary>
		/// Loads default settings.
		/// </summary>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool loadDefaultSettings();

		/// <summary>
		/// Loads the settings.
		/// </summary>
		///
		/// <param name="fileName"> Filename of the file. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool loadSettings(std::string fileName);

		/// <summary>
		/// template <class T>
		/// </summary>
		///
		/// <param name="force"> True to force. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool saveDefaultSettings(bool force);

		/// <summary>
		/// template <class T>
		/// </summary>
		///
		/// <param name="fileName"> Filename of the file. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool saveSettings(std::string fileName);

		/// <summary>
		/// Settings from XML.
		/// </summary>
		///
		/// <param name="xml"> The XML. </param>
		///
		/// <returns>
		/// Null if it fails, else a pointer to the ISettings.
		/// </returns>
		ISettings* settingsFromXml(std::string xml);

		template <class Settings>

		/// <summary>
		/// Settings to XML.
		/// </summary>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		std::string settingsToXml() {

			/// <summary>
			/// The temporary.
			/// </summary>
			auto tmp = settings;

#pragma message ("Derive Settigns from settings type?")

			/// <summary>
			/// The second temporary.
			/// </summary>
			Settings* tmp2 = getSettings<Settings>();

			/// <summary>
			/// The first temporary.
			/// </summary>
			std::unique_ptr<Settings> tmp1 = std::make_unique<Settings>(*getSettings<Settings>());

			/// <summary>
			/// The stream.
			/// </summary>
			std::stringstream stream;

			/// <summary>
			/// .
			/// </summary>
			//XXX See http://uscilab.github.io/cereal/polymorphism.html
			{
				cereal::XMLOutputArchive archive(stream); // cereal::XMLOutputArchive::Options::Default());

				archive(CEREAL_NVP(tmp1));
			}

			/// <summary>
			/// A std::string to process.
			/// </summary>
			std::string x = stream.str();

			return stream.str();
		}

		/// <summary>
		/// Gets the bridge.
		/// </summary>
		///
		/// <returns>
		/// Null if it fails, else the bridge.
		/// </returns>
		IBridge* getBridge();

		/// <summary>
		/// Sets a bridge.
		/// </summary>
		///
		/// <param name="bridge"> [in,out] If non-null, the bridge. </param>
		void setBridge(IBridge* bridge);
	protected:
		template<class Interface>

		/// <summary>
		/// Gets the interface.
		/// </summary>
		///
		/// <returns>
		/// Null if it fails, else the interface.
		/// </returns>
		Interface* getInterface()
		{
			if (this->bridge != nullptr && dynamic_cast<Interface*>(this->bridge))
			{
				return dynamic_cast<Interface*>(this->bridge);
			}
			else if (AssetManager::getInstance().getBridge() != nullptr
				&& dynamic_cast<Interface*>(AssetManager::getInstance().getBridge()))
			{
				return dynamic_cast<Interface*>(AssetManager::getInstance().getBridge());
			}

			return nullptr;
		}
	private:

		/// <summary>
		/// Name of the class.
		/// </summary>
		std::string className;

		/// <summary>
		/// The identifier.
		/// </summary>
		std::string id;

		/// <summary>
		/// Information describing the version.
		/// </summary>
		RageVersionInfo *versionInfo = nullptr;

		/// <summary>
		/// The bridge.
		/// </summary>
		IBridge *bridge = nullptr;

		/// <summary>
		/// Options for controlling the operation.
		/// </summary>
		ISettings* settings = nullptr;
	};
}

#endif // BASEASSET_H
