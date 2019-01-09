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
#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <IAsset.h>

#include <string>
#include <map>
#include <list>

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEPARATOR "\\" 
#else 
#define PATH_SEPARATOR "/" 
#endif 

// Define this simple to use a slightly older C++13 singleton implementation using call_once. 
// 
// See http://www.nuonsoft.com/blog/2017/08/10/implementing-a-thread-safe-singleton-with-c11-using-magic-statics/ 
// for the latest C++11 syntax.  
// 
// See http://www.nuonsoft.com/blog/2012/10/21/implementing-a-thread-safe-singleton-with-c11/for 
// a slightly older C++ implementation using call_once().
#undef USE_CALL_ONCE

namespace rage
{
	/// <summary>
	/// Manager for assets.
	/// </summary>
	class AssetManager
	{
	public:

		/// <summary>
		/// Gets the instance.
		/// </summary>
		///
		/// <returns>
		/// The instance.
		/// </returns>
		static AssetManager& getInstance();

		/// <summary>
		/// Destructor.
		/// 
		/// Note: The original body (now replaced by default) was delete &assets; which caused an
		/// exception at exit.
		/// </summary>
		virtual ~AssetManager() = default;

		/// <summary>
		/// Registers the asset instance.
		/// </summary>
		///
		/// <param name="asset"> [in,out] The asset. </param>
		/// <param name="clazz"> The clazz. </param>
		///
		/// <returns>
		/// A std::string.
		/// </returns>
		std::string registerAssetInstance(IAsset& asset, std::string clazz);

		/// <summary>
		/// Unregisters the asset instance described by ID.
		/// </summary>
		///
		/// <param name="id"> The identifier. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool unregisterAssetInstance(std::string id);

		/// <summary>
		/// Searches for the first asset by identifier.
		/// </summary>
		///
		/// <param name="id"> The identifier. </param>
		///
		/// <returns>
		/// Null if it fails, else the found asset by identifier.
		/// </returns>
		IAsset* findAssetById(std::string id);

		/// <summary>
		/// Searches for the first asset by class.
		/// </summary>
		///
		/// <param name="className"> Name of the class. </param>
		///
		/// <returns>
		/// Null if it fails, else the found asset by class.
		/// </returns>
		IAsset* findAssetByClass(std::string className);

		/// <summary>
		/// Searches for the first assets by class.
		/// </summary>
		///
		/// <param name="className"> Name of the class. </param>
		///
		/// <returns>
		/// Null if it fails, else the found assets by class.
		/// </returns>
		std::list<IAsset*> findAssetsByClass(std::string className);

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
		/// Gets version and dependencies report.
		/// </summary>
		///
		/// <returns>
		/// The version and dependencies report.
		/// </returns>
		std::string getVersionAndDependenciesReport();
	private:
#ifdef USE_CALL_ONCE
		static std::unique_ptr<AssetManager> m_instance;
		static std::once_flag m_onceFlag;
#endif
		/// <summary>
		/// Default constructor.
		/// </summary>
		AssetManager() : idGenerator(0)
		{
			//
		};

		/// <summary>
		/// Copy constructor.
		/// </summary>
		///
		/// <param name="parameter1"> The first parameter. </param>
		AssetManager(const AssetManager&);

		/// <summary>
		/// The assets.
		/// </summary>
		std::map<std::string, IAsset*> assets;

		/// <summary>
		/// The identifier generator.
		/// </summary>
		int idGenerator;

		/// <summary>
		/// The bridge.
		/// </summary>
		IBridge* bridge = nullptr;
	};
}

#endif // ASSETMANAGER_H
