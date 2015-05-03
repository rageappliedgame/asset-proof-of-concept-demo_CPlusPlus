#include <PubSub.h>

using namespace std;
using namespace rage;

PubSub& PubSub::getInstance()
{
    static PubSub instance;
    return instance;
}

PubSub::~PubSub()
{
    //dtor
}

bool PubSub::define(string topic)
{
    TopicMap::iterator itr = topics.find(topic);
    if (itr == topics.end())
    {
        Subscribers subscribers;
        topics[topic] = subscribers;
    }

    return false;
}

bool PubSub::unsubscribe(int token)
{
    Subscribers::iterator itrSub;
    for(TopicMap::iterator itr = topics.begin(); itr != topics.end(); ++itr)
    {
            itrSub = itr->second.find(token);
            if (itrSub != itr->second.end())
            {
                itr->second.erase(itrSub);
                return true;
            }
    }

    return false;
}
