#ifndef PUBSUB_H
#define PUBSUB_H

#include <IAsset.h>
#include <Callback.h>

#include <string>
#include <map>

namespace rage
{
	class PubSub
	{
        public:
            static PubSub& getInstance();
            bool define(std::string topic);
            bool unsubscribe(int token);

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

            template <typename ...Args>
            bool publish(std::string topic, Args... args)
            {
                TopicMap::const_iterator itr = topics.find(topic);
                if (itr != topics.end())
                {
                    for(Subscribers::const_iterator itrSub = itr->second.begin(); itrSub != itr->second.end(); ++itrSub)
                    {
                        auto callback = itrSub->second;
                        auto function = static_cast<std::function<void(Args...)>*>(callback.function);
                        if (typeid(function) != *(callback.signature))
                        {
                            //throw std::bad_typeid();
                        }

                        (*function)(args...);
                    }

                    return true;
                }

                return false;
            };

        private:
            PubSub() : subUId(1){};
            ~PubSub();
            PubSub(const PubSub&);
            const PubSub& operator=(const PubSub&);
            typedef std::map<int, Callback> Subscribers;
            typedef std::map<std::string, Subscribers> TopicMap;
            TopicMap topics;
            int subUId;
	};
}

#endif // PUBSUB_H
