// file:	include\PubSub.h
//
// summary:	Declares the pub sub class
#ifndef PUBSUB_H
#define PUBSUB_H

#include <IAsset.h>
#include <Callback.h>

#include <string>
#include <map>

// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// A pub sub implementation.
	/// </summary>
	class PubSub
	{
	public:

		/// <summary>
		/// Gets the instance.
		/// </summary>
		///
		/// <returns>
		/// The instance.
		/// </returns>
		static PubSub& getInstance();

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

		template <typename Function>

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
		int subscribe(std::string topic, Function lambda)
		{
			define(topic);

			TopicMap::iterator itr = topics.find(topic);

			auto function = new decltype(to_function(lambda))(to_function(lambda));

			itr->second[subUId].function = static_cast<void*>(function);
			itr->second[subUId].signature = &typeid(function);

			return subUId++;
		};

		template <typename ...Args>

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

	private:

		/// <summary>
		/// Default constructor.
		/// </summary>
		PubSub() : subUId(1) {};

		/// <summary>
		/// Destructor.
		/// </summary>
		~PubSub() {};

		/// <summary>
		/// Copy constructor.
		/// </summary>
		///
		/// <param name="parameter1"> The first parameter. </param>
		PubSub(const PubSub&);

		/// <summary>
		/// Assignment operator.
		/// </summary>
		///
		/// <param name="parameter1"> The first parameter. </param>
		///
		/// <returns>
		/// A shallow copy of this object.
		/// </returns>
		const PubSub& operator=(const PubSub&);

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

#endif // PUBSUB_H
