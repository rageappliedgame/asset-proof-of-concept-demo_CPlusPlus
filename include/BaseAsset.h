#ifndef BASEASSET_H
#define BASEASSET_H

#include <IAsset.h>
#include <RageVersionInfo.h>
#include <IDataArchive.h>
#include <IDataStorage.h>
#include <AssetManager.h>
#include <BaseSettings.h>

namespace rage
{
	class BaseAsset : public IAsset
	{
	public:
		explicit BaseAsset(std::string className);
		virtual ~BaseAsset();
		std::string getClassName();
		std::string getId();
		std::map<std::string, std::string> getDependencies();
		std::string getMaturity();
		std::string getVersion();
		bool hasSettings();

		template<class Settings> Settings* getSettings() {
			if (this->settings != nullptr && dynamic_cast<Settings*>(this->settings))
			{
				return dynamic_cast<Settings*>(this->settings);
			}
			return nullptr;
		}

		//template <class T>
		void setSettings(ISettings* settings);
		bool loadDefaultSettings();
		bool loadSettings(std::string fileName);

		//template <class T>
		bool saveDefaultSettings(bool force);

		//template <class T>
		bool saveSettings(std::string fileName);

		ISettings* settingsFromXml(std::string xml);

		template <class Settings>
		std::string settingsToXml() {
			auto tmp = settings;

#pragma message ("Derive Settigns from settings type?")
			Settings* tmp2 = getSettings<Settings>();

			std::unique_ptr<Settings> tmp1 = std::make_unique<Settings>(*getSettings<Settings>());

			std::stringstream stream;

			//XXX See http://uscilab.github.io/cereal/polymorphism.html
			{
				cereal::XMLOutputArchive archive(stream); // cereal::XMLOutputArchive::Options::Default());

				archive(CEREAL_NVP(tmp1));
			}
			std::string x = stream.str();

			return stream.str();
		}

		IBridge* getBridge();
		void setBridge(IBridge* bridge);
	protected:
		template<class Interface>
		Interface* getInterface()
		{
			if (this->bridge != nullptr && dynamic_cast<Interface*>(this->bridge))
			{
				return dynamic_cast<Interface*>(this->bridge);
			}
			else if (AssetManager::getInstance()->getBridge() != nullptr
				&& dynamic_cast<Interface*>(AssetManager::getInstance()->getBridge()))
			{
				return dynamic_cast<Interface*>(AssetManager::getInstance()->getBridge());
			}

			return nullptr;
		}
	private:
		std::string className;
		std::string id;
		RageVersionInfo *versionInfo = nullptr;
		IBridge *bridge = nullptr;
		ISettings* settings = nullptr;
	};
}

#endif // BASEASSET_H
