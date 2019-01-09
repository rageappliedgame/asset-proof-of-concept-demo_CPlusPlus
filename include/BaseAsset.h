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
#ifndef BASEASSET_H
#define BASEASSET_H

#include <IAsset.h>
#include <RageVersionInfo.h>
#include <IDefaultSettings.h>
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
		template<class Settings>
		Settings* getSettings() {
			if (this->settings != nullptr && dynamic_cast<Settings*>(this->settings))
			{
				return dynamic_cast<Settings*>(this->settings);
			}
			return nullptr;
		}

		/// <summary>
		/// template &lt;class T&gt;
		/// </summary>
		///
		/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
		virtual void setSettings(ISettings* settings);

		/// <summary>
		/// Loads default settings.
		/// </summary>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		template<class Settings>
		bool loadDefaultSettings() {
			IDefaultSettings* ds = getInterface<IDefaultSettings>();
			if (ds != nullptr && hasSettings() && ds->hasDefaultSettings(className, id))
			{
				std::string xml = ds->loadDefaultSettings(className, id);

				this->settings = settingsFromXml<Settings>(xml);

				return true;

			}
			return false;
		}

		/// <summary>
		/// Loads the settings.
		/// </summary>
		///
		/// <param name="fileName"> Filename of the file. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		template<class Settings>
		bool loadSettings(std::string fileName)
		{
			IDataStorage* ds = getInterface<IDataStorage>();
			if (ds != nullptr && hasSettings() && ds->Exists(fileName))
			{
				std::string xml = ds->Load(fileName);

				this->settings = settingsFromXml<Settings>(xml);

				return true;
			}
			return false;
		}


		/// <summary>
		/// template <class T>
		/// </summary>
		///
		/// <param name="force"> True to force. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		template <class Settings>
		bool saveDefaultSettings(bool force)
		{
			IDefaultSettings* ds = getInterface<IDefaultSettings>();
			if (ds != nullptr && hasSettings() && force)
			{
				ds->saveDefaultSettings(className, id, settingsToXml<Settings>());

				return true;
			}
			return false;
		}


		/// <summary>
		/// template <class T>
		/// </summary>
		///
		/// <param name="fileName"> Filename of the file. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		template <class Settings>
		bool saveSettings(std::string fileName)
		{
			IDataStorage* ds = getInterface<IDataStorage>();
			if (ds != nullptr && hasSettings())
			{
				ds->Save(fileName, settingsToXml<Settings>());

				return true;
			}
			return false;
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

		/// <summary>
		/// Settings to XML.
		/// </summary>
		/// <remarks>This method is public for debugging purposes. 
		/// <returns>
		/// A std::string.
		/// </returns>
		template<class Settings>
		std::string settingsToXml()
		{
			std::unique_ptr<Settings> ptr = std::make_unique<Settings>(*getSettings<Settings>());

			std::stringstream stream;

			/// <summary>
			/// See http://uscilab.github.io/cereal/polymorphism.html
			/// 
			/// Note: cereal populates the stream at the end of the block (just after the archive call it's still empty).
			/// </summary>
			{
				cereal::XMLOutputArchive oarchive(stream); // cereal::XMLOutputArchive::Options::Default());

				oarchive(cereal::make_nvp("AssetSettings", ptr));
			} // archive goes out of scope, ensuring all contents are flushed into the stream.

			/// <summary>
			/// A std::string to process.
			/// </summary>
			std::string x = stream.str();

			return stream.str();
		}

		/// <summary>
		/// Settings from XML.
		/// </summary>
		///
		/// <param name="xml"> The XML. </param>
		///
		/// <returns>
		/// Null if it fails, else a pointer to the ISettings.
		/// </returns>
		template<class Settings>
		Settings* settingsFromXml(std::string xml)
		{
			Settings* settings = new Settings();
			std::stringstream stream;
			stream << xml;

			{
				cereal::XMLInputArchive iarchive(stream);

				//iarchive(settings);
			}

			return settings;
		}
	protected:
		/// <summary>
		/// Gets the interface.
		/// </summary>
		///
		/// <returns>
		/// Null if it fails, else the interface.
		/// </returns>
		template<class Interface>
		Interface* getInterface()
		{
			if (this->bridge != nullptr) {
				if (Interface* icast = dynamic_cast<Interface*>(this->bridge))
				{
					return icast;
				}
			}
			else if (AssetManager::getInstance().getBridge() != nullptr) {
				if (Interface* icast = dynamic_cast<Interface*>(AssetManager::getInstance().getBridge()))
				{
					return icast;
				}
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
