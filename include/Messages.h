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
#ifndef MESSAGES_H
#define MESSAGES_H

#include <IAsset.h>
#include <Callback.h>

#include <string>
#include <map>

// namespace: rage
//
// summary:	.
namespace rage
{

#define EVENT_WRAPPER(f) \
    [&] (auto&&... args) -> decltype(auto) \
    { return f (std::forward<decltype(args)>(args)...); }

	/// <summary>
	/// A pub sub implementation.
	/// </summary>
	class Messages
	{
	public:

		/// <summary>
		/// Gets the instance.
		/// </summary>
		///
		/// <returns>
		/// The instance.
		/// </returns>
		static Messages& getInstance();

		/// <summary>
		/// Defines the given topic.
		/// </summary>
		///
		/// <param name="topic"> The topic. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool define(std::string topic);

		/// <summary>
		/// Unsubscribes.
		/// </summary>
		///
		/// <param name="token"> The token. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		bool unsubscribe(int token);

		/// <summary>
		/// Subscribes.
		/// </summary>
		///
		/// <param name="topic">  The topic. </param>
		/// <param name="lambda"> The lambda. </param>
		///
		/// <returns>
		/// An int.
		/// </returns>
		template <typename Function>
		int subscribe(std::string topic, Function lambda)
		{
			define(topic);

			TopicMap::iterator itr = topics.find(topic);

			auto function = new decltype(to_function(lambda))(to_function(lambda));

			itr->second[subUId].function = static_cast<void*>(function);
			itr->second[subUId].signature = &typeid(function);

			return subUId++;
		};

		/// <summary>
		/// Publishes.
		/// </summary>
		///
		/// <param name="topic"> The topic. </param>
		/// <param name="args">  Variable arguments providing the arguments. </param>
		///
		/// <returns>
		/// True if it succeeds, false if it fails.
		/// </returns>
		template <typename ...Args>
		bool publish(std::string topic, Args... args)
		{
			TopicMap::const_iterator itr = topics.find(topic);
			if (itr != topics.end())
			{
				for (Subscribers::const_iterator itrSub = itr->second.begin(); itrSub != itr->second.end(); ++itrSub)
				{
					auto callback = itrSub->second;
					auto function = static_cast<std::function<void(std::string, Args...)>*>(callback.function);
					if (typeid(function) != *(callback.signature))
					{
						//throw std::bad_typeid();
					}

					(*function)(topic, args...);
				}

				return true;
			}

			return false;
		};

		template <typename T>
		void EVENT_ARGS_EXPANDER(T t) {
			std::cout << t << " ";
		};

	private:

		/// <summary>
		/// Default constructor.
		/// </summary>
		Messages() : subUId(1) {};

		/// <summary>
		/// Destructor.
		/// </summary>
		~Messages() {};

		/// <summary>
		/// Copy constructor.
		/// </summary>
		///
		/// <param name="parameter1"> The first parameter. </param>
		Messages(const Messages&);

		/// <summary>
		/// Assignment operator.
		/// </summary>
		///
		/// <param name="parameter1"> The first parameter. </param>
		///
		/// <returns>
		/// A shallow copy of this object.
		/// </returns>
		const Messages& operator=(const Messages&);

		/// <summary>
		/// Defines an alias representing the subscribers.
		/// </summary>
		typedef std::map<int, Callback> Subscribers;

		/// <summary>
		/// Defines an alias representing the topic map.
		/// </summary>
		typedef std::map<std::string, Subscribers> TopicMap;

		/// <summary>
		/// The topics.
		/// </summary>
		TopicMap topics;

		/// <summary>
		/// Identifier for the sub u.
		/// </summary>
		int subUId;
	};
}

#endif // MESSAGES_H
